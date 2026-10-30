#include "landmark_associator.hpp"

#include <cmath>
#include <limits>
#include <Eigen/Cholesky>

namespace urc_slam {

    namespace {

        // Range/azimuth/elevation noise mapped to x/y/z noise at this
        // observation's range. A fixed angular sigma smears points sideways by
        // range * sigma, so far rocks are less certain than near ones. Azimuth
        // and elevation share bearing_sigma_rad, matching the factor's Unit3 noise.
        //Ahh this creates the measurement covariance matric which is related to the joint innovation covaraince matrix how?
        Eigen::Matrix3d cartesianMeasurementCovariance(
            const RockObservation &observation, const RockMeasurementNoise &noise
        ) {
            const double r = observation.range_m();
            const double ca = std::cos(observation.azimuth_rad());
            const double sa = std::sin(observation.azimuth_rad());
            const double ce = std::cos(observation.elevation_rad());
            const double se = std::sin(observation.elevation_rad());
            Eigen::Matrix3d jacobian;   // columns: d/d(range), d/d(azimuth), d/d(elevation)
            jacobian << ce * ca, -r * ce * sa, -r * se * ca,
                        ce * sa,  r * ce * ca, -r * se * sa,
                        se,       0.0,          r * ce;
            const Eigen::Vector3d sigmas(
                noise.range_sigma_m, noise.bearing_sigma_rad, noise.bearing_sigma_rad);
            return jacobian * sigmas.array().square().matrix().asDiagonal() *
                   jacobian.transpose();
        }

        gtsam::Point3 observationInMap(
            const RockObservation &observation,
            const BasePoseEstimate &pose,
            const gtsam::Pose3 &base_T_sensor
        ) {
            return pose.pose.transformFrom(base_T_sensor.transformFrom(observation.sensor_point));
        }

    }

    LandmarkAssociator::LandmarkAssociator(
        const AssociatorParams &params,
        const RockMeasurementNoise &noise,
        const gtsam::Pose3 &base_T_sensor
    )
        : params_(params), noise_(noise), base_T_sensor_(base_T_sensor) {}

    PairTerm LandmarkAssociator::pairTerm(
        const RockObservation &observation,
        const BasePoseEstimate &pose,
        const LandmarkCandidate &candidate
    ) const {
        // Predict where this landmark should appear: map -> base -> sensor.
        gtsam::Matrix36 d_base_d_pose;
        gtsam::Matrix3 d_base_d_landmark;
        const gtsam::Point3 in_base =
            pose.pose.transformTo(candidate.position, d_base_d_pose, d_base_d_landmark);
        const gtsam::Point3 in_sensor = base_T_sensor_.transformTo(in_base);

        //gets the inverse rotation for the base to sensor transofrm -- sensor to base
        const gtsam::Matrix3 sensor_R_base = base_T_sensor_.rotation().inverse().matrix();

        PairTerm term;
        term.innovation = observation.sensor_point - in_sensor;
        term.pose_jacobian = sensor_R_base * d_base_d_pose;
        const Eigen::Matrix3d landmark_jacobian = sensor_R_base * d_base_d_landmark;

        // APPROXIMATION: pose and landmark errors are treated as independent
        // (block-diagonal joint covariance). ISAM2 only exposes single-key
        // marginals cheaply; the cross-covariance would need a joint marginal
        // over the whole graph. In reality they are positively correlated for
        // a landmark seen from a nearby pose, and the innovation depends on
        // their DIFFERENCE, so ignoring the correlation overestimates the
        // innovation covariance: the gate is too LOOSE (more false candidates,
        // more reliance on the JCBB joint test and the Huber kernel to reject
        // them). It never makes the gate too tight.


        
        term.independent_covariance =
            landmark_jacobian * candidate.covariance * landmark_jacobian.transpose() +
            cartesianMeasurementCovariance(observation, noise_);


            //the pose.covariance can be got from the isam 2 graph.
        const Eigen::Matrix3d innovation_covariance =
            term.pose_jacobian * pose.covariance * term.pose_jacobian.transpose() +
            term.independent_covariance;

            
        const double distance_sq =
            term.innovation.dot(innovation_covariance.ldlt().solve(term.innovation));
        term.individually_compatible =
            distance_sq <= chiSquareQuantile(3, params_.gate_confidence);
        return term;
    }

    JcbbProblem LandmarkAssociator::buildProblem(
        const std::vector<RockObservation> &observations,
        const BasePoseEstimate &pose,
        const std::vector<LandmarkCandidate> &candidates
    ) const {
        JcbbProblem problem;
        problem.num_observations = observations.size();
        problem.num_candidates = candidates.size();
        problem.pose_covariance = pose.covariance;
        problem.gate_confidence = params_.gate_confidence;
        problem.ambiguity_margin = params_.ambiguity_margin;
        problem.max_search_nodes = params_.max_search_nodes;
        problem.terms.reserve(observations.size() * candidates.size());
        for (const RockObservation &observation : observations) {
            for (const LandmarkCandidate &candidate : candidates) {
                problem.terms.push_back(pairTerm(observation, pose, candidate));
            }
        }
        return problem;
    }

    std::vector<std::optional<std::size_t>> LandmarkAssociator::nearestNeighbor(
        const std::vector<RockObservation> &observations,
        const BasePoseEstimate &pose,
        const std::vector<LandmarkCandidate> &candidates
    ) const {
        std::vector<std::optional<std::size_t>> choice(observations.size());
        for (std::size_t i = 0; i < observations.size(); ++i) {
            const gtsam::Point3 in_map = observationInMap(observations[i], pose, base_T_sensor_);
            double closest = std::numeric_limits<double>::infinity();
            for (std::size_t j = 0; j < candidates.size(); ++j) {
                const double distance = (candidates[j].position - in_map).norm();
                if (pairTerm(observations[i], pose, candidates[j]).individually_compatible &&
                    distance < closest) {
                    closest = distance;
                    choice[i] = j;
                }
            }
        }
        return choice;
    }

    std::vector<ObservationAssociation> LandmarkAssociator::associate(
        const std::vector<RockObservation> &observations,
        const BasePoseEstimate &pose,
        const std::vector<LandmarkCandidate> &candidates
    ) const {
        const JcbbProblem problem = buildProblem(observations, pose, candidates);
        const JcbbResult search = runJcbb(problem);

        // Why (if at all) the search result may not be acted on, for any
        // observation that had at least one gated candidate.
        AmbiguityReason blocked = AmbiguityReason::kNone;
        if (search.budget_exhausted) {
            blocked = AmbiguityReason::kSearchBudgetExhausted;
        } else if (search.isAmbiguous(params_.ambiguity_margin)) {
            blocked = AmbiguityReason::kEquallyConsistentAlternatives;
        }
        const std::size_t pairings = search.best ? search.best->num_pairings : 0;

        std::vector<ObservationAssociation> result(observations.size());
        for (std::size_t i = 0; i < observations.size(); ++i) {
            bool has_candidate = false;
            for (std::size_t j = 0; j < candidates.size(); ++j) {
                has_candidate = has_candidate || problem.terms[i * candidates.size() + j].individually_compatible;
            }

            ObservationAssociation &out = result[i];
            if (!has_candidate) {
                // Nothing existing can explain it, so creating a node cannot
                // duplicate a landmark.
                out.disposition = Disposition::kNewLandmark;
                continue;
            }

            out.disposition = Disposition::kAmbiguous;
            out.reason = blocked;
            const int matched = search.best ? search.best->assignment[i] : -1;
            if (blocked != AmbiguityReason::kNone) {
                continue;
            }
            if (matched < 0) {
                out.reason = AmbiguityReason::kNoJointlyCompatibleSet;
                continue;
            }

            const LandmarkCandidate &landmark = candidates[static_cast<std::size_t>(matched)];
            // A single pairing with a long-unseen landmark is the weakest
            // possible loop closure: one wrong match drags the whole map.
            if (!landmark.recently_seen && pairings < params_.min_pairings_for_reassociation) {
                out.reason = AmbiguityReason::kTooFewPairings;
                continue;
            }
            out.disposition = Disposition::kMatched;
            out.landmark_key = landmark.key;
        }
        return result;
    }

}

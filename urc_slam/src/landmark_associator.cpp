#include "landmark_associator.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <Eigen/Cholesky>
#include <gtsam/linear/GaussianFactorGraph.h>

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
            const gtsam::Pose3 &pose,
            const gtsam::Pose3 &base_T_sensor
        ) {
            return pose.transformFrom(base_T_sensor.transformFrom(observation.sensor_point));
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
        const gtsam::Pose3 &pose,
        const LandmarkCandidate &candidate
    ) const {
        // Predict where this landmark should appear: map -> base -> sensor.
        gtsam::Matrix36 d_base_d_pose;
        gtsam::Matrix3 d_base_d_landmark;
        const gtsam::Point3 in_base =
            pose.transformTo(candidate.position, d_base_d_pose, d_base_d_landmark);
        const gtsam::Point3 in_sensor = base_T_sensor_.transformTo(in_base);
        const gtsam::Matrix3 sensor_R_base = base_T_sensor_.rotation().inverse().matrix();

        PairTerm term;
        term.innovation = observation.sensor_point - in_sensor;
        term.pose_jacobian = sensor_R_base * d_base_d_pose;
        term.landmark_jacobian = sensor_R_base * d_base_d_landmark;
        term.measurement_covariance = cartesianMeasurementCovariance(observation, noise_);
        return term;
    }

    JcbbProblem LandmarkAssociator::buildProblem(
        const std::vector<RockObservation> &observations,
        const AssociationState &state
    ) const {
        const std::vector<LandmarkCandidate> &candidates = state.candidates;
        const Eigen::Index state_dim = 6 + 3 * static_cast<Eigen::Index>(candidates.size());
        if (state.covariance.rows() != state_dim || state.covariance.cols() != state_dim) {
            throw std::invalid_argument(
                "AssociationState covariance must be (6 + 3 * candidates) square");
        }

        JcbbProblem problem;
        problem.num_observations = observations.size();
        problem.num_candidates = candidates.size();
        problem.state_covariance = state.covariance;
        problem.gate_confidence = params_.gate_confidence;
        problem.ambiguity_margin = params_.ambiguity_margin;
        problem.max_search_nodes = params_.max_search_nodes;
        problem.terms.reserve(observations.size() * candidates.size());
        for (const RockObservation &observation : observations) {
            for (const LandmarkCandidate &candidate : candidates) {
                problem.terms.push_back(pairTerm(observation, state.pose, candidate));
            }
        }
        // A single pairing's joint test is the individual gate.
        for (std::size_t i = 0; i < observations.size(); ++i) {
            for (std::size_t j = 0; j < candidates.size(); ++j) {
                problem.terms[i * candidates.size() + j].individually_compatible =
                    jointDistanceSq(problem, {{i, j}}).has_value();
            }
        }
        return problem;
    }

    std::vector<std::optional<std::size_t>> LandmarkAssociator::nearestNeighbor(
        const std::vector<RockObservation> &observations,
        const AssociationState &state
    ) const {
        const std::vector<LandmarkCandidate> &candidates = state.candidates;
        const JcbbProblem problem = buildProblem(observations, state);
        std::vector<std::optional<std::size_t>> choice(observations.size());
        for (std::size_t i = 0; i < observations.size(); ++i) {
            const gtsam::Point3 in_map = observationInMap(observations[i], state.pose, base_T_sensor_);
            double closest = std::numeric_limits<double>::infinity();
            for (std::size_t j = 0; j < candidates.size(); ++j) {
                const double distance = (candidates[j].position - in_map).norm();
                if (problem.terms[i * candidates.size() + j].individually_compatible &&
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
        const AssociationState &state
    ) const {
        const std::vector<LandmarkCandidate> &candidates = state.candidates;
        const JcbbProblem problem = buildProblem(observations, state);
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


    //Extracting pose landmark covaraince
    namespace {


        using Clique = gtsam::ISAM2::sharedClique;

        //finds the lowest common ancestor between two cliques
        Clique lowestCommonAncestor(Clique a, Clique b) {

            //hashmap of all ansectors of first clique

            std::unordered_set<const gtsam::ISAM2Clique *> ancestors_of_a;

            //find and save all ancestors of a
            for (; a; a = a->parent()) {
                ancestors_of_a.insert(a.get());
            }

            //starting at second clique, while clique is not in list of ancestors of a, keep moving up the tree
            while (b && !ancestors_of_a.count(b.get())) {
                b = b->parent();
            }

            //if b goes off the map there is no lca
            if (!b) {
                throw std::invalid_argument("jointCovariance: keys are in disconnected Bayes trees");
            }

            //return b
            return b;
        }

    }

  
    gtsam::Matrix jointCovariance(const gtsam::ISAM2 &isam, const gtsam::KeyVector &keys) {
        //list of all cliques queries(robot post and landmarks within a range)
        std::vector<Clique> query_cliques;


        //not sure yet
        std::unordered_set<const gtsam::ISAM2Clique *> holds_query;

        //for keys in vector of keys
        for (gtsam::Key key : keys) {
            //extract clique for that key
            const Clique &clique = isam[key];
            //if not already visited add to list of queried cliques
            if (holds_query.insert(clique.get()).second) {
                query_cliques.push_back(clique);
            }
        }

        //pick a clique
        Clique top = query_cliques.front();

        //finds the lowest common anscetor of all the cliques. 
        //note that if cliques are disjoint this will error. 
        for (const Clique &clique : query_cliques) {
            top = lowestCommonAncestor(top, clique);
        }

        // Walk each path up until it meets the tree; count children per clique
        // so branch points can be told apart from pass-through cliques.

        
        std::unordered_set<const gtsam::ISAM2Clique *> on_tree{top.get()};

        //holds the children count of each clique
        std::unordered_map<const gtsam::ISAM2Clique *, int> tree_children;

        //the steiner subtree
        std::vector<Clique> tree_cliques;

        //for cliques in queried cliques
        for (const Clique &clique : query_cliques) {
            //while not at the lca, keep moving up
            for (Clique c = clique; on_tree.insert(c.get()).second; c = c->parent()) {
                //add the clique to the tree up to the common ancestor(save all the paths)
                tree_cliques.push_back(c);
                //update the children
                ++tree_children[c->parent().get()];
            }
        }


        //optimizing for cliques, skips things not quered for, not branching, and not lca
        const auto kept = [&](const gtsam::ISAM2Clique *c) {
            const auto children = tree_children.find(c);
            return c == top.get() || holds_query.count(c) ||
                   (children != tree_children.end() && children->second > 1);
        };


        //lca marginal
        gtsam::GaussianFactorGraph joint = top->marginal2();
        //for cliques in the steiner tree
        for (const Clique &clique : tree_cliques) {
            //if needs to be skipped, skip it
            if (!kept(clique.get())) {
                continue;
            }

            //extract the ansector
            Clique ancestor = clique->parent();
            while (!kept(ancestor.get())) {
                ancestor = ancestor->parent();
            }
            joint.push_back(clique->conditional());
            joint.push_back(clique->shortcut(ancestor));   // empty when ancestor is the parent
        }

        const gtsam::Ordering order(keys);
        return gtsam::GaussianFactorGraph(*joint.marginalMultifrontalBayesNet(order))
            .hessian(order).first.inverse();
    }

}

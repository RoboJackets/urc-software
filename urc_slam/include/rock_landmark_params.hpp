#ifndef ROCK_LANDMARK_PARAMS_HPP_
#define ROCK_LANDMARK_PARAMS_HPP_

#include <cstddef>
#include <limits>
#include <gtsam/geometry/Pose3.h>

#include "rock_extractor_params.hpp"

namespace urc_slam {

    // Noise of a rock observation expressed as range/bearing of the EXTRACTED
    // centre (sphere-fit centre). No default: values come from configuration
    // (measured in simulation, see slam_params.yaml) and validate() rejects NaN.
    struct RockMeasurementNoise {
        double range_sigma_m = std::numeric_limits<double>::quiet_NaN();
        double bearing_sigma_rad = std::numeric_limits<double>::quiet_NaN();
    };

    struct AssociatorParams {
        // Probability mass inside the Mahalanobis gate, for both the
        // individual gate and the joint (JCBB) gate.
        double gate_confidence = 0.99;
        // A landmark last seen more than this many pose indices ago needs
        // min_pairings_for_reassociation jointly compatible pairings.
        std::size_t recently_seen_window_poses = 10;
        std::size_t min_pairings_for_reassociation = 2;
        // Best and runner-up joint hypotheses of equal size closer than this
        // (in joint squared Mahalanobis distance) are declared ambiguous.
        double ambiguity_margin = 2.0;
        // Bounds the exponential worst case of the JCBB tree search.
        std::size_t max_search_nodes = 20000;
        // Base map-frame search radius around the robot for association
        // candidates: the farthest a detectable rock's CENTRE can be, i.e.
        // extractor.max_range_m (surface reach) + extractor.max_radius_m.
        // validate() rejects anything smaller.
        double candidate_radius_m = 2.5;
        // The radius grows by this many 1-sigma pose position errors, so a
        // robot that has drifted still considers the landmarks it may really
        // be next to. Robot and landmark positions are both estimates; only
        // the pose term is added because landmark uncertainty is smaller
        // whenever drift is the problem.
        double candidate_pose_sigma_scale = 3.0;
        // Caps the grown radius: joint covariance and JCBB cost grow with the
        // number of candidates.
        double max_candidate_radius_m = 10.0;
    };

    struct RockLandmarkParams {
        RockExtractorParams extractor;
        RockMeasurementNoise noise;
        AssociatorParams associator;
        // Huber threshold in units of whitened residual (sigmas). 1.345 is the
        // textbook 95%-efficiency value for Gaussian noise.
        double huber_kernel_width = 1.345;
        // Physical gate on landmark creation, applied after the statistical
        // one: a new landmark whose centre lies closer than
        // max(this, r_new + r_mapped) to any mapped landmark would overlap a
        // rock already in the map, so it is dropped. Guards against
        // over-confident covariances that let a re-observation fail the
        // Mahalanobis gate.
        double min_landmark_separation_m = 0.3;
        // A re-sighting adds a factor only if, since the landmark's latest
        // factor, the line of sight turned by this much or the robot moved
        // this far, or more than associator.recently_seen_window_poses
        // keyframes passed. Sightings from nearly the same viewpoint share
        // the sphere-fit bias, so treating each as independent would make
        // the graph over-confident. 0 for both adds a factor every sighting.
        double min_factor_view_change_rad = 0.26;
        double min_factor_travel_m = 1.0;
        // Same identity placeholder as SlamNode::addKeyframeToMap.
        gtsam::Pose3 base_T_sensor;
    };

    // Throws std::invalid_argument naming the offending parameter.
    void validate(const RockLandmarkParams &params);

}

#endif

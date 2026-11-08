/*
Implementation file for path-smoothing using gradient descent

Inputs:
    - A-Star Path


Outputs:
    - The same start point
    - The same end point


Smoothing the Path
    - Get the original A* Path

    - Get the immutable endpoints (start/end)

    - Begin running gradient descent

*/

#include <urc_path_planning/gradient_descent_smoother.hpp>

namespace urc_path_planning {

    GradientDescentSmoother::GradientDescentSmoother(SmoothingParameters parameters) : parameters_(parameters) {}
    //creating the constructor (the parameters will be filled in by a yaml file uploading the weights)

    nav_msgs::msg::Path GradientDescentSmoother::smooth(const nav_msgs::msg::Path & original_path) const { //the smoother will take in a path here
        nav_msgs::msg::Path smoothed_path = original_path;

        if (smoothed_path.poses.size() < 3) {
            return smoothed_path;
        }

        for (std::size_t index = 1; index + 1 < smoothed_path.poses.size(); index++) {

            //this is the original path
            const auto & original = original_path.poses[index].pose.position;


            const auto & previous = smoothed_path.poses[index - 1].pose.position;
            //this is the previous waypont, which for the first iteration is the start point (which is never changed)

            //the current is the current node
            auto & current = smoothed_path.poses[index].pose.position;

            const auto & next = smoothed_path.poses[index + 1].pose.position;
            //this is the next node

            /*
                For every point in the system, we must take it and find the distance between it and
                the original coordinate point, then scale with some data weight, and this is our
                component which keeps us 'close' to the optimized path--this will hopefully prevent
                obstacles and keep our time optimal.

                And then, we must also include a component which does our smoothing, so we take add
                the respective x or y components of our previous and next blocks and then subtract by
                a doubled value of our current standing.
            */
            current.x += parameters_.data_weight * (original.x - current.x)
                + parameters_.smoothness_weight * (previous.x + next.x - 2.0 * current.x);

            current.y += parameters_.data_weight * (original.y - current.y)
                + parameters_.smoothness_weight * (previous.y + next.y - 2.0 * current.y);
            //the smoothing is really just pulling the current point closer to the middle of the point before and after it
        }

        return smoothed_path;

    }



}

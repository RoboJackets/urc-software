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
#include<algorithm> //gives std::max()
#include <cmath> //gives std::hypot()
#include <urc_path_planning/gradient_descent_smoother.hpp>

namespace urc_path_planning {



    GradientDescentSmoother::GradientDescentSmoother(SmoothingParameters parameters) : parameters_(parameters) {}
    //creating the constructor (the parameters will be filled in by a PlannerServer reading a yaml file and uploading the weights)

    nav_msgs::msg::Path GradientDescentSmoother::smooth(const nav_msgs::msg::Path & original_path) const { //the smoother will take in a path here
        nav_msgs::msg::Path smoothed_path = original_path;

        if (smoothed_path.poses.size() < 3) { //if a path is <=2 points, there is no way to smooth it
            return smoothed_path;
        }

        //capping at the safety limit
        for (std::size_t iteration = 0; iteration < parameters_.maximum_iterations; iteration++) {
            double maximum_change = 0.0;

            for (std::size_t index = 1; index + 1 < smoothed_path.poses.size(); index++) {

                //this is the original position of the current waypoint (from astar)
                const auto & original = original_path.poses[index].pose.position;


                const auto & previous = smoothed_path.poses[index - 1].pose.position;
                //this is the previous waypont, for when index == 1 is the start point (which is never changed)

                //the current is the current node
                auto & current = smoothed_path.poses[index].pose.position;

                const auto & next = smoothed_path.poses[index + 1].pose.position;
                //this is the next node

                const double old_x = current.x;
                const double old_y = current.y;

                /*
                    For every point in the system, we must take it and find the displacement between it and
                    the original coordinate point, then scale with some data weight, and this is our
                    component which keeps us 'close' to the optimized path

                    And then, we must also include a component which does our smoothing,
                    which pulls the current node towards the middle of its neighbors,
                    effectively 'smoothing'
                */
                current.x += parameters_.data_weight * (original.x - current.x)
                    + parameters_.smoothness_weight * (previous.x + next.x - 2.0 * current.x);

                current.y += parameters_.data_weight * (original.y - current.y)
                    + parameters_.smoothness_weight * (previous.y + next.y - 2.0 * current.y);
                //the smoothing is really just pulling the current point closer to the middle of the point before and after it


                //finds the straight-line distance from the current waypoint's pre-update and post-update positions
                const double point_change = std::hypot(current.x - old_x, current.y - old_y);

                //finds the max change between the most current point change and the current max change
                maximum_change = std::max(maximum_change, point_change);
            }

            /*if the path difference between two iterations that it is less than our arbitrary tolerance,
            then that means we have "converged", or just become small enough (arbitrarily)
            */

            if (maximum_change < parameters_.tolerance) {
                break;
            }
        }

        return smoothed_path;
    }
}

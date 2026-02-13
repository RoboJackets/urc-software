## Trajectory Following

This package exposes the `/navigate_to_waypoint` action server that, when called, commands the robot along the desired path. The request, response, and feedback definitions can be found [here](/urc_msgs/action/NavigateToWaypoint.action).

>  **Note:** Currently, the server is set up to call an implementation of the pure pursuit algorithm to achieve this. However, it is also set up so that we can (somewhat) easily drop in another
>  path tracking implementation in the future. However, to do this correctly, this would require the creation of a `PathTrackingAlgorithm` interface and a refactor of how we set parameters.

### Swerve Drive Support

The trajectory follower now takes advantage of swerve drive capabilities for improved navigation:

* **In-place turning**: When the robot needs to change direction significantly, it will turn in place before moving forward, reducing path deviation.
* **Holonomic motion**: The controller can command both forward/backward and lateral velocities simultaneously for more direct path following.
* **Final heading alignment**: When goal heading enforcement is enabled, the robot will perform an in-place turn at the goal to achieve the desired final orientation.

To enable swerve drive features, set `enable_holonomic_motion: true` in the configuration. The controller will fall back to diff drive behavior when this is disabled.

The action server is set up to be configurable. See `config/pure_pursuit_config.yaml` for all of the available parameters. The default values are shown below.

| Parameter | Default Value | Description |
| --------- | ------------- | ----------- |
| lookahead_distance | 1.0 | Distance ahead on path to track (meters) |
| desired_linear_velocity | 0.5 | Desired forward velocity (m/s) |
| max_angular_velocity | 1.0 | Maximum turning rate (rad/s) |
| heading_alignment_tolerance | 0.2 | Angular threshold for in-place turns (radians) |
| enable_holonomic_motion | true | Enable swerve drive features |
| cmd_vel_topic | "/cmd_vel" | Topic for velocity commands |
| odom_topic | "/odom" | Topic for odometry |
| map_frame | "map" | Global coordinate frame |
| goal_tolerance | 0.1 | Position tolerance for goal (meters) |
| enforce_goal_heading | false | Require specific heading at goal |
| goal_heading_tolerance | 0.1 | Heading tolerance at goal (radians) |

These default values will be used if the parameter is not defined in the specified config file.

There are also a couple debug outputs.

* The pure pursuit lookahead point is published to the `/carrot` topic.
* A circle representing the lookahead distance is published to the `/lookahead_circle` topic.

Both of these outputs can be visualized in rviz. There is also a rviz configuration file (`/rviz/navigation.rviz`) in the repo that will configure your rviz to visualize all of the outputs from the navigation stack (including path planning). This is useful for debugging purposes.

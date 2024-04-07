## Trajectory Following

This package exposes the the `/follow_path` action server that, when called, commands the robot along the desired path. The request, response, and feedback definitions can be found [here](/urc_msgs/action/FollowPath.action).

>  **Note:** Currently, the server is set up to call an implementation of the pure pursuit algorithm to achieve this. However, it is also set up so that we can (somewhat) easily drop in another
>  path tracking implementation in the future. However, to do this correctly, this would require the creation of a `PathTrackingAlgorithm` interface and a refactor of how we set parameters.

The action server is set up to be configurable. See `config/pure_pursuit_config.yaml` for all of the available parameters. The default values are shown below.

| Parameter | Default Value |
| --------- | ------------- |
| lookahead_distance | 1.0 |
| desired_linear_velocity | 0.5 |
| cmd_vel_topic | "/cmd_vel" |
| odom_topic | "/odom" |
| map_frame | "map" |
| goal_tolerance | 0.1 |

These default values will be used if the parameter is not defined in the specified config file.

There are also a couple debug outputs.

* The pure pursuit lookahead point is published to the `/carrot` topic.
* A circle representing the lookahead distance is published to the `/lookahead_circle` topic.

Both of these outputs can be visualized in rviz. There is also a rviz configuration file (`/rviz/navigation.rviz`) in the repo that will configure your rviz to visualize all of the outputs from the navigation stack (including path planning). This is useful for debugging purposes.

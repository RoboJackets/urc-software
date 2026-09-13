# Pure Pursuit Controller

`PurePursuit` implements the package-wide `TrajectoryController` interface. The
follower action server creates it through `TrajectoryFactory` when the
`trajectory_controller` parameter is set to `pure_pursuit`.

## Controller Contract

Every trajectory controller must:

- accept a planned `nav_msgs/Path` through `setPath()`
- compute a `TrajectoryOutput` from the current map-to-base transform
- return a velocity command in `TrajectoryOutput::cmd_vel`
- return a map-frame collision-check position in
  `TrajectoryOutput::tracking_point`

Pure Pursuit uses its lookahead point as the collision-check position. The
follower action server compares the cost at that position against the lethal
cost threshold and requests a new path when necessary.

## Adding LQR or MPC

An additional controller must implement `TrajectoryController` and be
constructed by `TrajectoryFactory`. Its selection name and parameters must also
be added to the trajectory-following configuration.

The current interface assumes every controller can provide one meaningful
collision-check position. LQR or MPC may instead need to expose a predicted
trajectory. If so, replace this single-point contract with a controller-neutral
collision-check representation before implementing those controllers.

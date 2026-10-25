# Coordinator design

`NavCoordinator` owns one mission and one navigation client. ROS callbacks share
its default mutually exclusive callback group. The TF buffer is thread-safe.

## Mission execution

The timer consumes a navigation result, handles stopping, recovery, and resume, checks the current deadline, and executes the current phase. A phase
starts its operation once and checks completion on later ticks. Commands supply
fresh events; they are never queued for a future phase.

- `src/fsm/`: pure transition tables, deadline selection, and matching reissued
  commands to interrupted tasks.
- `src/missions/`: route/astronaut operations, bounded recovery, the stop barrier,
  and action completion.
- `src/navigation/`: navigation cancellation/replacement, pose validation,
  standoff geometry, GPS conversion, and astronaut stationarity tracking.
- `src/ros/`: actions, subscriptions, parameters, drive handoffs, and LED output.

`ActiveMission` stores progress, observations, retry state, and steady-clock phase
start times. ROS action handles belong to the coordinator. `NavigationClient`
coalesces replacements and waits for the old action's terminal result before
sending another goal; late callbacks cannot complete a newer navigation leg.

## Abort and resume

STOPPING retains ownership until navigation acknowledges cancellation. PAUSED
preserves the interrupted task and selects teleop. RESUMING waits for autonomous
mux feedback and rechecks valid inputs before restarting navigation. Operational failures pause; explicit ROS action
cancellation ends the action.

The existing `/cmd_vel_mode` topic requests mux mode; retained `/drive_mode`
feedback drives the local autonomy flag and status lights. Repeated requests
while waiting make startup independent of discovery order. No new drive service
is required. The mux stops stale commands and arbitrates autonomous/teleop input.

See [state and timeout contracts](state_machine.md) and
[ROS inputs and abort/resume controls](integration.md) for operational behavior.

## Integration boundaries

Route navigation uses fresh nearby ArUco poses to refine its goal. Coordinate
arrival without detection triggers the external spiral service and path follower.
Search requests are invalidated on stop so late replies cannot restart motion. Arm operations currently fail or simulate
completion under an explicit test parameter. Integrate real arm results at
`completeToolPlaceholder()` and emit grasp/release events only after confirmation.
Real arm integration must join the stop barrier: do not grant teleop or complete an
action while a canceled operation can still move hardware.

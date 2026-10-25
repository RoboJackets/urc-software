# States, guards, and execution

This page describes the current implementation. The architecture drawing records
an earlier proposal; search is now a fallback after coordinate arrival.
Start with the [mission flow](../README.md) for the package overview.

## Execution in one paragraph

The timer calls `updateMission()`, which selects the current state's function
through `updateCurrentState()`. That function starts its work once and checks
progress on later updates. On completion it calls `transitionOn(event)`; the FSM
selects a new state and `changeState()` resets progress. Commands can also supply
events directly. See the [file and function guide](code_guide.md) for every
function's purpose and call-flow examples.

## Route execution

Accepted route goals enter RESUMING to confirm autonomous mux mode, then NAVIGATING.
The goal contains only the target waypoint. With refinement enabled, completion
requires a fresh associated marker plus rover distance within `route_arrival_radius`
(1 m by default) of both waypoint and marker. With refinement disabled, only the
waypoint distance is required. Completion passes through STOPPING and waits for
the follower to stop. Follower success alone does not bypass the measured distance check.

With `aruco_refinement=true`, fresh marker poses within
`aruco_association_radius` of the waypoint can refine the navigation goal to
`aruco_standoff` meters from the post. No marker ID is required. The refined goal
must stay within the waypoint arrival radius; otherwise navigation keeps the
original waypoint. Goal updates obey the existing displacement and rate limits.
Arrival checks both waypoint and marker distance while the observation is fresh.
Before coordinate arrival, missing/stale observations use the waypoint. If the
follower reaches it without a fresh detection, STOPPING → SEARCHING_ARUCO waits
for travel to stop and requests a path from `spiral_search_service`. Only a
successful, traversability-checked path in the map frame is followed. A fresh
associated detection cancels the request/search motion; after navigation stops,
NAVIGATING recomputes the marker approach. Path exhaustion or invalid generation
pauses the mission; `search_timeout` also bounds unavailable or unresponsive
services. Late service replies are discarded after abort, retry, or detection.
Resume/recovery returns to waypoint navigation before requesting another search.
Setting `aruco_refinement=false` disables both observation use and fallback search.

Association depends on map localization and calibrated camera geometry; nearby
unrelated markers cannot be distinguished by a route-specific ID in this interface.
On resume the next navigation goal is recalculated from current observations.
Travel still depends on planner/map coverage.

## Astronaut transitions

| From | Condition producing the event | To |
| --- | --- | --- |
| IDLE | Valid accepted astronaut goal | GO_TO_ASTRONAUT |
| GO_TO_ASTRONAUT | Navigation succeeds and distance to the supplied initial waypoint ≤ 3 m by default | WAIT_FOLLOW |
| WAIT_FOLLOW | Fresh FOLLOW command from GESTURE or REMOTE | FOLLOWING |
| FOLLOWING | Person stationary for the configured duration, distance ≤ 3 m, navigation stopped | WAIT_STAY |
| FOLLOWING or WAIT_STAY | STAY command from remote; cancellation completes | STAYING |
| WAIT_STAY | Person moves again or leaves the arrival radius | FOLLOWING |
| STAYING | FETCH from remote | FETCHING |
| FETCHING | GRASP_CONFIRMED event | HOLDING_HAMMER |
| HOLDING_HAMMER | COME from remote | COMING |
| COMING | Navigation succeeds and fresh person distance ≤ 3 m | WAIT_GIVE |
| WAIT_GIVE | GIVE from remote | GIVING |
| GIVING | RELEASE_CONFIRMED event | SUCCEEDED |

The fixed initial waypoint is separate from later person tracking. During STAYING,
tracking is not required: the astronaut can walk away before commanding FETCH.
A brief pause during FOLLOWING does not permanently disable following; WAIT_STAY
returns to FOLLOWING until the explicit STAY command is received.

The initial distance check uses the supplied waypoint, which must represent the
provided GNSS location. STAYING holds until the next valid command; it does not
require distance tracking while the astronaut walks away.

### Following and coming

`astronaut_mission.cpp` takes the latest map-frame astronaut pose and calculates
a goal `follow_distance` meters short of the person along the rover-to-person line.
This is a position-based standoff goal, not an estimate of the person's heading.

Updates require both the configured update period and sufficient goal displacement,
except that an idle follower may need a new goal. Replacements keep only the newest
pending goal. The old action must finish cancellation before the replacement is
sent. An old goal's result cannot advance the new leg.

Stationarity is measured from successive timestamped target observations against
a position anchor. Moving beyond `stationary_distance` resets the dwell interval.
Missing observations cannot establish stationarity. Stale tracking in FOLLOWING,
COMING, or WAIT_STAY immediately requests cancellation and starts recovery.

### Arm extension point

`completeToolPlaceholder()` in `astronaut_mission.cpp` is the only source of
simulated `GRASP_CONFIRMED` and `RELEASE_CONFIRMED` events. It is gated by `tool_placeholder_success` and logs each
simulated completion. This is a testing boundary, not a manipulation implementation.

To integrate a real arm, replace the placeholder with pickup/release requests and
emit those same events only after successful action results. Arm failure should
enter the shared stop/failure path. Extend STOPPING to await arm cancellation too;
never finish a mission while its future arm action is still active. No changes to
the successful astronaut transition sequence should be necessary.

## Recovery, cancellation, and ownership

The supervisor is the active mission kind in `NavCoordinator`: NONE, ROUTE,
ASTRONAUT, or a standalone WAYPOINT. A mission goal is rejected while another owner
is active, the follower is unavailable, or the goal has an invalid frame/pose.
Rejected ROS goals have no terminal result because they never start.

| Condition | Behavior |
| --- | --- |
| Command has wrong source, old/repeated timestamp, or wrong phase | Ignore it; do not queue it for a later phase |
| Navigation fails or is canceled externally | Stop and retry the interrupted phase within the configured budget |
| Required pose/TF becomes stale | Stop; await valid input until the recovery deadline |
| Recoverable failure with budget remaining | RECOVERING → interrupted phase; execute the operation again |
| Retry budget exhausted or recovery times out | STOPPING → PAUSED, then teleop handoff |
| Phase exceeds its enabled deadline | STOPPING → PAUSED with TIMEOUT and the phase name |
| Abort requested | STOPPING → PAUSED; preserve task, then request teleop |
| Valid resume/reissued task command | PAUSED → RESUMING → saved/requested phase after mux confirmation and input validation |
| Mission action canceled | STOPPING → CANCELED; request teleop, release ownership |
| STAY during following recovery | Cancel navigation and enter STAYING |
| Follower has not acknowledged stopping | Remain STOPPING; retain ownership and report the wait |

`max_retries` counts retries after the first attempt. It is not the follower's
obstacle-replan count. Follower replanning remains inside a navigation action;
the phase deadline bounds how long a mission tolerates that work. Retry budgets
reset at new astronaut phases.
They do not reset merely because a failed phase is re-entered.
An explicit resume after a teleop abort starts a new retry budget.

STOPPING is a cancellation barrier: the coordinator never starts another mission
while the follower may still be active. The follower publishes a zero velocity
command before returning success/cancellation/failure. This acknowledges a commanded
stop; physical stopping dynamics still need simulation/hardware validation.
PAUSED retains the action and rejects competing missions. It never commands a
return to the astronaut. See [abort and resume](integration.md#abort-teleoperation-and-resume)
for command and mode contracts. New mission goals also enter RESUMING to
confirm autonomous mux mode before starting their first phase.

### Phase deadlines

The previous `phase_timeout` parameter is replaced by separate limits, in seconds:

| Parameter | Phases | Default |
| --- | --- | --- |
| `navigation_timeout` | Route/waypoint travel and astronaut rendezvous/return | 180 |
| `search_timeout` | Spiral service wait, generation, and path following | 180 |
| `tool_timeout` | FETCHING and GIVING | 180 |
| `following_timeout` | FOLLOWING and WAIT_STAY | 0 (disabled) |
| `command_wait_timeout` | WAIT_FOLLOW, HOLDING_HAMMER, WAIT_GIVE | 0 (disabled) |
| `recovery_timeout` | Reacquisition/recovery, navigation readiness on resume, and stop-wait diagnostics | 5 |

STAYING has no deadline, even if `command_wait_timeout` is enabled. It holds until
FETCH or mission cancellation. Following and command waiting accept zero to
disable their deadlines; navigation, search, tool, and recovery limits must be
positive. All limits must be finite. Each phase entry/retry starts a new deadline;
these are not cumulative mission or course time limits. Freshness checks and
mission cancellation remain active when a phase deadline is disabled. STOPPING
retains ownership until navigation stops, even after its diagnostic threshold.

Phase and recovery deadlines use a steady clock. Observation age uses ROS time,
so sensor publishers and TF must share the coordinator's time source. If simulation
is paused, steady-clock deadlines still expire. The coordinator never silently
uses an old pose when a transform or current observation is missing.

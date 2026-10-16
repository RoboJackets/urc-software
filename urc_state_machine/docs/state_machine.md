# States, guards, and execution

This page describes the code implementing the sequences in the supplied
`RobonavARCH Updated.drawio (1).xml` architecture drawing.
The drawing supplies the intended phase order. Its *proposed/current* labels
refer to an earlier version of the repository; the tables below describe the
present working tree. Start with the [end-to-end flow](../README.md) if the
relationship between the coordinator, follower, and planner is unfamiliar.

## Execution in one paragraph

The timer calls `updateMission()`, which selects the current state's function
through `updateCurrentState()`. That function starts its work once and checks
progress on later updates. On completion it calls `transitionOn(event)`; the FSM
selects a new state and `changeState()` resets progress. Commands can also supply
events directly. See the [file and function guide](code_guide.md) for every
function's purpose and call-flow examples.

## Route transitions

| From | Condition producing the event | To |
| --- | --- | --- |
| IDLE | Valid accepted route goal | NAVIGATING |
| NAVIGATING | Follower succeeds at the search waypoint | SEARCHING_ARUCO |
| SEARCHING_ARUCO | Requested marker has a fresh map pose and coordinator navigation has stopped | CALCULATING_APPROACH |
| CALCULATING_APPROACH | Fresh marker and rover poses allow a standoff goal | NAVIGATING_TO_ARUCO |
| NAVIGATING_TO_ARUCO | Follower reports success | VERIFY_ARRIVAL |
| VERIFY_ARRIVAL | Fresh measured marker distance ≤ `aruco_arrival_radius` | SUCCEEDED |

`SEARCHING_ARUCO` currently waits for a fresh observation of the requested ID
without issuing search navigation goals. Search motion is reserved for the
incoming spiral-search node. No start/cancel interface for that node is wired
yet. The existing phase timeout and mission cancellation remain active. A
matching detection advances to approach after any coordinator-owned navigation
has stopped.

The approach goal lies between the rover and marker at `aruco_standoff` meters
from the marker. An approach result alone does not prove arrival. If verification
fails, the coordinator stops, waits for valid observations, and recomputes the
approach within its retry budget. Retries across the approach/verification cycle
share one budget, preventing an endless navigation-verification loop.

Travel still depends on planner/map coverage. The pending spiral-search node
will need an explicit start/cancel integration.
The drawing's `SEARCH_NONE` branch is absent from the current route action:
`marker_id` must be 1 or 2. The drawing's ID 0 is a start tag, not a route
target. Use the direct waypoint input for navigation without marker search.

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
| Retry budget exhausted or recovery times out | STOPPING → FAILED |
| Phase exceeds `phase_timeout` | STOPPING → FAILED with TIMEOUT |
| Mission action canceled | STOPPING → CANCELED |
| STAY during following recovery | Cancel navigation and enter STAYING |
| Follower has not acknowledged stopping | Remain STOPPING; retain ownership and report the wait |

`max_retries` counts retries after the first attempt. It is not the follower's
obstacle-replan count. Follower replanning remains inside a navigation action;
the phase deadline bounds how long a mission tolerates that work. Retry budgets
reset at new astronaut phases and when initial route navigation enters search.
They do not reset merely because a failed phase is re-entered.

STOPPING is a cancellation barrier: the coordinator never starts another mission
while the follower may still be active. The follower publishes a zero velocity
command before returning success/cancellation/failure. This acknowledges a commanded
stop; physical stopping dynamics still need simulation/hardware validation.

Phase and recovery deadlines use a steady clock. Observation age uses ROS time,
so sensor publishers and TF must share the coordinator's time source. If simulation
is paused, steady-clock deadlines still expire. The coordinator never silently
uses an old pose when a transform or current observation is missing.

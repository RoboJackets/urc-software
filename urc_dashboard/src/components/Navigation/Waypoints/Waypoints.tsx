import { AddWaypoint } from "./AddWaypoint";
import { WaypointCard } from "./WaypointCard";
import { Waypoint } from "./WaypointInterface";

interface WaypointsProps {
  waypoints: Waypoint[];
  addWaypoint: (waypoint: Waypoint) => void;
  deleteWaypoint: (id: number) => void;
}

export const Waypoints = (props: WaypointsProps) => {
  return (
    <div className="p-4 card">
      <div className="card-subtitle">Waypoints</div>
      <AddWaypoint addWaypoint={props.addWaypoint} />

      {props.waypoints.map((waypoint) => (
        <WaypointCard
          waypoint={waypoint}
          deleteWaypoint={props.deleteWaypoint}
        />
      ))}
    </div>
  );
};

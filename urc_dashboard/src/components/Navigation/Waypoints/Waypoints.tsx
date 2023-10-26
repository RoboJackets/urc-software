import { AddWaypoint } from "./AddWaypoint";
import { WaypointCard } from "./WaypointCard";
import { Coordinate } from "../CoordinateInterface";

interface WaypointsProps {
  waypoints: Coordinate[];
  addWaypoint: (waypoint: Coordinate) => void;
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

import { Coordinate } from "../CoordinateInterface";

interface WaypointCardProps {
  waypoint: Coordinate;
  deleteWaypoint: (id: number) => void;
}

export const WaypointCard = (props: WaypointCardProps) => {
  return (
    <div key={props.waypoint.id} className="card">
      <div className="flex whitespace-nowrap gap-2 items-center">
        <span>{`Id: ${props.waypoint.id} | Lat: ${props.waypoint.lat},  Lng: ${props.waypoint.lng}`}</span>
        <button
          className="bg-red-500 p-2 rounded-md"
          onClick={() => props.deleteWaypoint(props.waypoint.id)}
        >
          Delete
        </button>
      </div>
    </div>
  );
};

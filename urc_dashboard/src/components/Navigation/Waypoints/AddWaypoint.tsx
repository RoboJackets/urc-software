import { useState } from "react";
import { Waypoint } from "./WaypointInterface";

interface AddWaypointProps {
  addWaypoint: (waypoint: Waypoint) => void;
}

export const AddWaypoint = (props: AddWaypointProps) => {
  const [lat, setLat] = useState("");
  const [lng, setLng] = useState("");

  const [nextWaypointId, setNextWaypointId] = useState(0);

  const handleAddWaypoint = () => {
    if (isNaN(parseFloat(lat)) || isNaN(parseFloat(lng))) {
      return;
    }

    const newWaypoint = {
      id: nextWaypointId,
      lat: parseFloat(lat),
      lng: parseFloat(lng),
    };
    setNextWaypointId((prevId) => prevId + 1);
    props.addWaypoint(newWaypoint);
    setLat("");
    setLng("");
  };

  return (
    <div className="card">
      <div className="flex gap-2">
        <input
          type="text"
          placeholder="Latitude"
          value={lat}
          onChange={(e) => setLat(e.target.value)}
        />
        <input
          type="text"
          placeholder="Longitude"
          value={lng}
          onChange={(e) => setLng(e.target.value)}
        />
      </div>
      <button
        className="bg-yellow-500 text-white py-2 px-4 rounded"
        onClick={handleAddWaypoint}
      >
        Add Waypoint
      </button>
    </div>
  );
};

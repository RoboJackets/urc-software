import { MapContainer, Marker, TileLayer } from "react-leaflet";
import "leaflet/dist/leaflet.css";

import L from "leaflet";
import { useState } from "react";
import { Waypoint } from "./Waypoints/WaypointInterface";
import { Odometry } from "./Odometry/Odometry";

interface MapProps {
  waypoints: Waypoint[];
  odometry: Odometry;
}
export const Map = (props: MapProps) => {
  const [status, setStatus] = useState(true);

  const toggleStatus = () => {
    setStatus(!status);
  };
  const lat: number = 0;
  const lng: number = 0;

  const createCustomIcon = (waypoint: Waypoint) => {
    return L.divIcon({
      className: "waypoint-marker",
      html: `<div class="marker-content">${waypoint.id}</div>`,
    });
  };

  const robotMarker = L.divIcon({
    className: "robot-marker",
    html: `<div class="marker-content">R</div>`,
  });
  return (
    <div className=" card">
      <MapContainer
        center={[lat, lng]}
        zoom={2}
        maxBounds={[
          [lat, lng],
          [lat, lng],
        ]}
      >
        {props.waypoints.map((waypoint) => (
          <Marker
            key={waypoint.id}
            position={[waypoint.lat, waypoint.lng]}
            icon={createCustomIcon(waypoint)}
          />
        ))}

        <Marker
          position={[props.odometry.lat, props.odometry.lng]}
          icon={robotMarker}
        />

        {status ? (
          <TileLayer url="https://tile.openstreetmap.org/{z}/{x}/{y}.png" />
        ) : (
          <TileLayer url="/static/map/{y}.png" errorTileUrl="error" />
        )}
      </MapContainer>
      <button
        className={
          "text-white py-2 px-4 rounded " +
          (status ? "bg-yellow-500" : "bg-neutral-500")
        }
        onClick={toggleStatus}
      >
        {status ? "Online" : "Offline"}
      </button>
    </div>
  );
};

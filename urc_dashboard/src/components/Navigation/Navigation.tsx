import { useEffect, useState } from "react";
import { Map } from "./Map";
import { Waypoints } from "./Waypoints/Waypoints";
import { Waypoint } from "./Waypoints/WaypointInterface";
import { Odometry } from "./Odometry/Odometry";
import ROSLIB from "roslib";
interface NavigationPrpos {
  ROS: ROSLIB.Ros;
}
export const Navigation = (props: NavigationPrpos) => {
  const [waypoints, setWaypoints] = useState<Waypoint[]>([]);
  const [odometry, setOdometry] = useState<Odometry>({ lat: 0, lng: 0 });

  const odometryTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "add_topic_name_here",
    messageType: "add_topic_type_here",
  });

  useEffect(() => {
    odometryTopic.subscribe((message: any) => {
      setOdometry(message);
    });
  });

  const addWaypoint = (newWaypoint: Waypoint) => {
    setWaypoints((prevWaypoints) => [...prevWaypoints, newWaypoint]);
  };

  const deleteWaypoint = (id: number) => {
    setWaypoints((setWaypoints) => setWaypoints.filter((wp) => wp.id !== id));
  };

  return (
    <div className="flex flex-col card">
      <div className="card-title">Navigation</div>
      <div className="flex gap-2">
        <Map waypoints={waypoints} odometry={odometry} />
        <Waypoints
          waypoints={waypoints}
          addWaypoint={addWaypoint}
          deleteWaypoint={deleteWaypoint}
        />
        <Odometry odometry={odometry} />
      </div>
    </div>
  );
};

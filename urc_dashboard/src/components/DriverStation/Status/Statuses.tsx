import { useEffect, useState } from "react";
import { Status } from "./Status";
import ROSLIB from "roslib";

interface StatusesProps {
  ROS: ROSLIB.Ros;
}

enum StatusColors {
  RED = "bg-red-500",
  YELLOW = "bg-yellow-500",
  GREEN = "bg-green-500",
}

export const Statuses = (props: StatusesProps) => {
  const [bridgeStatus, setBridgeStatus] = useState<StatusColors>(
    StatusColors.RED
  );
  const [robotStatus, setRobotStatus] = useState<StatusColors>(
    StatusColors.RED
  );
  const [lastTimestamp, setLastTimestamp] = useState(0);

  // Rosbridge Status
  props.ROS.on("connection", () => setBridgeStatus(StatusColors.GREEN));
  props.ROS.on("error", () => setBridgeStatus(StatusColors.YELLOW));
  props.ROS.on("close", () => setBridgeStatus(StatusColors.RED));

  // Heartbeat Topic
  const heartbeatTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/heartbeat",
    messageType: "builtin_interfaces/msg/Time",
  });

  // Subscribe to heartbeat topic
  useEffect(() => {
    heartbeatTopic.subscribe((message: any) => {
      setLastTimestamp(message.stamp.sec);
    });
  });

  setInterval(() => {
    if (Date.now() / 1000 - lastTimestamp > 1) {
      setRobotStatus(StatusColors.RED);
    } else {
      setRobotStatus(StatusColors.GREEN);
    }
  });

  return (
    <div className="card">
      <div className="card-title">Status</div>
      <Status value="Rosbridge" color={bridgeStatus} />
      <Status value="Robot" color={robotStatus} />
    </div>
  );
};

import { useEffect, useState } from "react";
import { StatusOption } from "./StatusOption";
import ROSLIB from "roslib";

interface StatusListProps {
  ROS: ROSLIB.Ros;
}

enum StatusColors {
  RED = "bg-red-500",
  YELLOW = "bg-yellow-500",
  GREEN = "bg-green-500",
}

export const StatusList = (props: StatusListProps) => {
  const [bridgeStatus, setBridgeStatus] = useState<StatusColors>(
    StatusColors.RED
  );

  const heartbeatTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/heartbeat",
    messageType: "std_msgs/msg/Header",
  });

  const [robotStatus, setRobotStatus] = useState<StatusColors>(
    StatusColors.RED
  );
  const [lastTimestamp, setLastTimestamp] = useState(0);
  const [gamepadStatus, setGamepadStatus] = useState<StatusColors>(
    StatusColors.RED
  );

  props.ROS.on("connection", () => setBridgeStatus(StatusColors.GREEN));
  props.ROS.on("error", () => setBridgeStatus(StatusColors.YELLOW));
  props.ROS.on("close", () => setBridgeStatus(StatusColors.RED));

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
    <div className="border border-neutral-700 rounded-lg p-2 flex flex-col gap-2 h-min">
      <div className="text-center font-bold">Status</div>
      <StatusOption value="Rosbridge" color={bridgeStatus} />
      <StatusOption value="Robot" color={robotStatus} />
    </div>
  );
};

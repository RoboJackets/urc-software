import { useEffect, useState } from "react";
import { StatusOption } from "./StatusOption";
import ROSLIB from "roslib";
import { State } from "../DriverStation";

interface StatusListProps {
  ROS: ROSLIB.Ros;
  states: Record<string, State>;
  gamepads: Gamepad[];
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
  const desired: number = props.states.controllers.idx + 1;

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

  useEffect(() => {
    if (props.gamepads.length === desired) {
      setGamepadStatus(StatusColors.GREEN);
    } else {
      setGamepadStatus(StatusColors.RED);
    }
  }, [props.gamepads, desired]);

  return (
    <div className="border border-neutral-700 rounded-lg p-2 flex flex-col gap-2 h-min">
      <div className="text-center font-bold">Status</div>
      <StatusOption value="Rosbridge" color={bridgeStatus} />
      <StatusOption value="Gamepads" color={gamepadStatus} />
      <StatusOption value="Robot" color={robotStatus} />
    </div>
  );
};

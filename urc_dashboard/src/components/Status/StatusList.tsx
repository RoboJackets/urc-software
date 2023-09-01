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

  const topic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/heartbeat",
    messageType: "std_msgs/String",
  });

  const [robotStatus, setRobotStatus] = useState<StatusColors>(
    StatusColors.RED
  );
  const [lastTimestamp, setLastTimestamp] = useState(0);

  props.ROS.on("connection", () => setBridgeStatus(StatusColors.GREEN));
  // TODO: somehow print the errors from ROS?
  props.ROS.on("error", () => setBridgeStatus(StatusColors.YELLOW));
  props.ROS.on("close", () => setBridgeStatus(StatusColors.RED));

  useEffect(() => {
    // we update a timestamp pointer using the subscribe method.
    topic.subscribe((message) => console.log(message));
  });

  useEffect(() => {
    if (Date.now() - lastTimestamp > 500) {
      setRobotStatus(StatusColors.RED);
    } else {
      setRobotStatus(StatusColors.GREEN);
    }
  }, [15]);

  // gamepad input logic: read 2 controllers, led flashing to detect which connected, setup a operator and controller picker?
  return (
    <div className="border border-neutral-700 rounded-lg p-2 flex flex-col gap-2 h-min">
      <div className="text-center font-bold">Status</div>
      <StatusOption value="Rosbridge" color={bridgeStatus} />
      <StatusOption value="Gamepad 1" color={StatusColors.RED} />
      <StatusOption value="Gamepad 2" color={StatusColors.RED} />
      <StatusOption value="Robot" color={robotStatus} />
    </div>
  );
};

import { useState } from "react";
import { Modes } from "./Modes";
import { StatusList } from "./Status/StatusList";

interface DriverStationProps {
  ROS: ROSLIB.Ros;
}

export interface State {
  values: string[];
  idx: number;
  setIdx: React.Dispatch<React.SetStateAction<number>>;
  topicName: string;
  messageType: string;
}

export const DriverStation = (props: DriverStationProps) => {
  // TODO: define a gamepad listener object, and publish the gamepad inputs

  const [controlIdx, setControlIdx] = useState<number>(0);
  const [controllerIdx, setControllerIdx] = useState<number>(0);
  const [toggleIdx, setToggleIdx] = useState<number>(0);

  const states: Record<string, State> = {
    controls: {
      values: ["Teleop", "Auto", "Test"],
      idx: controlIdx,
      setIdx: setControlIdx,
      topicName: "/settings/control_modes",
      messageType: "std_msgs/String",
    },
    controllers: {
      values: ["1 Controller", "2 Controllers"],
      idx: controllerIdx,
      setIdx: setControllerIdx,
      topicName: "/settings/controllers",
      messageType: "std_msgs/String",
    },
    toggle: {
      values: ["Enable", "Disable"],
      idx: toggleIdx,
      setIdx: setToggleIdx,
      topicName: "/settings/toggle",
      messageType: "std_msgs/String",
    },
  };
  return (
    <div className="flex flex-col border border-neutral-700 rounded-xl w-min text-center p-2 m-5">
      <div className="font-bold text-lg mb-1">Driver Station</div>
      <div className="flex gap-2">
        <Modes ROS={props.ROS} states={states} />
        <StatusList ROS={props.ROS} states={states} />
      </div>
    </div>
  );
};

import { ModesList } from "./ModesList";
import { useState } from "react";

interface ModesProps {
  ROS: ROSLIB.Ros;
}

export interface Mode {
  values: string[];
  idx: number;
  setIdx: React.Dispatch<React.SetStateAction<number>>;
  topicName: string;
  messageType: string;
}

export const Modes = (props: ModesProps) => {
  const [controlIdx, setControlIdx] = useState<number>(0);
  const [toggleIdx, setToggleIdx] = useState<number>(1);

  const modes: Record<string, Mode> = {
    controls: {
      values: ["Teleop", "Auto", "Test"],
      idx: controlIdx,
      setIdx: setControlIdx,
      topicName: "/mode",
      messageType: "std_msgs/String",
    },
    toggle: {
      values: ["Enable", "Disable"],
      idx: toggleIdx,
      setIdx: setToggleIdx,
      topicName: "/enabled",
      messageType: "std_msgs/Bool",
    },
  };
  return (
    <div className="flex gap-2">
      <div className="card">
        <div className="card-title">Mode</div>
        <ModesList mode={modes.controls} ROS={props.ROS} />
      </div>
      <div className="card">
        <div className="card-title">State</div>
        <ModesList mode={modes.toggle} ROS={props.ROS} />
      </div>
    </div>
  );
};

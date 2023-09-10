import { useState } from "react";
import { Modes } from "./Modes";
import { StatusList } from "../Status/StatusList";
import { GamepadListener } from "./GamepadListener";
import { ControllerSelector } from "./ControllerSelector";

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
  const [controlIdx, setControlIdx] = useState<number>(0);
  const [toggleIdx, setToggleIdx] = useState<number>(0);
  const [driverGamepadIdx, setDriverGamepadIdx] = useState<number>(0);
  const [armGamepadIndex, setArmGamepadIdx] = useState<number>(0);
  const [gamepadCounter, setGamepadCounter] = useState<number>(0);

  const states: Record<string, State> = {
    controls: {
      values: ["Teleop", "Auto", "Test"],
      idx: controlIdx,
      setIdx: setControlIdx,
      topicName: "/settings/control_modes",
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

  window.addEventListener("gamepadconnected", (event) => {
    setGamepadCounter(gamepadCounter + 1);
  });

  window.addEventListener("gamepaddisconnected", (event) => {
    setGamepadCounter(gamepadCounter - 1);
  });

  return (
    <div className="flex flex-col border border-neutral-700 rounded-xl w-min text-center p-2 m-5">
      <div className="font-bold text-lg mb-1 whitespace-nowrap">
        Driver Station
      </div>
      <div className="flex gap-2">
        <Modes ROS={props.ROS} states={states} />
        <StatusList ROS={props.ROS} />
        <GamepadListener
          ROS={props.ROS}
          driverGamepadIdx={driverGamepadIdx}
          setDriverGamepadIdx={setDriverGamepadIdx}
          armGamepadIdx={armGamepadIndex}
          setArmGamepadIdx={setArmGamepadIdx}
        />
      </div>
      <ControllerSelector
        driverGamepadIdx={driverGamepadIdx}
        setDriverGamepadIdx={setDriverGamepadIdx}
        armGamepadIdx={armGamepadIndex}
        setArmGamepadIdx={setArmGamepadIdx}
        gamepadCounter={gamepadCounter}
      />
    </div>
  );
};

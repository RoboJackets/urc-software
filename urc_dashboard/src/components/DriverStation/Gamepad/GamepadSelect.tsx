import { useState } from "react";
import { GamepadPublisher } from "./GamepadPublisher";
import { GamepadDropdown } from "./GamepadDropdown";

interface GamepadSelectProps {
  ROS: ROSLIB.Ros;
}

export const GamepadSelect = (props: GamepadSelectProps) => {
  const [driverGamepadIdx, setDriverGamepadIdx] = useState<number>(0);
  const [armGamepadIdx, setArmGamepadIdx] = useState<number>(0);
  const [gamepadCounter, setGamepadCounter] = useState<number>(0);

  window.addEventListener("gamepadconnected", () => {
    setGamepadCounter(gamepadCounter + 1);
  });

  window.addEventListener("gamepaddisconnected", () => {
    setGamepadCounter(gamepadCounter - 1);
  });

  if (gamepadCounter === 0) {
    return null;
  }

  return (
    <div className="card">
      <div className="font-bold text-center">Gamepads</div>
      <GamepadDropdown operatorType={"Drive"} setState={setDriverGamepadIdx} />
      <GamepadDropdown operatorType={"Arm"} setState={setArmGamepadIdx} />
      <GamepadPublisher
        ROS={props.ROS}
        driverGamepadIdx={driverGamepadIdx}
        armGamepadIdx={armGamepadIdx}
      />
    </div>
  );
};

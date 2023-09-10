import { Modes } from "./Mode/Modes";
import { Statuses } from "./Status/Statuses";
import { GamepadSelect } from "./Gamepad/GamepadSelect";

interface DriverStationProps {
  ROS: ROSLIB.Ros;
}

export const DriverStation = (props: DriverStationProps) => {
  return (
    <div className="card">
      <div className="card-title text-lg">Driver Station</div>
      <div className="flex gap-2">
        <Modes ROS={props.ROS} />
        <Statuses ROS={props.ROS} />
        <GamepadSelect ROS={props.ROS} />
      </div>
    </div>
  );
};

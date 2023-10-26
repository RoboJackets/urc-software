import { Modes } from "./Mode/Modes";
import { Statuses } from "./Status/Statuses";
import { GamepadSelect } from "./Gamepad/GamepadSelect";

interface ControlPanelProps {
  ROS: ROSLIB.Ros;
}

export const ControlPanel = (props: ControlPanelProps) => {
  return (
    <div className="card">
      <div className="card-title text-lg">Control Panel</div>
      <div className="flex gap-2">
        <Modes ROS={props.ROS} />
        <Statuses ROS={props.ROS} />
        <GamepadSelect ROS={props.ROS} />
      </div>
    </div>
  );
};

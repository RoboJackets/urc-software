import { Modes } from "./Modes";
import { StatusList } from "./Status/StatusList";

interface DriverStationProps {
  ROS: ROSLIB.Ros;
}

export const DriverStation = (props: DriverStationProps) => {
  // TODO: define a gamepad listener object, and publish the gamepad inputs
  return (
    <div className="flex flex-col border border-neutral-700 rounded-xl w-min text-center p-2 m-5">
      <div className="font-bold text-lg mb-1">Driver Station</div>
      <div className="flex gap-2">
        <Modes ROS={props.ROS} />
        <StatusList />
      </div>
    </div>
  );
};

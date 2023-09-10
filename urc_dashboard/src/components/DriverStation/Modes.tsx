import { State } from "./DriverStation";
import { SelectList } from "../Select/SelectList";

interface ModesProps {
  ROS: ROSLIB.Ros;
  states: Record<string, State>;
}

export const Modes = (props: ModesProps) => {
  return (
    <div className="flex flex-col gap-1 border border-neutral-700 p-2 rounded-lg h-min">
      <div className="font-bold text-center">Modes</div>
      <div className="flex gap-2">
        <SelectList state={props.states.controls} ROS={props.ROS} />
        <SelectList state={props.states.toggle} ROS={props.ROS} />
      </div>
    </div>
  );
};

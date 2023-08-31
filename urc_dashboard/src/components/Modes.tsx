import { SelectList } from "./Select/SelectList";

interface ModesProps {
  ROS: ROSLIB.Ros;
}

export const Modes = (props: ModesProps) => {
  return (
    <div className="flex flex-col gap-1 border border-neutral-700 p-2 rounded-lg h-min">
      <div className="font-bold text-center">Modes</div>
      <div className="flex gap-2">
        <SelectList
          values={["Teleop", "Auto", "Test"]}
          ROS={props.ROS}
          topicName="/settings/control_modes"
          messageType="std_msgs/String"
        />
        <SelectList
          values={["1 Controller", "2 Controllers"]}
          ROS={props.ROS}
          topicName="/settings/controllers"
          messageType="std_msgs/String"
        />
        <SelectList
          values={["Enable", "Disable"]}
          ROS={props.ROS}
          topicName="/settings/toggle"
          messageType="std_msgs/String"
        />
      </div>
    </div>
  );
};

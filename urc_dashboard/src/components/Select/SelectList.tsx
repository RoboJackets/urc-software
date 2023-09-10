import { SelectOption } from "./SelectOption";
import ROSLIB from "roslib";
import { State } from "../DriverStation/DriverStation";

interface SelectListProps {
  state: State;
  ROS: ROSLIB.Ros;
}

export const SelectList = (props: SelectListProps) => {
  const setCurIdx = props.state.setIdx;
  const curIdx = props.state.idx;
  const values = props.state.values;
  const topicName = props.state.topicName;
  const messageType = props.state.messageType;

  const topic = new ROSLIB.Topic({
    ros: props.ROS,
    name: topicName,
    messageType: messageType,
  });

  const updateIdx = (idx: number) => {
    setCurIdx(idx);
    topic.publish(new ROSLIB.Message({ data: values[idx] }));
  };
  return (
    <div className="flex flex-col p-1 gap-1 border border-neutral-700 rounded-md h-min">
      {values.map((value: string, idx: number) => (
        <SelectOption
          key={idx}
          value={value}
          idx={idx}
          curIdx={curIdx}
          updateIdx={updateIdx}
        />
      ))}
    </div>
  );
};

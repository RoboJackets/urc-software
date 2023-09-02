import { useState } from "react";
import { SelectOption } from "./SelectOption";
import ROSLIB from "roslib";

interface SelectListProps {
  values: string[];
  ROS: ROSLIB.Ros;
  topicName: string;
  messageType: string;
}

export const SelectList = (props: SelectListProps) => {
  const [curIdx, setCurIdx] = useState<number>(0);

  const topic = new ROSLIB.Topic({
    ros: props.ROS,
    name: props.topicName,
    messageType: props.messageType,
  });

  const updateIdx = (idx: number) => {
    setCurIdx(idx);
    topic.publish(new ROSLIB.Message({ data: props.values[idx] }));
  };
  return (
    <div className="flex flex-col p-1 gap-1 border border-neutral-700 rounded-md h-min">
      {props.values.map((value, idx) => (
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

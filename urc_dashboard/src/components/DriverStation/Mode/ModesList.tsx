import { ModesOption } from "./ModesOptions";
import ROSLIB from "roslib";
import { Mode } from "./Modes";

interface ModesListProps {
  mode: Mode;
  ROS: ROSLIB.Ros;
}

export const ModesList = (props: ModesListProps) => {
  const setCurIdx = props.mode.setIdx;
  const curIdx = props.mode.idx;
  const values = props.mode.values;
  const topicName = props.mode.topicName;
  const messageType = props.mode.messageType;

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
        <ModesOption
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

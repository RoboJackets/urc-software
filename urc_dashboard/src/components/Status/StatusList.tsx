import { StatusOption } from "./StatusOption";

export const StatusList = () => {
  // TODO: Add a ROS status listener to update the pointer here

  // TODO: Add a listener for gamepads, and robot heartbeat

  // somehow we need to set which one controller is gamepad 1 and which one is gamepad 2.
  return (
    <div className="border border-neutral-700 rounded-lg p-2 flex flex-col gap-2 h-min">
      <div className="text-center font-bold">Status</div>
      <StatusOption value="Rosbridge" color="red" />
      <StatusOption value="Gamepad 1" color="green" />
      <StatusOption value="Gamepad 2" color="red" />
      <StatusOption value="Robot" color="green" />
    </div>
  );
};

import { Modes } from "./Modes";
import { StatusList } from "./Status/StatusList";

export const DriverStation = () => {
  return (
    <div className="flex flex-col border border-neutral-700 rounded-xl w-min text-center p-2 m-5">
      <div className="font-bold text-lg mb-1">Driver Station</div>
      <div className="flex gap-2">
        <Modes />
        <StatusList />
      </div>
    </div>
  );
};

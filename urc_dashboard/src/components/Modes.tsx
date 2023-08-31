import { SelectList } from "./Select/SelectList";

export const Modes = () => {
  return (
    <div className="flex flex-col gap-1 border border-neutral-700 p-2 rounded-lg h-min">
      <div className="font-bold text-center">Modes</div>
      <div className="flex gap-2">
        <SelectList values={["Teleop", "Auto", "Test"]} />
        <SelectList values={["1 Controller", "2 Controllers"]} />
        <SelectList values={["Enable", "Disable"]} />
      </div>
    </div>
  );
};

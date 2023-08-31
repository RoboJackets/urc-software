import { useState } from "react";
import { SelectOption } from "./SelectOption";

interface SelectListProps {
  values: string[];
}

export const SelectList = (props: SelectListProps) => {
  const [curIdx, setCurIdx] = useState<number>(0);

  return (
    <div className="flex flex-col p-1 gap-1 border border-neutral-700 rounded-md h-min">
      {props.values.map((value, idx) => (
        <SelectOption
          value={value}
          idx={idx}
          curIdx={curIdx}
          setCurIdx={setCurIdx}
        />
      ))}
    </div>
  );
};

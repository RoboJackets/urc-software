interface SelectOptionProps {
  value: string;
  idx: number;
  curIdx: number;
  setCurIdx: Function;
}

export const SelectOption = (props: SelectOptionProps) => {
  let styling =
    "w-full text-sm py-2 px-3 hover:cursor-pointer text-center rounded-md text-neutral-400 hover:text-white";
  return (
    <div
      className={
        styling +
        (props.idx === props.curIdx ? " bg-neutral-700 text-white" : "")
      }
      onClick={() => props.setCurIdx(props.idx)}
    >
      {props.value}
    </div>
  );
};

interface ModesOptionProps {
  value: string;
  idx: number;
  curIdx: number;
  updateIdx: Function;
}

export const ModesOption = (props: ModesOptionProps) => {
  let styling =
    "w-full whitespace-nowrap p-2 text-center rounded-md text-neutral-400 select-none";
  return (
    <div
      className={
        styling +
        (props.idx === props.curIdx ? " bg-neutral-700 text-white" : " hover:cursor-pointer hover:bg-slate-50 hover:text-white")
      }
      onClick={() => props.updateIdx(props.idx)}
    >
      {props.value}
    </div>
  );
};

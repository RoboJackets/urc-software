interface ModesOptionProps {
  value: string;
  idx: number;
  curIdx: number;
  updateIdx: Function;
}

export const ModesOption = (props: ModesOptionProps) => {
  let styling =
    "w-full whitespace-nowrap p-2 hover:cursor-pointer text-center rounded-md text-neutral-400 hover:text-white";
  return (
    <div
      className={
        styling +
        (props.idx === props.curIdx ? " bg-neutral-700 text-white" : "")
      }
      onClick={() => props.updateIdx(props.idx)}
    >
      {props.value}
    </div>
  );
};

interface StatusOptionProps {
  value: string;
  color: string;
}

export const StatusOption = (props: StatusOptionProps) => {
  return (
    <div
      className={"p-1 rounded-md text-center whitespace-nowrap " + props.color}
    >
      {props.value}
    </div>
  );
};

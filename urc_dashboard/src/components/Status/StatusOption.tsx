interface StatusOptionProps {
  value: string;
  color: string;
}

export const StatusOption = (props: StatusOptionProps) => {
  return (
    <div
      className={
        "p-2 rounded-md text-sm text-center whitespace-nowrap " + props.color
      }
    >
      {props.value}
    </div>
  );
};

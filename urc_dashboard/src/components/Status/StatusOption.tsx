interface StatusOptionProps {
  value: string;
  color: string;
}

export const StatusOption = (props: StatusOptionProps) => {
  return (
    <div
      className={
        "p-1 rounded-md text-center whitespace-nowrap " +
        `bg-${props.color}-500`
      }
    >
      {props.value}
    </div>
  );
};

interface ControllerSelectorProps {
  driverGamepadIdx: any;
  setDriverGamepadIdx: any;
  armGamepadIdx: any;
  setArmGamepadIdx: any;
  gamepadCounter: number;
}

export const ControllerSelector = (props: ControllerSelectorProps) => {
  if (props.gamepadCounter === 0) {
    return null;
  }
  const gamepadAlias: Record<string, string> = {
    "Wireless Controller (STANDARD GAMEPAD Vendor: 054c Product: 0ce6)":
      "PS5 Controller",
  };
  return (
    <div className="w-min p-2">
      <div className="flex gap-2 items-center">
        <div>Drive</div>
        <select
          className="bg-neutral-800 rounded-sm pr-1 w-min"
          onChange={(event) => props.setDriverGamepadIdx(event.target.value)}
        >
          {navigator.getGamepads().map((gamepad, idx) => {
            return gamepad ? (
              <option key={idx} value={idx}>
                {gamepadAlias[gamepad.id] || gamepad.id}
              </option>
            ) : null;
          })}
        </select>
      </div>
      <div className="flex gap-2 items-center">
        <div>Arm</div>
        <select
          className="bg-neutral-800 rounded-sm pr-1 w-min"
          onChange={(event) => props.setArmGamepadIdx(event.target.value)}
        >
          {navigator.getGamepads().map((gamepad, idx) => {
            return gamepad ? (
              <option key={idx} value={idx}>
                {gamepadAlias[gamepad.id] || gamepad.id}
              </option>
            ) : null;
          })}
        </select>
      </div>
    </div>
  );
};

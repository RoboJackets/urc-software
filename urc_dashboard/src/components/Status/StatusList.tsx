import { useEffect, useState } from "react";
import { StatusOption } from "./StatusOption";
import ROSLIB from "roslib";

interface StatusListProps {
  ROS: ROSLIB.Ros;
}

enum StatusColors {
  RED = "bg-red-500",
  YELLOW = "bg-yellow-500",
  GREEN = "bg-green-500",
}

export const StatusList = (props: StatusListProps) => {
  const [bridgeStatus, setBridgeStatus] = useState<StatusColors>(
    StatusColors.RED
  );

  const heartbeatTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/heartbeat",
    messageType: "std_msgs/String",
  });

  const driverControllerTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/driverController",
    messageType: "std_msgs/String",
  });

  const operatorControllerTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/operatorController",
    messageType: "std_msgs/String",
  });

  const [robotStatus, setRobotStatus] = useState<StatusColors>(
    StatusColors.RED
  );
  const [lastTimestamp, setLastTimestamp] = useState(0);
  const [gamepads, setGamepads] = useState<Gamepad[]>([]);
  const [gamepadStatus, setGamepadStatus] = useState<StatusColors>(
    StatusColors.RED
  );
  const desired: number = 1;

  props.ROS.on("connection", () => setBridgeStatus(StatusColors.GREEN));
  // TODO: somehow print the errors from ROS?
  props.ROS.on("error", () => setBridgeStatus(StatusColors.YELLOW));
  props.ROS.on("close", () => setBridgeStatus(StatusColors.RED));

  useEffect(() => {
    // we update a timestamp pointer using the subscribe method.
    heartbeatTopic.subscribe((message) => console.log(message));
  });

  // useEffect(() => {
  //   if (Date.now() - lastTimestamp > 500) {
  //     setRobotStatus(StatusColors.RED);
  //   } else {
  //     setRobotStatus(StatusColors.GREEN);
  //   }
  // }, [15]);

  const inputDeadzone = (num: number, deadzone: number) => {
    return Math.abs(num) < deadzone ? 0 : num;
  };

  const checkNonzero = (arr: readonly any[], deadzone: number) => {
    var nonzero = false;
    arr.forEach((element) => {
      if (typeof element == typeof 0.0) {
        if (inputDeadzone(element, deadzone) != 0) {
          nonzero = true;
        }
      } else {
        if (inputDeadzone(element.value, deadzone) != 0) {
          nonzero = true;
        }
      }
    });

    return nonzero;
  };

  const publishMovementInput = (gamepad: Gamepad, topic: ROSLIB.Topic) => {
    let joy_msg = new ROSLIB.Message({
      axes: [
        0.0,
        inputDeadzone(gamepad.axes[1], 0.02),
        0.0,
        0.0,
        inputDeadzone(gamepad.axes[3], 0.02),
      ],
      buttons: [
        gamepad.buttons[0].pressed ? 1 : 0,
        gamepad.buttons[1].pressed ? 1 : 0,
        gamepad.buttons[2].pressed ? 1 : 0,
        gamepad.buttons[3].pressed ? 1 : 0,
      ],
    });

    topic.publish(joy_msg);
  };

  useEffect(() => {
    if (gamepads.length === desired) {
      setGamepadStatus(StatusColors.GREEN);
    } else {
      setGamepadStatus(StatusColors.RED);
    }
  }, [gamepads]);

  setInterval(() => {
    if (gamepads.length === desired) {
      if (
        checkNonzero(gamepads[0].axes, 0.02) ||
        checkNonzero(gamepads[0].buttons, 0)
      ) {
        publishMovementInput(gamepads[0], driverControllerTopic);
      }

      if (
        checkNonzero(gamepads[-1].axes, 0.02) ||
        checkNonzero(gamepads[-1].buttons, 0)
      ) {
        publishMovementInput(gamepads[-1], operatorControllerTopic);
      }
    }
  }, 100);

  window.addEventListener("gamepadconnected", (event) => {
    console.log(event.gamepad);
    setGamepads((prev) => [...prev, event.gamepad]);
  });

  window.addEventListener("gamepaddisconnected", (event) => {
    console.log(event.gamepad);
    setGamepads((prev) => prev.filter((gamepad) => gamepad !== event.gamepad));
  });

  // TODO: switch controller order method.
  return (
    <div className="border border-neutral-700 rounded-lg p-2 flex flex-col gap-2 h-min">
      <div className="text-center font-bold">Status</div>
      <StatusOption value="Rosbridge" color={bridgeStatus} />
      <StatusOption value="Gamepads" color={gamepadStatus} />
      <StatusOption value="Robot" color={robotStatus} />
    </div>
  );
};

import ROSLIB from "roslib";
import { State } from "./DriverStation";

interface GamepadListenerProps {
  ROS: ROSLIB.Ros;
  states: Record<string, State>;
  gamepads: Gamepad[];
  setGamepads: React.Dispatch<React.SetStateAction<Gamepad[]>>;
}

export const GamepadListener = (props: GamepadListenerProps) => {
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

  const desired = props.states.controllers.idx + 1;
  const inputDeadzone = (num: number, deadzone: number) => {
    return Math.abs(num) < deadzone ? 0 : num;
  };

  const checkNonzero = (arr: readonly any[], deadzone: number) => {
    var nonzero = false;
    arr.forEach((element) => {
      if (typeof element == typeof 0.0) {
        if (inputDeadzone(element, deadzone) !== 0) {
          nonzero = true;
        }
      } else {
        if (inputDeadzone(element.value, deadzone) !== 0) {
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

  // const switchGamepadOrder = () => {
  //   if (props.gamepads.length === 2) {
  //     props.setGamepads((prev) => [prev[1], prev[0]]);
  //   }
  // };

  window.addEventListener("gamepadconnected", (event) => {
    props.setGamepads((prev) => [...prev, event.gamepad]);
  });

  window.addEventListener("gamepaddisconnected", (event) => {
    props.setGamepads((prev) =>
      prev.filter((gamepad) => gamepad !== event.gamepad)
    );
  });

  setInterval(() => {
    if (props.gamepads.length === desired) {
      if (
        checkNonzero(props.gamepads[0].axes, 0.02) ||
        checkNonzero(props.gamepads[0].buttons, 0)
      ) {
        publishMovementInput(props.gamepads[0], driverControllerTopic);
      }

      if (
        checkNonzero(props.gamepads[-1].axes, 0.02) ||
        checkNonzero(props.gamepads[-1].buttons, 0)
      ) {
        publishMovementInput(props.gamepads[-1], operatorControllerTopic);
      }
    }
  }, 100);

  return null;
};

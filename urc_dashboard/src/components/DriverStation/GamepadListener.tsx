import ROSLIB from "roslib";

interface GamepadListenerProps {
  ROS: ROSLIB.Ros;
  driverGamepadIdx: any;
  setDriverGamepadIdx: any;
  armGamepadIdx: any;
  setArmGamepadIdx: any;
}

export const GamepadListener = (props: GamepadListenerProps) => {
  const driverTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/driverController",
    messageType: "std_msgs/String",
  });

  const armTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/operatorController",
    messageType: "std_msgs/String",
  });

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

  const publishMovementInput = (gamepad: any, topic: ROSLIB.Topic) => {
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

  // checkNonZero logic, refactoring needed
  setInterval(() => {
    if (navigator.getGamepads()[props.driverGamepadIdx]) {
      publishMovementInput(
        navigator.getGamepads()[props.driverGamepadIdx],
        driverTopic
      );
    }
    if (navigator.getGamepads()[props.driverGamepadIdx]) {
      publishMovementInput(
        navigator.getGamepads()[props.armGamepadIdx],
        armTopic
      );
    }
  }, 100);

  return null;
};

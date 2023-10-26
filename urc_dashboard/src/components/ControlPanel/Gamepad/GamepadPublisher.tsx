import ROSLIB from "roslib";

interface GamepadPublisherProps {
  ROS: ROSLIB.Ros;
  driverGamepadIdx: number;
  armGamepadIdx: number;
}

export const GamepadPublisher = (props: GamepadPublisherProps) => {
  const driverTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/driverGamepad",
    messageType: "sensor_msgs/msg/Joy",
  });

  const armTopic = new ROSLIB.Topic({
    ros: props.ROS,
    name: "/driverGamepad",
    messageType: "sensor_msgs/msg/Joy",
  });

  // Helper Functions
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

  // Publish Movement Method
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

  // Publish Gamepad Movement Every 100ms
  setInterval(() => {
    const driveGamepad = navigator.getGamepads()[props.driverGamepadIdx];
    const armGamepad = navigator.getGamepads()[props.armGamepadIdx];
    if (
      driveGamepad &&
      checkNonzero(driveGamepad.axes, 0.02) &&
      checkNonzero(driveGamepad.buttons, 0.02)
    ) {
      publishMovementInput(driveGamepad, driverTopic);
    }
    if (
      armGamepad &&
      checkNonzero(armGamepad.axes, 0.02) &&
      checkNonzero(armGamepad.buttons, 0.02)
    ) {
      publishMovementInput(armGamepad, armTopic);
    }
  }, 100);

  return null;
};

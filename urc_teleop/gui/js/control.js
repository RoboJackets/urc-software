// Joystick publication
// --------------------

const joy_publisher = new ROSLIB.Topic({
  ros : ros,
  name : '/joy',
  messageType : 'sensor_msgs/msg/Joy'
});

function publishInput(gamepad) {
    let joy_msg = new ROSLIB.Message({
        axes: [
            0.0,
            gamepad[0].axes[0],
            0.0,
            0.0,
            gamepad[0].axes[0]
        ],
        buttons: [
            gamepad.buttons[0],
            gamepad.buttons[1],
            gamepad.buttons[2],
            gamepad.buttons[3]
        ]
    });

    joy_publisher.publish(joy_msg)
}


// Controller functionality
// -----------------------

window.addEventListener("gamepadconnected", event => {
    console.log('Gamepad connected!');
    console.log(event.gamepad);
});

window.addEventListener("gamepaddisconnected", event => {
    console.log('Gamepad disconnected!');
    console.log(event.gamepad);
});

const gamepadDisplay = document.getElementById('gamepad-display');
setInterval(function() {
    var gamepad_list = navigator.getGamepads();
    
    // controller
    if (gamepad_list[0]) {
        const gamepadState = {
            id : gamepads[0].id,
            axes: [
                gamepads[0].axes[0].toFixed(2),
                gamepads[0].axes[1].toFixed(2),
                gamepads[0].axes[2].toFixed(2),
                gamepads[0].axes[3].toFixed(2)
            ],
            buttons: [
                { button_0 : gamepads[0].buttons[0].pressed },
                { button_1 : gamepads[0].buttons[1].pressed },
                { button_2 : gamepads[0].buttons[2].pressed },
                { button_3 : gamepads[0].buttons[3].pressed }
            ]
        }
        gamepadDisplay.textContent = JSON.stringify(gamepadState, null, 2);
        publishInput(gamepad_list[0])
    }
}, 17)

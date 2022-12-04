// Joystick publication
// --------------------

function inputDeadzone(num) {
    return Math.abs(num) < 0.02 ? 0 : num;
}

function checkNonzero(arr) {
    var nonzero = false;
    arr.forEach(element => {
        if (typeof element == typeof 0.0) {
            if (inputDeadzone(element) != 0) {
                nonzero = true;
            }
        } else {
            if (inputDeadzone(element.value) != 0) {
                nonzero = true;
            }
        }
    });

    return nonzero;
}

const joy_publisher = new ROSLIB.Topic({
  ros : ros,
  name : '/joy',
  messageType : 'sensor_msgs/msg/Joy'
});

function publishMovementInput(gamepad) {
    let joy_msg = new ROSLIB.Message({
        axes: [
            0.0,
            inputDeadzone(gamepad.axes[1]),
            0.0,
            0.0,
            inputDeadzone(gamepad.axes[3])
        ],
        buttons: [
            gamepad.buttons[0].pressed ? 1 : 0,
            gamepad.buttons[1].pressed ? 1 : 0,
            gamepad.buttons[2].pressed ? 1 : 0,
            gamepad.buttons[3].pressed ? 1 : 0
        ]
    });
    
    joy_publisher.publish(joy_msg)
}


// Controller/Joystick functionality
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
const joystickDisplay = document.getElementById('joystick-display');

// Checks the gamepad inputs every 17 ms, publishes inputs across rosbridge
setInterval(function() {
    var gamepad_list = navigator.getGamepads();
    
    // controller (rover movement)
    if (gamepad_list[0]) {
        const gamepadState = {
            id : gamepad_list[0].id,
            axes: [
                inputDeadzone(gamepad_list[0].axes[0].toFixed(2)),
                inputDeadzone(gamepad_list[0].axes[1].toFixed(2)),
                inputDeadzone(gamepad_list[0].axes[2].toFixed(2)),
                inputDeadzone(gamepad_list[0].axes[3].toFixed(2))
            ],
            buttons: [
                { button_0 : gamepad_list[0].buttons[0].pressed },
                { button_1 : gamepad_list[0].buttons[1].pressed },
                { button_2 : gamepad_list[0].buttons[2].pressed },
                { button_3 : gamepad_list[0].buttons[3].pressed }
            ]
        }

        if (checkNonzero(gamepad_list[0].axes) || checkNonzero(gamepad_list[0].buttons)) {
            document.getElementById('gamepad').style.boxShadow = '0 0 10px 0 rgba(255, 0, 0, 0.5)';
        }
        else {
            document.getElementById('gamepad').style.boxShadow = none;
        }
        
        gamepadDisplay.textContent = JSON.stringify(gamepadState, null, 2);
        publishMovementInput(gamepad_list[0]);
    }
    
    // joystick (arm movement)
    //if (gamepad_list[1]) {
    //    const joystickState = {
    //        id : gamepad_list[1].id,
    //        axes: [
    //            gamepad_list[1].axes[0].toFixed(2)
    //        ],
    //        buttons: [
    //            { button_0 : gamepad_list[1].buttons[0].pressed }
    //        ]
    //    }
    //    joystickDisplay.textContent = JSON.stringify(joystickState, null, 2);
        //publishArmInput(gamepad_list[1])
    //}
}, 17)
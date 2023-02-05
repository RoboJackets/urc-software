const gamepad_publisher = new ROSLIB.Topic({
    ros : ros,
    name : '/joy',
    messageType : 'sensor_msgs/msg/Joy'
});

// Helper Functions
function inputDeadzone(num, deadzone) {
    return Math.abs(num) < deadzone ? 0 : num;
}

function checkNonzero(arr, deadzone) {
    var nonzero = false;
    arr.forEach(element => {
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
}

function publishMovementInput(gamepad) {
    let joy_msg = new ROSLIB.Message({
        axes: [
            0.0,
            inputDeadzone(gamepad.axes[1], 0.02),
            0.0,
            0.0,
            inputDeadzone(gamepad.axes[3], 0.02)
        ],
        buttons: [
            gamepad.buttons[0].pressed ? 1 : 0,
            gamepad.buttons[1].pressed ? 1 : 0,
            gamepad.buttons[2].pressed ? 1 : 0,
            gamepad.buttons[3].pressed ? 1 : 0
        ]
    });
    
    gamepad_publisher.publish(joy_msg);
}

// Gamepad Event Listeners
window.addEventListener('gamepadconnected', event => {
    console.log('Gamepad Connected!');
    console.log(event.gamepad);
});

window.addEventListener('gamepaddisconnected', event => {
    console.log('Gamepad Disconnected!');
    console.log(event.gamepad);
});

// Checks the gamepad inputs every 15 ms, publishes inputs across rosbridge
setInterval(function() {
    var controller_list = navigator.getGamepads();
    var gamepad_index = -1;
    var joystick_index = -1;

    // Get indexes for controllers
    for (var i = 0; i < controller_list.length; i++) {
        if (controller_list[i] != null) {
            if (controller_list[i].id.includes('Xbox 360 Controller') || controller_list[i].id.includes('Gamepad')) {
                gamepad_index = i;
            } else if (controller_list[i].id.includes('Logitech Attack 3')) {
                joystick_index = i;
            }
        }
    }

    // Deal with gamepad input
    if (gamepad_index >= 0) {
        if (checkNonzero(controller_list[gamepad_index].axes, 0.02) || checkNonzero(controller_list[gamepad_index].buttons, 0.02)) {
            document.getElementById('gamepad').style.opacity = '1';
        } else {
            document.getElementById('gamepad').style.opacity = '0.5';
        }
        
        publishMovementInput(controller_list[gamepad_index]);
    } else {
        document.getElementById('gamepad').style.opacity = '0.5';
    }

    // Deal with joystick input
    if (joystick_index >= 0) {
        if (checkNonzero(controller_list[joystick_index].axes.slice(0, 2), 0.1) || checkNonzero(controller_list[joystick_index].buttons, 0.1)) {
            document.getElementById('joystick').style.opacity = '1';
        } else {
            document.getElementById('joystick').style.opacity = '0.5';
        }

        // publishArmInput(gamepad_list[joystick_index]);
    } else {
        document.getElementById('joystick').style.opacity = '0.5';
    }
}, 15);

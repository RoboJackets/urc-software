# URC Arm Py

This package uses [mink](https://github.com/kevinzakka/mink) to solve Inverse Kinematics (IK) based on an QP-Formuated, task-based approach.

## Requirements

You need to have ros2 installed.

Then, run

```bash
pip install mujoco      # mujoco engine
pip install mink        # mink library
pip install numpy scipy # for numericals and spatial transformation
```

This should installed all the required dependencies for the controller.

## Run the Controller

Simply do

```bash
ros2 launch urc_arm_py mjsim.launch.py
```

And you will see the simulation window popping up.

Publishing a twist command to `/qp_ctrl/cmd_twist` willl change the end-effector mocap location, updating the IK solution.
The position output from IK is sent to `/qp_ctrl/pos_ctrl`.

A quick test script is to run `twist_sender` in a seperate terminal:

```bash
ros2 run urc_arm_py twist_sender
```

You should be able to control the arm's movement using keyboard.

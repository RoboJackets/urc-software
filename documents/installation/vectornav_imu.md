# Launch Instructions for VectorNav with Permission Issues

This document explains how to resolve permission issues for serial devices (like `/dev/ttyUSB0`) and launch the VectorNav package on Linux.

## Prerequisites

1. **Install Necessary Packages**: Ensure all required packages are installed in your workspace and that the workspace is correctly sourced.
   
2. **Device Permissions**: You’ll need permission to access the device files (e.g., `/dev/ttyUSB0`).

## Steps

### Step 1: Check Device Permissions

1. First, identify the device port:
   ```bash
   ls /dev/ttyUSB*
   ```
2. Verify your user has permission to access the device. If you see an error or permission denied, proceed with the steps below.

### Step 2: Add User to the `dialout` Group

The `dialout` group typically has access to serial devices. Add your user to this group:

```bash
sudo usermod -aG dialout $USER
```

**Note**: Log out and log back in for the group change to take effect. Alternatively, you can restart the system to apply these changes immediately.

### Step 3: Verify Permissions

After re-logging or rebooting, check that you have read and write permissions on the device:

```bash
ls -l /dev/ttyUSB0
```

If permissions are set correctly, the output should show that `dialout` has `rw` (read/write) access for `/dev/ttyUSB0`.

### Step 4: Launch VectorNav

Source your ROS workspace, then launch the VectorNav nodes with the appropriate configurations:

```bash
source ~/Documents/urc/rover-colcon/install/setup.bash
ros2 launch vectornav vectornav.launch.py
```

**Note**: Replace the workspace path with the correct path if it’s different on your system.

### Troubleshooting

If you continue to experience issues with permissions, consider checking `dmesg` logs to ensure the device is recognized:

```bash
dmesg | grep ttyUSB
```

This command shows messages related to the USB connection and may help diagnose connectivity issues.

--- 

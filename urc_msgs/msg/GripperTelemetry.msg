# Timestamp and frame copied from the controller feedback.
std_msgs/Header header

# Distance between the inner finger faces in meters.
# Assumes symmetric motion: twice the left_finger_joint position.
float64 opening_width_m

# Rate of change of the opening width in meters per second.
# Twice the left_finger_joint velocity; positive opens, negative closes.
float64 opening_speed_mps

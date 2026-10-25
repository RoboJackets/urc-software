# Timestamp and frame copied from the controller feedback.
std_msgs/Header header

# Distance between the inner finger faces in meters.
# Assumes symmetric motion: twice the left_finger_joint position.
float64 opening_width_m

# Rate of change of the opening width in meters per second.
# Twice the left_finger_joint velocity; positive opens, negative closes.
float64 opening_speed_mps

# Summed normal contact force on each finger, in newtons.
float64 left_force_n
float64 right_force_n

# Nominal average pressure over the configured finger face areas.
float64 left_pressure_pa
float64 right_pressure_pa
float64 combined_pressure_pa

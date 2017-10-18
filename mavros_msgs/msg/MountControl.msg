# ROS representation of Mavlink MAV_CMD_DO_MOUNT_CONTROL message
# http://mavlink.org/messages/common#MAV_CMD_DO_MOUNT_CONTROL


# Enum MAV_MOUNT_MODE (possible mount operation modes)
uint8 MODE_RETRACT = 0  # Load safe position and stop stabilisation
uint8 MODE_NEUTRAL = 1  # Load neutral position
uint8 MODE_MAVLINK_TARGETING = 2  # Load neutral position and start Mavlink control with stabilisation
uint8 MODE_RC_TARGETING = 3  # Load neutral position and start RC control with stabilization
uint8 MODE_GPS_POINT = 4  # Load netural position and start to point at (lat, lon, alt)


std_msgs/Header header

# (pitch, roll, yaw) or (lat, lon, alt) are optional depending on mode
float32 pitch  # degrees or degrees/sec depending on configuration
float32 roll   # degrees or degrees/sec depending on configuration
float32 yaw    # degrees or degrees/sec depending on configuration
float32 lat    # degrees*1e7
float32 lon    # degrees*1e7
float32 alt    # meters
uint8 mode     # from enum MAV_MOUNT_MODE

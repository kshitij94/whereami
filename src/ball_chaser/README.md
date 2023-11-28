First launch the world:
   cd ~/catkin_ws;
   source;
   roslaunch my_robot world.launch;

To start the drive_bot service:
    source;
 rosrun ball_chaser drive_bot

To give commands to the drive_bot service:

 rosservice call /ball_chaser/command_robot "linear_x: 0.5
    angular_z: 0.0"  # This request should drive your robot forward

  rosservice call /ball_chaser/command_robot "linear_x: 0.0
    angular_z: 0.5"  # This request should drive your robot left

    rosservice call /ball_chaser/command_robot "linear_x: 0.0
    angular_z: -0.5"  # This request should drive your robot right

    rosservice call /ball_chaser/command_robot "linear_x: 0.0
    angular_z: 0.0"  # This request should bring your robot to a complete stop

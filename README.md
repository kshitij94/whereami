To launch the world use following commands:

```
cd ~/catkin_ws;
catkin_make;
source devel/setup.bash;
roslaunch my_robot world.launch;

New terminal:
cd ~/catkin_ws/;
source devel/setup.bash;
roslaunch ball_chaser ball_chaser.launch;

```

To just test the drive bot:

```
rosrun ball_chaser drive_bot;

rosservice call /ball_chaser/command_robot "linear_x: 0.5
angular_z: 0.0"  # This request should drive your robot forward

 rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: 0.5"  # This request should drive your robot left

 rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: -0.5"  # This request should drive your robot right

 rosservice call /ball_chaser/command_robot "linear_x: 0.0
angular_z: 0.0"  # This request should bring your robot to a complete stop

```
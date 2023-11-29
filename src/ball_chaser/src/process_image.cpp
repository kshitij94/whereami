#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Image.h>

ros::ServiceClient client;


// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}


// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel_col = -1;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    ROS_INFO_STREAM("img.step");
    ROS_INFO_STREAM(img.step);


      for (int i = 0;i < img.height * img.step; i++) {
        if (img.data[i] == 255) {
            white_pixel_col = i;
            break;
        }
    }

    /*
    for (int row = 0; row < img.height; row++) {
        for (int col = 0; col < img.step; col++) {
            int index = row * col; 
            if (img.data[index] == 255) {
                white_pixel_col = col;
                break;
            }
        }
    }

*/
    ROS_INFO_STREAM("white_pixel_col");
    ROS_INFO_STREAM(white_pixel_col);

    white_pixel_col = white_pixel_col %2400;
    if (white_pixel_col == -1) {
        ROS_INFO_STREAM("Ball not found. Stopping Bot.");        
        drive_robot(0.0, 0.0);
    } else if (((float)white_pixel_col/2400) < 0.33){
        // turn left at 45 degree.
        ROS_INFO_STREAM("Ball found. Rotating left at 45 degree.");        
        drive_robot(0.0, 0.2);
        ROS_INFO_STREAM("Ball found. Rotating left at 45 degree complete.");        
        
        ros::Duration(1).sleep();
        ROS_INFO_STREAM("Ball found. Moving forward now.");        
        
        drive_robot(0.2, 0.0);
    } else if (((float)white_pixel_col/2400) < 0.66) {
        ROS_INFO_STREAM("Ball found. Moving forward.");        

        drive_robot(0.2,0.0);
    } else {
        ROS_INFO_STREAM("Ball found. Rotating right at 45 degree.");        

        // turn right at 45 degree.
        drive_robot(0.0, -0.2);
        ROS_INFO_STREAM("Ball found. Rotating right at 45 degree complete.");        

        ros::Duration(1).sleep();
        ROS_INFO_STREAM("Ball found. Moving forward now.");        
        
        drive_robot(0.2, 0.0);
    }
}


int main(int argc, char** argv)
{
    // Initialize the look_away node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
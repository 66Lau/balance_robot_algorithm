#include <string>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
#include <Eigen/Dense>
#include <casadi/casadi.hpp>
#include "teeterbot_controller/nmpc_cartpole.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "teeterbot_controller_nmpc");
    ros::NodeHandle nh;
    ros::NodeHandle nhPrivate = ros::NodeHandle("~");
    ROS_INFO("Starting the nmpc node");

    nmpc_cartpole cartpole(3,3);
    

    

}
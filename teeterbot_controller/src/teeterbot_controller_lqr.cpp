#include <string>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
#include <Eigen/Dense>

std::string topic_imu = "teeterbot/imu";
std::string topic_left_wheel_speed = "/teeterbot/left_wheel_speed";
std::string topic_right_wheel_speed = "/teeterbot/right_wheel_speed";

std::string topic_left_wheel_torque = "/teeterbot/left_torque_cmd";
std::string topic_right_wheel_torque = "/teeterbot/right_torque_cmd";

std::string topic_control_cmd_vel = "/teeterbot_cmd_vel";

double hz_left_wheel = 100;
double hz_right_wheel = 100;

double state_space_left_x = 0;//locomotion of the robot(as well as the center of the wheel)
double state_space_left_x_dot = 0;//velocity of the robot(as same as the velocity of the wheels)
double state_space_left_theta = 0;//the angular of the pitch axis
double state_space_left_theta_dot = 0;//the angular velocity of the pitch axis

double state_space_right_x = 0;//locomotion of the robot(as well as the center of the wheel)
double state_space_right_x_dot = 0;//velocity of the robot(as same as the velocity of the wheels)
double state_space_right_theta = 0;//the angular of the pitch axis
double state_space_right_theta_dot = 0;//the angular velocity of the pitch axis

double control_output_left_Torque = 0; //the torque of the driving wheel
double control_output_right_Torque = 0; //the torque of the driving wheel

double K1 = 0;
double K2 = 268.6225;
double K3 = 10.66;
double K4 = 73.908;

geometry_msgs::Twist keyboard_input_cmd_vel;



void ImuHandler(const sensor_msgs::Imu::ConstPtr& ImuIn)
{
  // ImuIn->orientation.x;
  // ImuIn->orientation.y;
  // ImuIn->orientation.z;
  // ImuIn->orientation.w;
  // ImuIn->angular_velocity.x;
  // ImuIn->angular_velocity.y; 
  // ImuIn->angular_velocity.z;
  // ImuIn->linear_acceleration.x;
  // ImuIn->linear_acceleration.y;
  // ImuIn->linear_acceleration.z;

  tf::Quaternion quat;
  tf::quaternionMsgToTF(ImuIn->orientation, quat);
  double roll, pitch, yaw;
  tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
  //这里的pitch是距离重心垂直距离的夹角，弧度制
  

  state_space_left_theta_dot = -ImuIn->angular_velocity.y;
  state_space_left_theta = -pitch;
  state_space_right_theta_dot = -ImuIn->angular_velocity.y;
  state_space_right_theta = -pitch;
  // ROS_INFO("pitch:%f",pitch);
}

void LeftWheelSpeedHandler(const std_msgs::Float64::ConstPtr& SpeedIn)
{
  state_space_left_x = state_space_left_x + SpeedIn->data * (1/hz_left_wheel);
  state_space_left_x_dot = SpeedIn->data;
}

void RightWheelSpeedHandler(const std_msgs::Float64::ConstPtr& SpeedIn)
{
  state_space_right_x = state_space_right_x + SpeedIn->data * (1/hz_right_wheel);
  state_space_right_x_dot = SpeedIn->data;
}

void CmdVelSpeedHandler(const geometry_msgs::Twist::ConstPtr& CmdVelIn)
{
  keyboard_input_cmd_vel = *CmdVelIn;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "teeterbot_controller_lqr");
  ros::NodeHandle nh;
  ros::NodeHandle nhPrivate = ros::NodeHandle("~");
  nhPrivate.getParam("K1", K1);
  nhPrivate.getParam("K2", K2);
  nhPrivate.getParam("K3", K3);
  nhPrivate.getParam("K4", K4);

  ros::Subscriber subImu = nh.subscribe<sensor_msgs::Imu>(topic_imu, 100, ImuHandler);
  ros::Subscriber subLeftWheelSpeed = nh.subscribe<std_msgs::Float64>(topic_left_wheel_speed, 100, LeftWheelSpeedHandler);
  ros::Subscriber subRightWheelSpeed = nh.subscribe<std_msgs::Float64>(topic_right_wheel_speed, 100, RightWheelSpeedHandler);
  ros::Subscriber subCmd_vel = nh.subscribe<geometry_msgs::Twist>(topic_control_cmd_vel, 100, CmdVelSpeedHandler);

  ros::Publisher pubLeftWheelTorque = nh.advertise<std_msgs::Float64>(topic_left_wheel_torque, 5);
  ros::Publisher pubRightWheelTorque = nh.advertise<std_msgs::Float64>(topic_right_wheel_torque, 5);

  std_msgs::Float64 left_wheel_torque;
  std_msgs::Float64 right_wheel_torque;

  ros::Rate rate(300);
  bool status = ros::ok();
  while (status)
  {
    ros::spinOnce();
    ROS_INFO("x: %f", state_space_left_x);
    ROS_INFO("theta: %f", state_space_left_theta);
    ROS_INFO("x_dot: %f", state_space_left_x_dot);
    ROS_INFO("theta_dot: %f", state_space_left_theta_dot);

    Eigen::Matrix<double, 4, 1> error; // x theta d-x d-theta
    error <<  0-state_space_left_x, 
              0-state_space_left_theta, 
              keyboard_input_cmd_vel.linear.x-state_space_left_x_dot, 
              0-state_space_left_theta_dot;
    
    Eigen::Matrix<double, 1, 4> K_LQR; 
    K_LQR <<  K1, 
              K2, 
              K3, 
              K4;

    double control_output_left_Torque = K_LQR * error;
    double control_output_right_Torque = K_LQR * error;


    left_wheel_torque.data = control_output_left_Torque * 0.2;
    right_wheel_torque.data = control_output_left_Torque * 0.2;


    ROS_INFO("Wheel Torque: %f", control_output_left_Torque);

    pubLeftWheelTorque.publish(left_wheel_torque);
    pubRightWheelTorque.publish(right_wheel_torque);
    

    status = ros::ok();
    rate.sleep();
  }
}
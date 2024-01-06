#include <string>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Twist.h>

#include <Eigen/Dense>
#include <eigen3/unsupported/Eigen/KroneckerProduct> 
#include "MPC_Prediction.h"
// #include "coder_array.h"

#include <iostream>

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

void MPC_Matrices1(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B, const Eigen::MatrixXd &Q,
                  const Eigen::MatrixXd &R, const Eigen::MatrixXd &F, int N, Eigen::MatrixXd &E, Eigen::MatrixXd &H) {
    int n = A.rows();
    int p = B.cols();

    // Initialize matrices
    Eigen::MatrixXd M = Eigen::MatrixXd::Zero((N + 1) * n, n);
    Eigen::MatrixXd C = Eigen::MatrixXd::Zero((N + 1) * n, N * p);
    Eigen::MatrixXd tmp = Eigen::MatrixXd::Identity(n, n);

    // Update M and C
    for (int i = 0; i < N; ++i) {
        int rows = i * n;
        C.block(n+rows, 0, n, N * p) << tmp * B, C.block(rows, 0, n, (N-1) *p);

        tmp = A * tmp;
        M.block(n+rows, 0, n, n) = tmp;
    }
    ROS_INFO("initializaing M and C matrices");

    // Define Q_bar and R_bar
    Eigen::MatrixXd Q_bar = Eigen::kroneckerProduct(Eigen::MatrixXd::Identity(N+1, N+1), Q);
    Q_bar.block(N*n,N*n,n,n) << F;
    Eigen::MatrixXd R_bar = Eigen::kroneckerProduct(Eigen::MatrixXd::Identity(N, N), R);
    ROS_INFO("initializaing Q_bar and R_bar matrices");


    // Calculate G, E, H
    Eigen::MatrixXd G = M.transpose() * Q_bar * M;
    E = C.transpose() * Q_bar * M;
    H = C.transpose() * Q_bar * C + R_bar;
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "teeterbot_controller_lmpc");
    ros::NodeHandle nh;
    ros::NodeHandle nhPrivate = ros::NodeHandle("~");
    ROS_INFO("Starting the lmpc node");

     ros::Subscriber subImu = nh.subscribe<sensor_msgs::Imu>(topic_imu, 100, ImuHandler);
     ros::Subscriber subLeftWheelSpeed = nh.subscribe<std_msgs::Float64>(topic_left_wheel_speed, 100, LeftWheelSpeedHandler);
     ros::Subscriber subRightWheelSpeed = nh.subscribe<std_msgs::Float64>(topic_right_wheel_speed, 100, RightWheelSpeedHandler);
     ros::Subscriber subCmd_vel = nh.subscribe<geometry_msgs::Twist>(topic_control_cmd_vel, 100, CmdVelSpeedHandler);

     ros::Publisher pubLeftWheelTorque = nh.advertise<std_msgs::Float64>(topic_left_wheel_torque, 5);
     ros::Publisher pubRightWheelTorque = nh.advertise<std_msgs::Float64>(topic_right_wheel_torque, 5);

     std_msgs::Float64 left_wheel_torque;
     std_msgs::Float64 right_wheel_torque;


    double m = 10; //body weight
    double M = 1; // wheel weight
    double g = 9.8; // gravity
    double l = 0.8; //length
    double T = 0.002; //desired control cycle/seconds

    int n = 4; //state dimension
    int p = 1; //control dimension
    int N = 10; //prediction steps(horizon)

    Eigen::MatrixXd A(n, n);
    Eigen::MatrixXd B(n, p);
    Eigen::MatrixXd Q(n, n);
    Eigen::MatrixXd R(p, p);
    Eigen::MatrixXd F(n, n);

    A << 1.0, 0.0,                            T,   0.0,
         0.0, 1.0,                            0.0, T,
         0.0, m * g * T / M,                  1.0, 0.0,
         0.0, (m * g + M * g) * T / (M * l),  0.0, 1.0;

    B << 0.0,
         0.0,
         T / M,
         T / (M * l);
    
    Q << 1, 0.0, 0.0, 0.0,
         0.0, 100.0, 0.0, 0.0,
         0.0, 0.0, 5, 0.0,
         0.0, 0.0, 0.0, 1;

    R << 0;

    F << 0.1, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.5, 0.0,
         0.0, 0.0, 0.0, 0.1;

    Eigen::MatrixXd E, H;
    MPC_Matrices1(A, B, Q, R, F, N, E, H);
     std::cout << "E:\n" << E << "\n\n";
     std::cout << "H:\n" << H << "\n";

     double x_k[4] = {0,0,0,0};
     double u_k_data[1];
     int u_k_size[1];
     double* E_array = E.data();
     double* H_array = H.data();


     ros::Rate rate((int)(1/T));
     bool status = ros::ok();
     while (status)
     {
          ros::spinOnce();
          x_k[0] = state_space_left_x;
          x_k[1] = state_space_left_theta;  
          x_k[2] = state_space_left_x_dot;
          x_k[3] = state_space_left_theta_dot;

          ROS_INFO("x: %f", state_space_left_x);
          ROS_INFO("theta: %f", state_space_left_theta);
          ROS_INFO("x_dot: %f", state_space_left_x_dot);
          ROS_INFO("theta_dot: %f", state_space_left_theta_dot);
          

          MPC_Prediction(x_k, E_array, H_array, N, p, u_k_data, u_k_size);

          left_wheel_torque.data = u_k_data[0]*0.2;
          right_wheel_torque.data = u_k_data[0]*0.2;
          ROS_INFO("torque: %f", u_k_data[0]*0.2);
          pubLeftWheelTorque.publish(left_wheel_torque);
          pubRightWheelTorque.publish(right_wheel_torque);
          std::cout << " " << std::endl;

          status = ros::ok();
          rate.sleep();
     }



}
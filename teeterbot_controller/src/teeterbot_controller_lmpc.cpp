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

    double m = 10; //body weight
    double M = 1; // wheel weight
    double g = 9.8; // gravity
    double l = 0.8; //length
    double T = 0.06; //desired control cycle/seconds

    int n = 4; //state dimension
    int p = 1; //control dimension
    int N = 10; //prediction steps(horizon)
    
    // const double A[16] = {  1,	0,	                T,	0,
    //                         0,	1,	                0,	T,
    //                         0,	m*g*T/M,	        1,	0,
    //                         0,	(m*g+M*g)*T/(M*l),	0,	1};

    // const double B[4] = {0, 0, T/M, T/(M*l)};

    // const double Q[16] = {  0.1, 0,    0,    0,
    //                         0,   10,   0,    0,
    //                         0,   0,    0.5,  0,
    //                         0,   0,    0,    0.1};
    // double R = 0;

    // const double F[16] = {  0.1, 0,   0 ,   0,
    //                         0,   1,   0,    0,
    //                         0,   0,   0.5,  0,
    //                         0,   0,   0,  0.1};
    
    // double N = 10;

    // coder::array<double, 2U> E;
    // coder::array<double, 2U> H;

    // MPC_Matrices(A, B, Q, R, F, N, E, H);

    // for (int i = 0; i < E.size(1); i++) {
    //     if (i > 0) std::cout << " ";
    //     std::cout << E[i];
    //     if (((i+1) % 4) == 0) std::cout << std::endl;
    // }

    // std::cout << "the row of the E "<< E.size(0) << std::endl;
    // std::cout << "the column of the E "<< E.size(1) << std::endl;


    // std::cout << "the row of the E "<< E[5] << std::endl;

    Eigen::MatrixXd A(n, n);
    Eigen::MatrixXd B(n, p);
    Eigen::MatrixXd Q(n, n);
    Eigen::MatrixXd R(p, p);
    Eigen::MatrixXd F(n, n);

    A << 1.0, 0.0, T, 0.0,
         0.0, 1.0, 0.0, T,
         0.0, m * g * T / M, 1.0, 0.0,
         0.0, (m * g + M * g) * T / (M * l), 0.0, 1.0;

    B << 0.0,
         0.0,
         T / M,
         T / (M * l);
    
    Q << 0.1, 0.0, 0.0, 0.0,
         0.0, 10.0, 0.0, 0.0,
         0.0, 0.0, 0.5, 0.0,
         0.0, 0.0, 0.0, 0.1;

    R << 0.1;

    F << 0.1, 0.0, 0.0, 0.0,
         0.0, 1.0, 0.0, 0.0,
         0.0, 0.0, 0.5, 0.0,
         0.0, 0.0, 0.0, 0.1;

    Eigen::MatrixXd E, H;
    MPC_Matrices1(A, B, Q, R, F, N, E, H);

     double x_k[4] = {0,0,0,0};
     // double E_array[40];
     // double H_array[100];
     double u_k_data[1];
     int u_k_size[1];

     double* E_array = E.data();
     double* H_array = H.data();

    MPC_Prediction(x_k, E_array, H_array, N, p, u_k_data, u_k_size);





    std::cout << "E:\n" << E << "\n\n";
    std::cout << "H:\n" << H << "\n";

    std::cout << "u_k_data:\n" << u_k_data[0] << "\n";


}
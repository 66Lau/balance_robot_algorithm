#ifndef NMPC_CARTPOLE_H
#define NMPC_CARTPOLE_H

#include <casadi/casadi.hpp>
#include <iostream>
#include <Eigen/Dense>

class nmpc_cartpole
{
private:
    /* data */
    //系统参数
    double M = 0.5; //轮子质量,单位kg
    double m = 8; //杆末端重量
    double l = 0.8; //杆长
    double g = 9.8; //重力加速度


    // MPC参数
    int m_predict_step; //一次采样间隔预测的步数
    float m_sample_time; //采样时间
    int m_predict_stage; //存储第几次调用nmpc
    int n_states; //共有n个状态-----3
    int n_controls; //共有n个控制输入-----2
    std::vector<Eigen::Matrix<float,3,1>> m_predict_trajectory; //预测轨迹 
    std::vector<float> m_initial_guess; //初始猜测解
    //符号定义
    casadi::Function m_solver; //求解器
    casadi::Function m_predict_fun; //预测函数
    std::map<std::string, casadi::DM> m_res; //求解结果
    std::map<std::string, casadi::DM> m_args; //求解参数
    //求解得到的控制量
    Eigen::Matrix<float, 2, 1> m_control_command; 
    
 
public:
    nmpc_cartpole(int predict_step, float sample_time);
    ~nmpc_cartpole();
    //定义求解器
    void set_my_nmpc_solver();
    //优化求解
    void opti_solution(Eigen::Matrix<float,3,1> current_states,
                       Eigen::Matrix<float,3,1> desired_states,
                       Eigen::Matrix<float,2,1> desired_controls);
    //获取最优控制向量
    Eigen::Matrix<float,2,1> get_controls();
    //获取预测轨迹
    std::vector<Eigen::Matrix<float,3,1>> get_predict_trajectory();
 
};

#endif

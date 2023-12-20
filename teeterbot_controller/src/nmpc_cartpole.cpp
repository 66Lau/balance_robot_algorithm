#include "teeterbot_controller/nmpc_cartpole.h"


nmpc_cartpole::nmpc_cartpole(int predict_step, float sample_time)
{
    m_predict_step = predict_step;
    m_sample_time = sample_time;
    m_predict_stage = -1;
 
    n_states = 3;
    n_controls = 2;
 
    for(int j=0;j<m_predict_step;j++)
    {
        m_initial_guess.push_back(0);
        m_initial_guess.push_back(0);
    }
 
    //设置求解器
    set_my_nmpc_solver();
 
}

nmpc_cartpole::~nmpc_cartpole()
{


}

 void nmpc_cartpole::set_my_nmpc_solver()
{
    //状态量-符号变量
    casadi::SX x = casadi::SX::sym("x");
    casadi::SX q = casadi::SX::sym("q");
    casadi::SX dx = casadi::SX::sym("dx");
    casadi::SX dq = casadi::SX::sym("dq");

    //控制量-符号变量
    casadi::SX force = casadi::SX::sym("force");
    
    //vertcat意味着列向量
    casadi::SX states = casadi::SX::vertcat({x,q,dx,dq});
    casadi::SX controls = casadi::SX::vertcat({force});
 
    // std::cout<<"n_states: "<< n_states<< endl;
    // std::cout<<"n_controls: "<< n_controls<< endl;
 
    //运动学模型参数
 
    //运动学模型 Right-Hand Side 系统的导数
    casadi::SX rhs = casadi::SX::vertcat({
        dx,
        dq,
        (m*g/M)*q+(1/M)*force,
        (((m+M)*g)/(M*l))*x + (1/(M*l))*force

    });
 
    //定义模型函数，此模型是动力学方程
    casadi::Function m_f = casadi::Function("f", {states, controls}, {rhs});
 
    // 求解器--符号变量，这里的U是k个时刻的控制量，X是k个时刻的状态量
    casadi::SX U = casadi::SX::sym("U",n_controls,m_predict_step); //待求解的控制变量,n_controls行，m列
    casadi::SX X = casadi::SX::sym("X",n_states,m_predict_step+1); //系统状态，n_sates行，m+1列

    // 求解器要用到的符号变量--当前状态
    casadi::SX current_states = casadi::SX::sym("current_sattes",n_states);

    //优化参数--符号变量，一个（2*状态量个数+控制量个数）行*1列的矩阵
    //其中0-1-2是初始状态量--符号变量
    //其中3-4-5是k时刻的状态量--符号变量
    //其中6-7是k时刻的控制量--符号变量
    //（需要给出当前运动状态和预测视野内的参考轨迹,先测试定点控制,则参考轨迹可设置为期望终点）
    casadi::SX opt_para = casadi::SX::sym("opt_para",2*n_states+n_controls);

    //优化变量（需要求解的控制序列）
    //符号变量 = 转置的U = k个时刻控制量的转置
    casadi::SX opt_var = casadi::SX::reshape(U.T(),-1,1);

    //根据上述模型函数向前预测无人艇运动状态
    //Slice-切片函数，（初始索引，结束索引（不包括在内），步长）
    //这里是另X的第一列，即初始状态列等于SX opt_para的前三个状态量
    X(casadi::Slice(),0) = opt_para(casadi::Slice(0,3,1)); //状态初始值，即X的第0列等于初始状态

    //根据时序迭代，逐个时间步长迭代
    for(int i=0;i<m_predict_step;i++)
    {
        //创建一个容器，容器里面装的都是符号变量
        std::vector<casadi::SX> input_X;
        casadi::SX X_current = X(casadi::Slice(),i);
        casadi::SX U_current = U(casadi::Slice(),i);
        //将i时刻的状态和控制符号变量存入容器中
        input_X.push_back(X_current);
        input_X.push_back(U_current);
        //这里是根据模型函数滚动求解下一时刻的值，
        //注意，这里仍然是符号变量，意思是并不会在这里求出具体数值，而是定义了符号变量之间的关系，相当于生成了K个等式/方程
        //m_f是上面定义的动力学方程，这里就是X_k+1 = 动力学方程m_f(X_k，U_k)*时间间隔+X_k
        X(casadi::Slice(),i+1) = m_f(input_X).at(0)*m_sample_time+X_current;
    }
    //控制序列与输出的关系函数（预测函数）,
    //这里输入是一个U（k个时刻的状态量）将其按一列重新组合，还有opt_para（2*状态量个数+控制量个数）
    //输出是k个时刻的控制量
    m_predict_fun = casadi::Function("m_predict_fun",{casadi::SX::reshape(U,-1,1),opt_para},{X});

    //代价函数的权重矩阵，q代表状态量的误差的权重，R代表控制量的权重
    casadi::SX m_Q = casadi::SX::zeros(3,3);
    casadi::SX m_R = casadi::SX::zeros(2,2);
    m_Q(0,0) = 0.5;
    m_Q(1,1) = 0.5;
    m_Q(2,2) = 0.1;
    m_R(0,0) = 0.5;
    m_R(1,1) = 0.05;

    //符号变量cost_fun
    casadi::SX cost_fun = casadi::SX::sym("cost_fun");
    cost_fun = 0;

    int trajectory_points_index = 0;

     for(int k=0;k<m_predict_step;k++)
    {   
        //状态量的误差-符号变量-代表一个等式
        casadi::SX states_err = X(casadi::Slice(),k)-opt_para(casadi::Slice(3,6,1));
        //控制量的误差-符号变量-代表一个等式
        casadi::SX controls_err = U(casadi::Slice(),k)-opt_para(casadi::Slice(6,8,1));
        //每时刻的代价累积-符号变量-代表一个等式
        cost_fun = cost_fun+casadi::SX::mtimes({states_err.T(),m_Q,states_err})+
                            casadi::SX::mtimes({controls_err.T(),m_R,controls_err});
    }

    //构建求解器(暂时不考虑约束)
    //var变量是求解量=casadi::SX opt_var = casadi::SX::reshape(U.T(),-1,1);即k个时刻所有控制量
    //para是参数量=casadi::SX opt_para = casadi::SX::sym("opt_para",2*n_states+n_controls);
    casadi::SXDict nlp_prob = {
        {"f", cost_fun},
        {"x", opt_var},
        {"p",opt_para}
    };
 
    std::string solver_name = "ipopt";
    casadi::Dict nlp_opts;
    nlp_opts["expand"] = true;
    nlp_opts["ipopt.max_iter"] = 5000;
    nlp_opts["ipopt.print_level"] = 0;
    nlp_opts["print_time"] = 0;
    nlp_opts["ipopt.acceptable_tol"] =  1e-6;
    nlp_opts["ipopt.acceptable_obj_change_tol"] = 1e-4;
 
    m_solver = nlpsol("nlpsol", solver_name, nlp_prob, nlp_opts);


}


void nmpc_cartpole::opti_solution(Eigen::Matrix<float,3,1> current_states,
                          Eigen::Matrix<float,3,1> desired_states,
                          Eigen::Matrix<float,2,1> desired_controls)
{
    //设置控制约束
    std::vector<float> lbx;
    std::vector<float> ubx;
    std::vector<float> parameters;
    for (int k = 0; k < m_predict_step; k++)
    {
        lbx.push_back(-0.6);
 
        ubx.push_back(0.6);
    }
    for (int k = 0; k < m_predict_step; k++)
    {
        lbx.push_back(-M_PI/4);
 
        ubx.push_back(M_PI/4);
    }
    for(int j=0;j<3;j++)
    {
        parameters.push_back(current_states[j]);
    }
    for(int j=0;j<3;j++)
    {
        parameters.push_back(desired_states[j]);
    }
    for(int j=0;j<2;j++)
    {
        parameters.push_back(desired_controls[j]);
    }
    
    //求解参数设置
    m_args["lbx"] = lbx;
    m_args["ubx"] = ubx;
    m_args["x0"] = m_initial_guess;
    m_args["p"] = parameters;
    //求解
    m_res = m_solver(m_args);
 
    //获取优化变量
    std::vector<float> res_control_all(m_res.at("x"));
 
    std::vector<float> res_control_v, res_control_omega;
 
    res_control_v.assign(res_control_all.begin(), res_control_all.begin() + m_predict_step);
    res_control_omega.assign(res_control_all.begin() + m_predict_step, res_control_all.begin() + 2 * m_predict_step);
 
    //存储下一时刻最初优化猜测解
    std::vector<float> initial_guess;
    for(int j=0;j<m_predict_step-1;j++)
    {
        initial_guess.push_back(res_control_v.at(j));
    }
    initial_guess.push_back(res_control_v.at(m_predict_step-1));
    for(int j=0;j<m_predict_step-1;j++)
    {
        initial_guess.push_back(res_control_omega.at(j));
    }
    initial_guess.push_back(res_control_omega.at(m_predict_step-1));
    m_initial_guess = initial_guess;
 
    // 采用求解得到的控制序列的第一组作为当前控制量
    m_control_command << res_control_v.front(), res_control_omega.front();
 
    //预测轨迹
    // std::vector<casadi::SX> input_X;
    // input_X.push_back(res_control_all);
    // input_X.push_back(parameters);
    // m_predict_trajectory = m_predict_fun(input_X).at(0);
    // m_predict_trajectory = predict_trajectory;
    // std::cout<<"predict_trajectory: "<< predict_trajectory(1,5)<<endl; 
 
    //手动计算预测轨迹
    std::vector<Eigen::Matrix<float,3,1>> predict_X;
 
    predict_X.push_back(current_states);
    
    for(int j=0;j<m_predict_step;j++)
    {
        Eigen::Matrix<float,3,1> Next_X;
        Next_X<< m_sample_time*res_control_v.at(j)*std::cos(predict_X.at(j)[2])+predict_X.at(j)[0]
                ,m_sample_time*res_control_v.at(j)*std::sin(predict_X.at(j)[2])+predict_X.at(j)[1]
                ,m_sample_time*res_control_omega.at(j)+predict_X.at(j)[2];
        predict_X.push_back(Next_X);
 
    }
    
    m_predict_trajectory = predict_X;
 
}


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
    //状态量
    casadi::SX x = casadi::SX::sym("x");
    casadi::SX q = casadi::SX::sym("q");
    casadi::SX dx = casadi::SX::sym("dx");
    casadi::SX dq = casadi::SX::sym("dq");

    //控制量
    casadi::SX force = casadi::SX::sym("force");
 
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
 
    //定义模型函数
    casadi::Function m_f = casadi::Function("f", {states, controls}, {rhs});
 
    // 求解问题符号表示
    casadi::SX U = casadi::SX::sym("U",n_controls,m_predict_step); //待求解的控制变量,n_controls行，m列
    casadi::SX X = casadi::SX::sym("X",n_states,m_predict_step+1); //系统状态，n_sates行，m+1列

    //当前运动状态
    casadi::SX current_states = casadi::SX::sym("current_sattes",n_states);

    //优化参数（需要给出当前运动状态和预测视野内的参考轨迹,先测试定点控制,则参考轨迹可设置为期望终点）
    casadi::SX opt_para = casadi::SX::sym("opt_para",2*n_states+n_controls);

    //优化变量（需要求解的控制序列）
    //这里的 U 需要转置一下
    casadi::SX opt_var = casadi::SX::reshape(U.T(),-1,1);

    //根据上述模型函数向前预测无人艇运动状态
    X(casadi::Slice(),0) = opt_para(casadi::Slice(0,3,1)); //状态初始值，即X的第0列等于初始状态

    //根据时序迭代，逐个时间步长迭代
    for(int i=0;i<m_predict_step;i++)
    {
        std::vector<casadi::SX> input_X;
        casadi::SX X_current = X(casadi::Slice(),i);
        casadi::SX U_current = U(casadi::Slice(),i);
        input_X.push_back(X_current);
        input_X.push_back(U_current);
        //这里是根据模型函数滚动求解下一时刻的值
        X(casadi::Slice(),i+1) = m_f(input_X).at(0)*m_sample_time+X_current;
    }
    //控制序列与输出的关系函数（预测函数）
    m_predict_fun = casadi::Function("m_predict_fun",{casadi::SX::reshape(U,-1,1),opt_para},{X});

    //代价函数的权重矩阵，q代表状态量的误差的权重，R代表控制量的权重
    casadi::SX m_Q = casadi::SX::zeros(3,3);
    casadi::SX m_R = casadi::SX::zeros(2,2);
    m_Q(0,0) = 0.5;
    m_Q(1,1) = 0.5;
    m_Q(2,2) = 0.1;
    m_R(0,0) = 0.5;
    m_R(1,1) = 0.05;

    casadi::SX cost_fun = casadi::SX::sym("cost_fun");
    cost_fun = 0;

    int trajectory_points_index = 0;

     for(int k=0;k<m_predict_step;k++)
    {   
        //状态量的误差
        casadi::SX states_err = X(casadi::Slice(),k)-opt_para(casadi::Slice(3,6,1));
        //控制量的误差
        casadi::SX controls_err = U(casadi::Slice(),k)-opt_para(casadi::Slice(6,8,1));
        //每时刻的代价累积
        cost_fun = cost_fun+casadi::SX::mtimes({states_err.T(),m_Q,states_err})+
                            casadi::SX::mtimes({controls_err.T(),m_R,controls_err});
    }

    //构建求解器(暂时不考虑约束)
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

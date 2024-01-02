%% 清屏
clear
close all
clc

%% 定义变量
m = 1; %球重
M = 10; % 车重
g = 9.8;
l = 0.1;
T = 0.01 %采样周期2ms
%% 定义离散状态矩阵 A, n x n 矩阵

A = [1  0                  T  0;
     0  1                  0  T;
     0  m*g*T/M            1  0;
     0  (m*g+M*g)*T/(M*l)  0  1]



n= size (A,1);

%% 定义离散输入矩阵 B, n x p 矩阵

B = [0;
     0;
     T/M;
     T/(M*l)];

p = size(B,2)

%% 定义Q矩阵，n x n 矩阵

Q=[0.1 0   0  0;
   0   10   0  0;
   0   0   0.5  0;
   0   0   0  0.1];
Q = Q*10

%% 定义F矩阵，n x n 矩阵

F=[0.1 0   0    0;
   0   1   0    0;
   0   0   0.5  0;
   0   0   0  0.1];

%% 定义R矩阵，p x p 矩阵

R=[0];

%% 定义step数量k

k_steps=3000;

%% 定义矩阵 X_K， n x k 矩 阵

X_K = zeros(n,k_steps);


%% 初始状态变量值， n x 1 向量

X_K(:,1) =[0;0.1;0;0];

%% 定义输入矩阵 U_K， p x k 矩阵

U_K=zeros(p,k_steps);



%% 定义预测区间K

N=20;

%% Call MPC_Matrices 函数 求得 E,H矩阵 

[E,H]=MPC_Matrices(A,B,Q,R,F,N);



%% 计算每一步的状态变量的值

for k = 1 : k_steps
%% 求得U_K(:,k)

U_K(:,k) = Prediction(X_K(:,k),E,H,N,p);

%% 计算第k+1步时状态变量的值

X_K(:,k+1)=(A*X_K(:,k)+B*U_K(:,k));

end



%% 绘制状态变量和输入的变化

subplot(2, 1, 1);

hold;

for i =1 :size (X_K,1)

plot (X_K(i,:));

end

legend("x","q","dx","dq")

hold off;

subplot (2, 1, 2);

hold;

for i =1 : size (U_K,1)

plot (U_K(i,:));

end

# balance_robot_algorithm
TeeterBot is a self-balancing robot simulation model for ROS / Gazebo. The dimensions and mass of each component are easily configured using launch file arguments, so it is easy to adjust physical parameters to test robustness of control algorithms.

Besides, this repo will also provide some control algorithms like LQR/MPC for self balancing robot.

Self-balancing robot simulation model for ROS / Gazebo(using LQR/MPC) 

## Installation 
```SHELL
sudo apt install ros-noetic-hector-gazebo-plugins
sudo apt install xterm
```

```SHELL
#install 
sudo apt-get install libeigen3-dev

# because the program use <Eigen/Dense> directly, so we need to create a soft link to Eigen
sudo ln -s /usr/include/eigen3/Eigen /usr/include/Eigen
sudo ln -s /usr/include/eigen3/Eigen /usr/include/unsupported
sudo ln -s /usr/include/eigen3/Eigen /usr/include/signature_of_eigen3_matrix_library
```

```SHELL
cd $your_work_space/src
git clone git@github.com:66Lau/balance_robot_algorithm.git
cd ..
catkin_make
```

## Launch Files
There are two launch files in the `teeterbot_gazebo` package.
### `teeterbot_robot.launch`
This launch file spawns TeeterBot in Gazebo. The arguments of this launch file control the dimensions, mass, and behavior of the simulation:

- **Name and spawn pose**: These arguments set the name and initial position and heading of Teeterbot in Gazebo `world` frame. The `start_z` parameter should be equal to the wheel radius, as the origin of TeeterBot's base frame is at the focal point of its rotation.
- **Physical properties**: These arguments specify the dimensions and masses of the wheels and body of TeeterBot. 
	- `training_wheels`: Set true to spawn two invisible, frictionless spheres that prevent the robot from tipping over.
- **Simulation behavior settings**:
	- `pub_gound_truth`: set true to broadcast a TF transform from Gazebo `world` frame to TeeterBot's `base_footprint` frame.
	- `auto_reset_orientation`: set true, and the Gazebo plugin will detect when TeeterBot falls down and automatically reset it to vertical orientation.
	- `auto_reset_delay`: amount of time between detecting a fallen-over Teeterbot and when the automatic reset is performed.
- **Control mode**: Switches the control interface to TeeterBot's motors. ***Set only one of these to true***
	- `voltage_mode`: User directly controls the voltage applied to the motor
	- `torque_mode`: User issues a torque command to each motor, and the simulator internally regulates the motor current to achieve that torque.
	- `speed_mode`: User issues angular velocity commands to each motor and the simulator regulates the motor voltage inputs to achieve that command.
	
### `teeterbot_empty_world.launch`
This launch file serves as an example of how to start Gazebo, include `teeterbot_robot.launch`, and set its arguments to configure the simulation.

## Input Topics
To control TeeterBot, a separate `std_msgs/Float64` topic is advertised for each wheel. The topics are advertised in the namespace of the particular robot name specified in the `robot_name` launch file argument. However, the names of these topics are different for each control mode:

- **Voltage mode**: `<robot name>/left_motor_voltage` and `<robot name>/right_motor_voltage`
- **Torque mode**: `<robot name>/left_torque_cmd` and `<robot name>/right_torque_cmd`
- **Speed mode**: `<robot name>/left_speed_cmd` and `<robot name>/right_speed_cmd`

## Controller
To use different controller (lqr/lmpc/nmpc), you need to change the controller node in `teeterbot_controller.launch`.

- LQR  
Using matlab to get `K`, and multiple the states to get the control input.
- LMPC  
First, I build a desperate state space for cart-pole modle, and then I convert the code for initializing MPC matrices and MPC rollout prediction from matlab to CPP. The part of initializing MPC are included in `teeterbot_controller_lmpc.cpp` file, and the part of prediction will take use of function `quadprog()` in matlab, which I have converting it into the CPP code in directory `MPC_Prediction` and modified CmakeLists to make it works.
- NMPC  
	...TBD

## Usage

``` SHELL
roslaunch teeterbot_gazebo teeterbot_empty_world.launch
roslaunch teeterbot_controller teeterbot_controller.launch 
```
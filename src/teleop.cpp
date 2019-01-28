#include "teleop/teleop.hpp"
#include "std_msgs/Float32.h"

std_msgs::Float32 right_speed;
std_msgs::Float32 left_speed;
geometry_msgs::Twist cmd_vel;
ros::Publisher pubSim;


void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
	right_speed.data = msg->axes[1]*0.8;
	left_speed.data = msg->axes[4]*0.8;

	if(msg->buttons[9]==1)
		{
			//std::cout << "speed max" << std::endl;
			cmd_vel.linear.x = msg->axes[1];
			cmd_vel.angular.z = msg->axes[0];
		}
	else
		{
			cmd_vel.linear.x = msg->axes[1]/3;
			cmd_vel.angular.z = msg->axes[0]/3;
		}
	pubSim.publish(cmd_vel);
}

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "teleop");
	ros::NodeHandle n;

	ros::Subscriber subJoy = n.subscribe("/joy", 10, joyCallback);
	 pubSim = n.advertise<geometry_msgs::Twist>(argv[1], 10);
	 //ros::Publisher pubRight = n.advertise<std_msgs::Float32>("/simu_fastsim/speed_left", 10);
	 //ros::Publisher pubLeft =  n.advertise<std_msgs::Float32>("/simu_fastsim/speed_right", 10);


	ros::spin();
		
	
	
	return 0;
}

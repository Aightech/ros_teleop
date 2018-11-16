#include "teleop/teleop.hpp"

int rate = 10; //10 Hz
float linear_speed = 0.0;
float angular_speed = 0.0;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
	linear_speed = msg->axes[1];
	angular_speed = msg->axes[0];
}

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "teleop");
	ros::NodeHandle n;

	ros::Subscriber subJoy = n.subscribe("joy", 1000, joyCallback);
	ros::Publisher pubSim = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);
	ros::Rate loop_rate(rate);

	while(ros::ok())
	{
		geometry_msgs::Twist cmd_vel;
		cmd_vel.linear.x = linear_speed;
		cmd_vel.angular.z = angular_speed;
		pubSim.publish(cmd_vel);
	}

	return 0;
}

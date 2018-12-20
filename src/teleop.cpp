#include "teleop/teleop.hpp"
#include "std_msgs/Float32.h"

int rate = 10; //10 Hz
std_msgs::Float32 right_speed;
std_msgs::Float32 left_speed;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
	right_speed.data = msg->axes[1]*0.8;
	left_speed.data = msg->axes[4]*0.8;
}

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "teleop");
	ros::NodeHandle n;

	ros::Subscriber subJoy = n.subscribe("/joy", 10, joyCallback);
	ros::Publisher pubRight = n.advertise<std_msgs::Float32>("/simu_fastsim/speed_left", 10);
	ros::Publisher pubLeft =  n.advertise<std_msgs::Float32>("/simu_fastsim/speed_right", 10);
	ros::Rate loop_rate(rate);

	while(ros::ok())
	{
		ros::spinOnce();
		
		pubRight.publish(right_speed);
		pubLeft.publish(left_speed);
	}
	return 0;
}

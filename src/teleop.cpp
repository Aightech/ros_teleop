#include <teleop.hpp>

void joyCallback(const geometry_msgs::Twist& msg)
{
	
}

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "teleop");
	ros::NodeHandle n;

	ros::Subscriber subJoy = n.subscribe("joy", 1000, joyCallback);
	return 0;
}

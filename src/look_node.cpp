#include "look.h"
#include <ros/ros.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "look_node");
	Look look(argc, argv) ;
	ros::spin();
	return 0;
}

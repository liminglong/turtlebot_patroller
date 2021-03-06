#include "runaway.h"
Runaway::Runaway(int argc, char**argv):min_y_(0.1),max_y_(0.5),min_x_(-0.35),max_x_(0.35),max_z_(5)
{
	pub1 = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1000, true);
	sub1 = n.subscribe<pcl::PointCloud<pcl::PointXYZ> >("camera/depth/points", 1000, &Runaway::cloudCB, this);
}

Runaway::~Runaway()
{

}

void Runaway::cloudCB(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud)
{
    ROS_INFO("cloudCB start!");
    float x = 0.0;//X of the centroid
    float y = 0.0;//Y of the centroid
    float z = 1e6;//Z of the centroid
    unsigned int n = 0;//Number of points ovserved
    double rand_angular;
	BOOST_FOREACH (const pcl::PointXYZ& pt, cloud->points)
    {
    	if (!std::isnan(x) && !std::isnan(y) && !std::isnan(z))
      	{
        	if (-pt.y > min_y_ && -pt.y < max_y_ && pt.x < max_x_ && pt.x > min_x_ && pt.z < max_z_)
        	{
          		z = std::min(z, pt.z);
          		n++;
        	}
      	}
    }
	ROS_INFO("The distance away from you and me is: %f",z);
	if (z < 1.0)
	{
		geometry_msgs::Twist cmd;
		cmd.linear.x = -0.2;
		ROS_INFO("cmd->linear.x: ",cmd.linear.x);	
		pub1.publish(cmd);
	}
}

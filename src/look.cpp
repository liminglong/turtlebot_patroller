#include "look.h"

Look::Look(int argc, char**argv):min_y_(0.1),max_y_(0.5),min_x_(-0.35),max_x_(0.35),max_z_(5),direction(0)
{
	pub1 = n.advertise<geometry_msgs::Twist>("/look_cmd_vel", 1000, true);
	sub1 = n.subscribe<pcl::PointCloud<pcl::PointXYZ> >("camera/depth/points", 1000, &Look::cloudCB, this);
}

Look::~Look()
{

}

void Look::cloudCB(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr & cloud)
{
    ROS_INFO("cloudCB start!");
    float x = 0.0;//X of the centroid
    float y = 0.0;//Y of the centroid
    float z = 1e6;//Z of the centroid
	float goal_z = 0.5;//if shorter than the distance goal_z away from the obstacle, the kinect is blind
    unsigned int n = 0;//Number of points ovserved
	int MAX = 10;//for the random command velocity
    double rand_angular;
	geometry_msgs::Twist cmd;
	BOOST_FOREACH (const pcl::PointXYZ & pt, cloud->points)
    {
      	if (!std::isnan(x) && !std::isnan(y) && !std::isnan(z))
      	{
        	//Test to ensure the point is within the aceptable box.
       		if (-pt.y > min_y_ && -pt.y < max_y_ && pt.x < max_x_ && pt.x > min_x_ && pt.z < max_z_)
        	{
          		//Add the point to the totals
          		x += pt.x;
          		y += pt.y;
          		z = std::min(z, pt.z);
          		n++;
        	}
      	}
    }
	//if some obstacle is detected ahead, move and turn accordingly, 
	//else, simply publish a forward command.
	if (n > 4000)
	{
		x /= n;
    	y /= n;
		ROS_INFO("Obstacle ahead detected!");
		// if z-goal_z > 0, which means obstacle ahead is far enough,
		// then the robot will move forward and turn accordingly.
		if (z - goal_z > 0)
		{
			cmd.linear.x = 0.2;
			if(x > 0.2 )
			{
				direction = 1;
		        srand((unsigned)time(NULL));
				rand_angular = rand()%7;
				rand_angular = rand_angular/7.0;
				ROS_INFO(" x > 0.2  , rand_angular %f ", rand_angular);
				if(rand_angular > 0.7 && rand_angular <= 1.0 )
				{
					cmd.angular.z = 0.4;
		            ROS_INFO("rand_angular = 0.7~1.0, cmd.angular.z = %f ", cmd.angular.z );
				}
				else if(rand_angular > 0.4 && rand_angular  <= 0.7)
				{
					cmd.angular.z = rand_angular;
		            ROS_INFO("rand_angular = 0.4~0.7, cmd.angular.z = %f ", cmd.angular.z );
				}
				else
				{
					cmd.angular.z = 0.3;
		            ROS_INFO("rand_angular = 0.0~0.4, cmd.angular.z = %f ", cmd.angular.z );
				}
			}
			else if(x <- 0.2)
			{
				direction = 0;
		        srand((unsigned)time(NULL));
				rand_angular = rand()%7;
				rand_angular = double(rand_angular)/7.0 - 1.0;
				ROS_INFO(" x < -0.2  , rand_angular %f ", rand_angular);
				if(rand_angular >= -1.0 && rand_angular < -0.7 )
				{
					cmd.angular.z = -0.36;
		            ROS_INFO("rand_angular = -1.0~-0.7, cmd.angular.z = %f ", cmd.angular.z );
				}
				else if(rand_angular >= -0.7 && rand_angular  < -0.5)
				{
					cmd.angular.z = rand_angular;
		            ROS_INFO("rand_angular = -0.7~-0.4, cmd.angular.z = %f ", cmd.angular.z );
				}
				else 
				{
					cmd.angular.z = - 0.2;
		            ROS_INFO("rand_angular = -0.4~-0.0, cmd.angular.z = %f ", cmd.angular.z );
				}
						
			}
			else
			{
				if(direction)
				{
					cmd.angular.z = 0.3;
				}
				else
				{
					cmd.angular.z = -0.3;
				}
			}
			pub1.publish(cmd);
		}
		// if z-goal_z<0.6, which means obstacle ahead is too close,
		// then stop the robot from moving forward and turn accordingly.
		else
		{
			cmd.linear.x = 0;
			int num = 0;
		    double ang = 0.0;
			if(x > 0.2)
			{
		    	srand((unsigned)time(NULL));
		        num = (rand() % MAX);
		       	ang = double(num) / MAX;
		        ROS_INFO(" x > 0.2  , ang %f ", ang);
		        direction = 1 ;
				if(ang > 0.7 && ang <= 1 )
				{
					cmd.angular.z = 0.4 ;
		            ROS_INFO("ang=0.7~1.0, ancmd.angular.z = %f ", cmd.angular.z );
				}
				else if(ang > 0.4 && ang  <= 0.7)
				{
					cmd.angular.z = ang ;
		            ROS_INFO("ang=0.4~0.7, cmd.angular.z = %f ", cmd.angular.z );
				}
				else
				{
					cmd.angular.z = 0.3 ;
		            ROS_INFO("ang=0.0~0.4,cmd.angular.z = %f ", cmd.angular.z );
				}
			}
			else if(x < -0.2)
			{
		        srand((unsigned)time(NULL));
		        num = (rand() % MAX);
		        ang = double(num) / MAX ;
		        ang = ang - 1.0 ;
		    	direction = 0 ;
		        ROS_INFO(" x < -0.2  , ang %f ", ang);
		        if(ang >= -1.0 && ang < -0.7 )
				{
		        	cmd.angular.z = -0.2 ;
		            ROS_INFO("ang=-1.0~-0.7, ancmd.angular.z = %f ", cmd.angular.z );
		        }
				else if(ang >= -0.7 && ang  < -0.4)
				{
		        	cmd.angular.z = ang ;
		            ROS_INFO("ang=-0.7~-0.4, ancmd.angular.z = %f ", cmd.angular.z );
		        }
				else 
				{
		        	cmd.angular.z = - 0.2 ;
		            ROS_INFO("ang=-0.4~-0.0, ancmd.angular.z = %f ", cmd.angular.z );
		        }
			}
			else
			{
				ROS_INFO(" direction is  %d ", direction);
				if(direction)
				{
					cmd.angular.z = 0.3 ;
				}
				else
				{
					cmd.angular.z = -0.3 ;
				}
			}
			pub1.publish(cmd) ;
		}
	}
	//if no points detected just go straightly ahead
	else
	{
		cmd.linear.x = 0.2;
       	pub1.publish(cmd);
		/*
		//generate a random number from -1.0 to 1.0
		double rand_angular = 0;
		double i, s(0);
		srand((unsigned)time(NULL));
		rand_angular = rand()%7 ;
		rand_angular = rand_angular/7.0 - 0.5;
		//publish a random velocity cmd
		cmd.linear.x = 0;
		cmd.angular.z = rand_angular;
		ROS_INFO("cmd.linear.x, cmd.angular.z are: %f, %f",cmd.linear.x, cmd.angular.z);	
		pub1.publish(cmd);*/
	}
}

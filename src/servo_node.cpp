#include "ros/ros.h"
// #include "std_msgs/UInt16.h"
#include "sensor_msgs/Range.h"

#include <sstream>
int main(int argc, char **argv)
{

  ros::init(argc, argv, "servo_node");


  ros::NodeHandle n;


  ros::Publisher chatter_pub = n.advertise<sensor_msgs::Range>("servo", 1000);

  ros::Rate loop_rate(100);


  int count = 0;
  while (ros::ok())
  {
 
    sensor_msgs::Range msg;

    for(int i=75;i<=125;i++)
	{
	    msg.range = i;
	    msg.header.stamp=ros::Time::now();
	    
	    chatter_pub.publish(msg);

	    ros::spinOnce();

	    loop_rate.sleep();
	    }

    for(int i=125;i>=75;i--)
	{
	    msg.range = i ;
	    msg.header.stamp=ros::Time::now();
	    chatter_pub.publish(msg);

	    ros::spinOnce();

	    loop_rate.sleep();
	    }



  }


  return 0;
}

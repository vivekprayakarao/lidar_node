#include "ros/ros.h"
// #include "std_msgs/UInt16.h"
#include "sensor_msgs/Range.h"
#include "lidar/LidarMsg.h"
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

using namespace message_filters;
using namespace sensor_msgs;

float lidar_range=0.0;
int servo_angle=0;
float compass_angle=0.0;


ros::Publisher obst_pub;
//void callback(const Range::ConstPtr& Lidarmsg, const Range::ConstPtr& Servomsg,const Range::ConstPtr& Compassmsg)
void callback(const Range::ConstPtr& Lidarmsg, const Range::ConstPtr& Servomsg)
{
   
   lidar::LidarMsg m;
   
   lidar_range=Lidarmsg->range;
   servo_angle=Servomsg->range;
   //compass_angle=Compassmsg->range;
   
   ROS_INFO("lidar range is %f", lidar_range);
   ROS_INFO("servo angle is %d", servo_angle);
   //ROS_INFO("compass angle is %f", compass_angle);
   
   m.range=lidar_range;
   m.servo_angle=servo_angle;
   //m.field_of_view=compass_angle;
   m.stamp=ros::Time::now();
   
   obst_pub.publish(m);
  
}


int main(int argc, char **argv)
{
 

  ros::init(argc, argv, "lidarservo_node");
  
  ros::NodeHandle n;

  obst_pub = n.advertise<lidar::LidarMsg>("obstacle_data", 10);

  message_filters::Subscriber<sensor_msgs::Range> lidar_sub(n, "lidar_data", 100);
  message_filters::Subscriber<sensor_msgs::Range> servo_sub(n, "servo", 10);
 // message_filters::Subscriber<sensor_msgs::Range> compass_sub(n, "compass_data", 10);
    
       
  //  typedef sync_policies::ApproximateTime<sensor_msgs::Range, sensor_msgs::Range, sensor_msgs::Range> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  
  //typedef sync_policies::ApproximateTime<sensor_msgs::Range, sensor_msgs::Range, sensor_msgs::Range> MySyncPolicy;
  typedef sync_policies::ApproximateTime<sensor_msgs::Range, sensor_msgs::Range> MySyncPolicy;
  //Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), lidar_sub, servo_sub, compass_sub);
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), lidar_sub, servo_sub);
  
  sync.registerCallback(boost::bind(&callback, _1,_2)); 
  
  ros::spin();
   
  return 0;
}
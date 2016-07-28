#include "ros/ros.h"
#include "std_msgs/String.h"
#include "lidar/LidarMsg.h"

float32 lidar_range=0.0;
UInt16 servo_angle=0;
float32 compass_angle=0.0;


void lidarCallback(const sensor_msgs::Range::ConstPtr& msg)
{
   lidar_range=msg->Range;
   
}

void servoCallback(const std_msgs::UInt16::ConstPtr& msg)
{
   servo_angle=msg->data;
}

void compassCallback(const sensor_msgs::Range::ConstPtr& msg)
{
   compass_angle=msg->Range;
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "lidarservo_node");


  ros::NodeHandle n;


  ros::Publisher obst_pub = n.advertise<lidar::LidarMsg>("obstacle_data", 1000);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {

    std_msgs::String msg;
    LidarMsg m;
    ros::Subscriber lidar_sub = n.subscribe("lidar_data", 1000, lidarCallback);
    ros::Subscriber servo_sub = n.subscribe("servo", 1000, servoCallback);
    ros::Subscriber compass_sub = n.subscribe("compass_data", 1000, compassCallback);
    
    m.range=lidar_range;
    m.servo_angle=servo_angle;
    m.compass_angle=compass_angle;
    m.stamp=n.now();

    obst_pub.publish(msg);
    
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
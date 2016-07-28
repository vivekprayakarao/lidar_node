#include "ros/ros.h"

#include "lidar/Obst_detect.h"
#include "lidar/LidarMsg.h"

int current_servo_angle = 75;
float current_lidar_value = 0;

float cumulative_right_lidar_value = 0.0;
float cumulative_left_lidar_value = 0.0;
float cumulative_front_lidar_value = 0.0;
int count = 0;

int left_count = 0;
int front_count = 0;
int right_count = 0;

float average_right_lidar_value = 0.0;
float average_left_lidar_value = 0.0;
float average_front_lidar_value = 0.0;

int obstacle_threshold = 1000;

ros::Publisher obst_det_pub;

void obstacleCallback(const lidar::LidarMsg::ConstPtr& msg)
{
  current_servo_angle = msg->servo_angle;
  current_lidar_value = msg->range;
  
  if(current_servo_angle < 95)
  {
   cumulative_right_lidar_value = cumulative_right_lidar_value + current_lidar_value;  
   right_count++;
  }
  
  else if(current_servo_angle >= 95 && current_servo_angle <= 105 )
   {
     cumulative_front_lidar_value = cumulative_front_lidar_value + current_lidar_value;
     front_count++;
   }
  
  else if(current_servo_angle > 105)
  {
   cumulative_left_lidar_value = cumulative_left_lidar_value + current_lidar_value;
   left_count++;
        }
  
  count = front_count+left_count+right_count;
  
  if(count >= 100)
  {
  
  average_right_lidar_value = (cumulative_right_lidar_value)/right_count;
  average_left_lidar_value = (cumulative_left_lidar_value)/left_count;
  average_front_lidar_value = (cumulative_front_lidar_value)/front_count;
  
  lidar::Obst_detect m;
  
	  if(average_right_lidar_value <= obstacle_threshold)
	  {
	  m.obst_right = 1;
  
	  }
	  else
	  {
	  m.obst_right = 0;
	  }
  
	  if(average_left_lidar_value <= obstacle_threshold)
	  {
  
	  m.obst_left = 1;
  
	   }
	  else
	  {
	  m.obst_left = 0;
	  }
  
	  if(average_front_lidar_value <= obstacle_threshold)
	  {
	  m.obst_front = 1;
  
	  }
	  else
	  {
	  m.obst_front = 0;
	  }
  
  m.stamp = ros::Time::now();
  
  obst_det_pub.publish(m); 
    
  front_count = 0;
  left_count = 0;
  right_count = 0;
  
  cumulative_right_lidar_value = 0.0;
  cumulative_left_lidar_value = 0.0;
  cumulative_front_lidar_value = 0.0;
  
  }
    
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "obst_detect_node");

  ros::NodeHandle n;

  obst_det_pub = n.advertise<lidar::Obst_detect>("obstacle_detection", 1000);
  
  ros::Subscriber sub = n.subscribe("obstacle_data", 1000, obstacleCallback);

  ros::spin();
  
  return 0;
  
}
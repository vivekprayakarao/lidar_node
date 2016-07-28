# lidar_node
ROS implementation for a rangefinder and a servo working together

OBSTACLE DETECTION LAUNCH SEQUENCE

1. roscore

// Check the port number for Arduino Nano using the command 'dmesg' and modify the command below accordingly.
//The node below subscribes to topic 'servo' and publishes compass data to
// topic "compass_data" as sensors_msg::Range where the field 'range' 
// contains the orientation value of z

2. rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 


// The node below publishes servo data to topic 'servo' as sensors_msg::Range 
// where the field 'range' contains the angle of servo
 
3. rosrun lidar servodata   

// Go into the following folder catkin_ws/src/lidar/src/ and run the command below.
// In this file it is given that lidar is connected to ttyUSB1 , check to 
//make sure that the lidar is connected to the same port , if not edit the 
//file. This node publishes lidar value to the topic "lidar_data" as sensors_msg::Range 
// where the field 'range' contains the lidar value

4. python lidar_node.py 

// This node synchronizes the lidar data and servo angle and publishes to the topic
// "obstacle_data" as a custom msg given by "lidar::LidarMsg" where the fields 'range' contains the lidar value
// and 'servo_angle' contains the servo angle value

5. rosrun lidar obstdata

//This node subscribes to "obstacle_data" and publishes to the topic "obstacle_detection" as a custom msg given by
// "lidar::Obst_detect" where the fields obst_left,obst_right and obst_front denote whether there are obstacles in 
// the left,right or front respectively. The fields have the value 1 if it detects obstacle in that particular direction or
// else it has the value zero, if there are no obstacles. The threshold value for obstacle detection is 1000 mm. The range
// of servo sweep is from 75 degrees to 125 degrees where 100 degrees is the center position. The range for front obstacle detection is
// 95 to 105 degrees, for right obstacle detection it is 75 to 95 degrees and for left obstacle detection it is 105 to 125 degrees.

6.rosrun lidar obstdetect

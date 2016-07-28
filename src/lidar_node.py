#!/usr/bin/env python
# license removed for brevity
import rospy
import serial
from sensor_msgs.msg import Range


def talker():
    pub = rospy.Publisher('lidar_data', Range, queue_size=10)
    rospy.init_node('lidar_node')
    rate = rospy.Rate(1000) # 10hz
    ser=serial.Serial('/dev/ttyUSB1',115200)
    msg=Range()
    
    while not rospy.is_shutdown():
	p=ser.readline()
	if p!='\n' and p!='':
	   try:
	      msg.range=int(p)
	      msg.header.stamp = rospy.Time.now()
	      print msg.range
	      pub.publish(msg)
	   except:
	      pass   
	rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass




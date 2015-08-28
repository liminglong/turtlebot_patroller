#!/usr/bin/env python
# coding=utf-8

import rospy
import random
from geometry_msgs.msg import Twist

def main():
    rospy.init_node('wander', anonymous=True)
    pub1 = rospy.Publisher('/wander_cmd_vel', Twist, queue_size = 10)
    cmd = Twist()
    rate = rospy.Rate(5)
    while not rospy.is_shutdown():
        cmd.linear.x = 0.2
        cmd.angular.z = random.uniform(-1, 1)
        pub1.publish(cmd)
        rate.sleep()
        #print (cmd.angular.z)
if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

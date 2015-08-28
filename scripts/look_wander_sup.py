#!/usr/bin/env python
# coding=utf-8

import rospy
import time
from geometry_msgs.msg import Twist

time1 = 0.0

def lookCB(msg):  
    global time1
    print("lookCB start")
    time1 = time.time()
    pub1 = rospy.Publisher('/wander_cmd_vel', Twist, queue_size=10)
    pub1.publish(msg)    

def wanderCB(msg):
    global time1
    print("wanderCB start!")
    time2 = time.time()
    pub1 = rospy.Publisher('/wander_cmd_vel', Twist, queue_size=10)
    if (time2 - time1) > 0.5:
        pub1.publish(msg)
        print("look node broke down, wander node publish successfully!")

def main():
    rospy.init_node('look_wander_sup', anonymous=True)
    sub1 = rospy.Subscriber("/look_cmd_vel", Twist, avoidCB)
    sub2 = rospy.Subscriber("/wander_cmd_vel", Twist, runawayCB)
    rospy.spin()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

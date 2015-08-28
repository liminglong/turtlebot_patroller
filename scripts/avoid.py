#!/usr/bin/env python
#coding=utf-8

import rospy
from geometry_msgs.msg import Twist
from kobuki_msgs.msg import BumperEvent

bumper_state_flag = False #True represent 'pressed', False represent 'released'
bumper_left_flag = False
bumper_center_flag = False
bumper_right_flag = False

def bumper_eventCB(msg):
    global bumper_state_flag
    global bumper_left_flag
    global bumper_center_flag
    global bumper_right_flag
    rospy.loginfo("bumper_eventCB start")
    if msg.state == 1:
        bumper_state_flag = True
        if msg.bumper == 0:
            bumper_left_flag = True
        elif msg.bumper == 1:
            bumper_center_flag = True
        elif msg.bumper == 2:
            bumper_right_flag = True

def wander_cmd_velCB(msg):
    global bumper_state_flag
    global bumper_left_flag
    global bumper_center_flag
    global bumper_right_flag
    rospy.loginfo("wander_cmd_velCB start")
    print (bumper_state_flag)
    pub1 = rospy.Publisher('/cmd_vel_mux/input/teleop', Twist, queue_size=10)
    rate = rospy.Rate(10) # 10hz
    cmd_count = 0
    cmd = Twist()
    if bumper_state_flag == True:
        if bumper_left_flag == True:
            while not rospy.is_shutdown():
                cmd_count += 1
                cmd.angular.z = -0.4
                cmd.linear.x = -0.2
                pub1.publish(cmd)
				#print("left bumped!")
                rate.sleep()
                if cmd_count > 15:
                    bumper_left_flag = False
                    bumper_state_flag = False
                    break
        if bumper_center_flag == True:
            while not rospy.is_shutdown():
                cmd_count += 1
                cmd.angular.z = 0
                cmd.linear.x = -0.2
                pub1.publish(cmd)
				#print("center bumped!")
                rate.sleep()
                if cmd_count > 15:
                    bumper_center_flag = False
                    bumper_state_flag = False
                    break 
        if bumper_right_flag == True:
            while not rospy.is_shutdown():
                cmd_count += 1
                cmd.angular.z = 0.4
                cmd.linear.x = -0.2
                pub1.publish(cmd)
				#print("right bumped!")
                rate.sleep()
                if cmd_count > 15:
                    bumper_right_flag = False
                    bumper_state_flag = False
                    break 
    else:
        pub1.publish(msg)

def main():
    rospy.init_node('avoid', anonymous=True)
    sub1 = rospy.Subscriber("/mobile_base/events/bumper", BumperEvent, bumper_eventCB)
    sub2 = rospy.Subscriber("/wander_cmd_vel", Twist, wander_cmd_velCB)
    rospy.spin()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

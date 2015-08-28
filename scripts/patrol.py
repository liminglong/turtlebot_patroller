#! /usr/bin/env python

#import roslib; roslib.load_manifest('patroller')
import roslib
import rospy

import actionlib
from geometry_msgs.msg import PoseStamped
from std_msgs.msg import String
# brings in the messages used by the move_base action, including the
# goal message and the result message.
import turtlebot_patroller.msg

def patrol_client():
	#client = actionlib.SimpleActionClient('patrol', turtlebot_patroller.msg.MoveBaseAction)
	#client.wait_for_server()
	client = actionlib.SimpleActionClient('move_base', turtlebot_patroller.msg.MoveBaseAction)
	client.wait_for_server()
	print ("Patroller start!")
	#Make goals to send to the action server.
	goal1 = turtlebot_patroller.msg.MoveBaseGoal()
	goal1.target_pose.header.frame_id = 'map'
	goal1.target_pose.pose.position.x = 4.31624078751
	goal1.target_pose.pose.position.y = 2.01429009438
	goal1.target_pose.pose.position.z = 0.0
	goal1.target_pose.pose.orientation.x = 0.0
	goal1.target_pose.pose.orientation.y = 0.0
	goal1.target_pose.pose.orientation.z = 0.0
	goal1.target_pose.pose.orientation.w = 1	

	goal2 = turtlebot_patroller.msg.MoveBaseGoal()
	goal2.target_pose.header.frame_id = 'map'
	goal2.target_pose.pose.position.x = 7.61525249481
	goal2.target_pose.pose.position.y = 4.1121263504
	goal2.target_pose.pose.position.z = 0.0
	goal2.target_pose.pose.orientation.x = 0.0
	goal2.target_pose.pose.orientation.y = 0.0
	goal2.target_pose.pose.orientation.z = 0.699830366068
	goal2.target_pose.pose.orientation.w = 0.714309077871

	goal3 = turtlebot_patroller.msg.MoveBaseGoal()
	goal3.target_pose.header.frame_id = 'map'
	goal3.target_pose.pose.position.x = 3.03740096092
	goal3.target_pose.pose.position.y = 8.01436042786
	goal3.target_pose.pose.position.z =  0.0
	goal3.target_pose.pose.orientation.x = 0.0
	goal3.target_pose.pose.orientation.y = 0.0
	goal3.target_pose.pose.orientation.z = -0.709114237556
	goal3.target_pose.pose.orientation.w = 0.705093609455 	

	goal4 = turtlebot_patroller.msg.MoveBaseGoal()
	goal4.target_pose.header.frame_id = 'map'
	goal4.target_pose.pose.position.x = 7.75135707855
	goal4.target_pose.pose.position.y = 5.35705661774
	goal4.target_pose.pose.position.z = 0.0
	goal4.target_pose.pose.orientation.x = 0.0
	goal4.target_pose.pose.orientation.y = 0.0
	goal4.target_pose.pose.orientation.z = -0.723652451035
	goal4.target_pose.pose.orientation.w = 0.690164567412

	while not rospy.is_shutdown():
		client.send_goal(goal1)
		client.wait_for_result()

		client.send_goal(goal2)
		client.wait_for_result()

		client.send_goal(goal3)
		client.wait_for_result()

		client.send_goal(goal4)
		client.wait_for_result()

if __name__ == '__main__':
	try:
		rospy.init_node('patrol_client_py')
		patrol_client()
	except rospy.ROSInterruptException:
		print "program interrupted before completion"


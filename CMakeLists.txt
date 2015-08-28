cmake_minimum_required(VERSION 2.8.3)
project(turtlebot_patroller)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  kobuki_msgs
  roscpp
  rospy
  std_msgs
  pcl_ros
  actionlib
  actionlib_msgs
  message_generation
)
find_package(Boost REQUIRED)
find_package(PCL)

add_action_files(
  DIRECTORY action
  FILES MoveBase.action
)
generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs geometry_msgs
)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES 
  CATKIN_DEPENDS roscpp std_msgs pcl_ros kobuki_msgs actionlib_msgs
  DEPENDS PCL Boost
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(look_node src/look_node.cpp
						 src/look.cpp)

add_executable(runaway_node src/runaway_node.cpp
							src/runaway.cpp)

target_link_libraries(
   look_node
   ${catkin_LIBRARIES}
   ${PCL_LIBRARIES}
)
target_link_libraries(
   runaway_node
   ${catkin_LIBRARIES}
   ${PCL_LIBRARIES}
)

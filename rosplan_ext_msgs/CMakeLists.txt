cmake_minimum_required(VERSION 2.8.3)
project(rosplan_ext_msgs)

set(MSG_DEPS
   actionlib_msgs
   diagnostic_msgs
   std_msgs
)

set(DEPS
  message_generation
  roscpp
  rospy
  genmsg
  ${MSG_DEPS}
)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
${DEPS}
)

## Generate messages in the 'msg' folder
add_message_files(
   FILES
   Plan.msg
   PlanItem.msg
)

#add_service_files(
#  FILES
#  PlanningService.srv
#)

#add_action_files(
#  FILES
#  Plan.action
#  NonBlockingDispatch.action
#)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   ${MSG_DEPS}
)

## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS ${DEPS}
)

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

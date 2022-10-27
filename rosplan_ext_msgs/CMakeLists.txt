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

find_package(catkin REQUIRED COMPONENTS
${DEPS}
)

add_message_files(
   FILES
   Plan.msg
   PlanItem.msg
   Tree.msg
   Node.msg
   Param.msg
   ActionExecutionInfo.msg
)

add_service_files(
  FILES
  GetOrderedSubGoals.srv
  GetPlan.srv
)

add_action_files(
  FILES
  ExecutePlan.action
)

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

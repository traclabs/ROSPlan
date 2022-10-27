/**
 * @file bt_executor_node.cpp
 */
#include <ros/ros.h>
#include <rosplan_bt_executor/ExecutorNode.h>


int main(int argc, char* argv[])
{
  ros::init(argc, argv, "bt_executor_node");
  ros::NodeHandle nh;

  rosplan::ExecutorNode en(nh);
  ros::spin();

  return 0;
}

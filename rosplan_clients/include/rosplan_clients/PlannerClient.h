/**
 * @file PlannerClient.h
 * @brief Make planner requests easily
 * @author A.C. Huaman Quispe
 */

#pragma once

#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <std_msgs/String.h>

namespace rosplan
{
  
class PlannerClient
{
 public:
  PlannerClient();
  bool getPlan(std::string &_plan);
  
 protected:

  void plan_cb(const std_msgs::String::ConstPtr &_msg);
  void problem_cb(const std_msgs::String::ConstPtr &_msg);

  void reset();
  
  ros::NodeHandle pnh_;
  ros::ServiceClient client_problem_gen_;
  ros::ServiceClient client_plan_;

  ros::Subscriber sub_problem_gen_;
  ros::Subscriber sub_plan_gen_;

  bool plan_received_;
  std::string latest_plan_;
  
  bool problem_received_;
  std::string latest_problem_;

  double max_plan_wait_time_;
};

} // namespace rosplan

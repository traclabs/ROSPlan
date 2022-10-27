#pragma once

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include <rosplan_ext_msgs/Plan.h>
#include <rosplan_ext_msgs/Tree.h>
#include <rosplan_ext_msgs/GetPlan.h>
#include <rosplan_ext_msgs/GetOrderedSubGoals.h>
#include <rosplan_ext_msgs/ExecutePlanAction.h>

namespace rosplan
{

/**
 * @class ExecutorClient
 */
class ExecutorClient
{
  
 public:
  
  ExecutorClient();
  bool start_plan_execution(const rosplan_ext_msgs::Plan &_plan);
  bool execute_and_check_plan();
  void cancel_plan_execution();

  std::vector<rosplan_ext_msgs::Tree> getOrderedSubGoals();
  bool getPlan(rosplan_ext_msgs::Plan &_plan);

  rosplan_ext_msgs::ExecutePlanFeedback getFeedback() { return feedback_; }
  rosplan_ext_msgs::ExecutePlanResult getResult();
  
 protected:

  ros::NodeHandle nh_;

  // Action client
  std::shared_ptr<actionlib::SimpleActionClient<rosplan_ext_msgs::ExecutePlanAction> > action_client_;
  // Service client
  ros::ServiceClient get_ordered_sub_goals_client_;
  ros::ServiceClient get_plan_client_;

  rosplan_ext_msgs::ExecutePlanFeedback feedback_;
  rosplan_ext_msgs::ExecutePlanResult result_;
  
  bool goal_result_available_;
  bool executing_plan_;

  bool should_cancel_goal();
  void createActionClient();

  bool on_new_goal_received(const rosplan_ext_msgs::Plan &_plan);

  void result_cb(const actionlib::SimpleClientGoalState &_state,
		 const rosplan_ext_msgs::ExecutePlanResultConstPtr& _result);
  void feedback_cb(const rosplan_ext_msgs::ExecutePlanFeedbackConstPtr &_feedback);

  
};

} // namespace rosplan

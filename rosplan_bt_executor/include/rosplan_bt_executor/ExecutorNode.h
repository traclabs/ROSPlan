#pragma once

#include <rosplan_clients/DomainClient.h>
#include <rosplan_clients/ProblemClient.h>
#include <rosplan_clients/PlannerClient.h>
//#include <rosplan_bt_executor/ActionExecutor.h>

#include <rosplan_ext_msgs/ExecutePlanAction.h>

#include <lifecycle/managed_node.h>

#include <rosplan_ext_msgs/ExecutePlanAction.h>
#include <rosplan_ext_msgs/GetOrderedSubGoals.h>
#include <rosplan_ext_msgs/GetPlan.h>

#include <optional>

namespace rosplan
{

/**
 * @class ExecutorNode
 */  
class ExecutorNode : public ros::lifecycle::ManagedNode
{
 public:
  ExecutorNode(ros::NodeHandle _nh);

 protected:
  bool onActivate();
  bool onConfigure();
  bool onDeactivate();
  bool onShutdown();
  bool onCleanup();
  bool onError(const std::exception&);

  void readParams();

  void handle_goal(const rosplan_ext_msgs::ExecutePlanGoalConstPtr &_goal);
  bool get_ordered_sub_goals_cb(rosplan_ext_msgs::GetOrderedSubGoals::Request &_req,
				rosplan_ext_msgs::GetOrderedSubGoals::Response &_res);
  bool get_plan_cb(rosplan_ext_msgs::GetPlan::Request &_req,
		   rosplan_ext_msgs::GetPlan::Response &_res);

  std::string get_name() { return name_; }
  
 private:

  std::string name_;
  
  std::optional<rosplan_ext_msgs::Plan> current_plan_;
  std::optional<std::vector<rosplan_ext_msgs::Tree> > ordered_sub_goals_;
  
  std::string action_bt_xml_;

  std::shared_ptr<rosplan::DomainClient> domain_client_;
  std::shared_ptr<rosplan::ProblemClient> problem_client_;
  std::shared_ptr<rosplan::PlannerClient> planner_client_;

  // Actionlib server
  std::shared_ptr<actionlib::SimpleActionServer<rosplan_ext_msgs::ExecutePlanAction>> execute_plan_action_server_;
  // Services offered
  ros::ServiceServer get_ordered_sub_goals_srv_;
  ros::ServiceServer get_plan_srv_;
  
};

  
} // namespace rosplan

#include <rosplan_bt_executor/ExecutorNode.h>
#include <ros/package.h>
#include <fstream>

namespace rosplan
{

  ExecutorNode::ExecutorNode(ros::NodeHandle _nh)
    : ros::lifecycle::ManagedNode(_nh),
      name_("ExecutorNode")
{
  
  readParams();

  // Execute plan action server
  execute_plan_action_server_.reset(new actionlib::SimpleActionServer<rosplan_ext_msgs::ExecutePlanAction>(nh_,
													   "execute_plan",
													   boost::bind(&ExecutorNode::handle_goal, this, _1), false));
  
  execute_plan_action_server_->start();

  // GetSubGoals service
  get_ordered_sub_goals_srv_ = nh_.advertiseService("executor/get_ordered_sub_goals",
						    &ExecutorNode::get_ordered_sub_goals_cb,
						    this);
  // Get plan service
  get_plan_srv_ = nh_.advertiseService("executor/get_plan",
				       &ExecutorNode::get_plan_cb,
				       this);

}

/**
 * @function handle_goal
 */
void ExecutorNode::handle_goal(const rosplan_ext_msgs::ExecutePlanGoalConstPtr &_goal)
{
  ROS_INFO("[%s] handle_goal! ", get_name().c_str());
}

bool ExecutorNode::get_ordered_sub_goals_cb(rosplan_ext_msgs::GetOrderedSubGoals::Request &_req,
					    rosplan_ext_msgs::GetOrderedSubGoals::Response &_res)
{
  return true;
}

bool ExecutorNode::get_plan_cb(rosplan_ext_msgs::GetPlan::Request &_req,
			       rosplan_ext_msgs::GetPlan::Response &_res)
{
  return true;
}

  
/**
 * @function readParams
 */  
void ExecutorNode::readParams()
{
  
}


bool ExecutorNode::onActivate()
{
  ROS_INFO("ExecutorNode Activating...");
  //dotgraph_pub_->on_activate();
  //execution_info_pub_->on_activate();
  //executing_plan_pub_->on_activate();
  ROS_INFO("ExecutorNode Activated");

  return true;
}
  
bool ExecutorNode::onConfigure()
{
  ROS_INFO("Configuring ExecutorNode...");

  std::string default_action_bt_xml_filename;

  nh_.getParam("default_action_bt_xml_filename",
	       default_action_bt_xml_filename);

  if (default_action_bt_xml_filename.empty())
  {
    default_action_bt_xml_filename =
      ros::package::getPath("rosplan_bt_executor") +
      "/behavior_trees/rosplan_action_bt.xml";
  }

  std::ifstream ifs(default_action_bt_xml_filename);
  if (!ifs) {
    ROS_ERROR_STREAM("Error openning [" << default_action_bt_xml_filename << "]");
    return false;
  }

  action_bt_xml_.assign(
    std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
  
  /*
  dotgraph_pub_ = this->create_publisher<std_msgs::msg::String>("dot_graph", 1);
  execution_info_pub_ = create_publisher<plansys2_msgs::msg::ActionExecutionInfo>(
    "action_execution_info", 100);
  executing_plan_pub_ = create_publisher<plansys2_msgs::msg::Plan>(
    "executing_plan", rclcpp::QoS(100).transient_local());
  */
  //aux_node_ = std::make_shared<rclcpp::Node>("executor_helper");

  domain_client_ = std::make_shared<rosplan::DomainClient>();
  problem_client_ = std::make_shared<rosplan::ProblemClient>();
  planner_client_ = std::make_shared<rosplan::PlannerClient>();

  ROS_INFO( "[%s] Configured", get_name().c_str());
  return true;

}
  
bool ExecutorNode::onDeactivate()
{
  ROS_INFO("[%s] Deactivating...", get_name().c_str());
  //dotgraph_pub_->on_deactivate();
  //executing_plan_pub_->on_deactivate();
  ROS_INFO("[%s] Deactivated", get_name().c_str());

  return true;
}
  
bool ExecutorNode::onShutdown()
{
  return true;
}
  
bool ExecutorNode::onCleanup()
{
  return true;
}
  
bool ExecutorNode::onError(const std::exception&)
{
  return true;
}
  

} // namespace rosplan

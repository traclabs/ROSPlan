#include <rosplan_clients/ExecutorClient.h>

namespace rosplan
{

ExecutorClient::ExecutorClient() :
  goal_result_available_(false),
  executing_plan_(false)
{
  nh_ = ros::NodeHandle();

  createActionClient();
  
  get_ordered_sub_goals_client_ = nh_.serviceClient<rosplan_ext_msgs::GetOrderedSubGoals>("executor/get_ordered_goals");
  get_plan_client_ = nh_.serviceClient<rosplan_ext_msgs::GetPlan>("executor/get_plan");
}

void ExecutorClient::createActionClient()
{

  action_client_.reset( new actionlib::SimpleActionClient<rosplan_ext_msgs::ExecutePlanAction>("execute_plan", true)  );

  if(!action_client_->waitForServer(ros::Duration(3.0)))
    ROS_ERROR("Action server not available after waiting");

}



bool ExecutorClient::start_plan_execution(const rosplan_ext_msgs::Plan &_plan)
{
  if (!executing_plan_)
  {
    //createActionClient(); // this should be created in constructor already, right?
    bool success = on_new_goal_received(_plan);

    if(success) {
      executing_plan_ = true;
      return true;
    }
  }
  else
    ROS_INFO("Already executing a plan!");

  return false;
}


bool ExecutorClient::on_new_goal_received(const rosplan_ext_msgs::Plan &_plan)
{
  rosplan_ext_msgs::ExecutePlanGoal goal;
  goal.plan = _plan;

  action_client_->sendGoal(goal,
			   boost::bind(&ExecutorClient::result_cb, this, _1, _2),
			   actionlib::SimpleActionClient<rosplan_ext_msgs::ExecutePlanAction>::SimpleActiveCallback(),
			   boost::bind(&ExecutorClient::feedback_cb, this, _1));

  return true;
}

/**
 * @function result_cb
 */
void ExecutorClient::result_cb(const actionlib::SimpleClientGoalState &_state,
			       const rosplan_ext_msgs::ExecutePlanResultConstPtr& _result)
{
  goal_result_available_ = true;
  result_ = *_result;
  feedback_ = rosplan_ext_msgs::ExecutePlanFeedback();
}

/**
 * @function feedback_cb
 */
void ExecutorClient::feedback_cb(const rosplan_ext_msgs::ExecutePlanFeedbackConstPtr &_feedback)
{
  feedback_ = *_feedback;
}

bool ExecutorClient::execute_and_check_plan()
{
  return true;
}

void ExecutorClient::cancel_plan_execution()
{

}

std::vector<rosplan_ext_msgs::Tree> ExecutorClient::getOrderedSubGoals()
{
  std::vector<rosplan_ext_msgs::Tree> res;
  return res;
}

bool ExecutorClient::getPlan(rosplan_ext_msgs::Plan &_plan)
{
  return true;
}


rosplan_ext_msgs::ExecutePlanResult ExecutorClient::getResult()
{
  rosplan_ext_msgs::ExecutePlanResult msg;
  return msg;
}

bool ExecutorClient::should_cancel_goal()
{
  return true;
}


} // namespace rosplan

/**
 * @file PlanClient.cpp
 * @author A.C. Huaman Quispe
 */
#include <rosplan_clients/PlannerClient.h>

namespace rosplan
{

  /**
   * @function PlanClient
   * @brief Constructor
   */
  PlanClient::PlanClient() :
    pnh_("~"),
    plan_received_(false),
    problem_received_(false),
    max_plan_wait_time_(2.0)
{
  client_problem_gen_ = nh_.serviceClient<std_srvs::Empty>("/rosplan_problem_interface/problem_generation_server");
  client_plan_ = nh_.serviceClient<std_srvs::Empty>("/rosplan_planner_interface/planning_server");
  
  // Catch stuff
  sub_problem_gen_ = nh_.subscribe("/rosplan_problem_interface/problem_instance",
				   10, &PlanClient::problem_cb, this);
  sub_plan_gen_ = nh_.subscribe("/rosplan_planner_interface/planner_output",
				10, &PlanClient::plan_cb, this);  
}

void PlanClient::problem_cb(const std_msgs::String::ConstPtr &_msg)
{
  if(!_msg.data.empty())
  {
    problem_received_ = true;
    latest_problem_ = _msg.data;
  }
}

  
void PlanClient::plan_cb(const std_msgs::String::ConstPtr &_msg)
{
  if(!_msg.data.empty())
  {
    plan_received_ = true;
    latest_plan_ = _msg.data;
  }
}

void reset()
{
  plan_received_ = false;
  problem_received_ = false;
  latest_plan_ = std::string("");
  latest_problem_ = std::string("");
}
  
bool PlanClient::getPlan(std::string &_plan)
{
  reset();
  std_srvs::Empty srv;   
   
   if(!client_problem_gen_.call(srv))
     return false;
   
   if(!client_plan_.call(srv))
     return false;

   ros::Time ts = ros::Time::now();
   while(!plan_received_ &&
	 (ts - ros::Time::now()).toSec() < max_plan_wait_time_ )
   {
     usleep(0.1*e6);
   }

   bool res = plan_received_;
   if(res) 
     _plan = latest_plan_;

   reset();

   return res;
}


  
} // end namespace

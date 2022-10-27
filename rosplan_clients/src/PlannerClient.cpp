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
  PlannerClient::PlannerClient() :
    pnh_("~"),
    plan_received_(false),
    problem_received_(false),
    max_plan_wait_time_(2.0)
{
  client_problem_gen_ = pnh_.serviceClient<std_srvs::Empty>("/rosplan_problem_interface/problem_generation_server");
  client_plan_ = pnh_.serviceClient<std_srvs::Empty>("/rosplan_planner_interface/planning_server");
  
  // Catch stuff
  sub_problem_gen_ = pnh_.subscribe("/rosplan_problem_interface/problem_instance",
				   10, &PlannerClient::problem_cb, this);
  sub_plan_gen_ = pnh_.subscribe("/rosplan_planner_interface/planner_output",
				10, &PlannerClient::plan_cb, this);  
}

void PlannerClient::problem_cb(const std_msgs::String::ConstPtr &_msg)
{
  if(!_msg->data.empty())
  {
    problem_received_ = true;
    latest_problem_ = _msg->data;
  }
}

  
void PlannerClient::plan_cb(const std_msgs::String::ConstPtr &_msg)
{
  printf("Plan was received in cb!! \n");
  if(!_msg->data.empty())
  {
    plan_received_ = true;
    latest_plan_ = _msg->data;
  }
}

void PlannerClient::reset()
{
  plan_received_ = false;
  problem_received_ = false;
  latest_plan_ = std::string("");
  latest_problem_ = std::string("");
}
  
bool PlannerClient::getPlan(rosplan_ext_msgs::Plan &_plan_msg)
{
  reset();
  std_srvs::Empty srv;   
   
   if(!client_problem_gen_.call(srv))
     return false;
   
   if(!client_plan_.call(srv))
     return false;

   ros::Time ts = ros::Time::now();
   while(!plan_received_ &&
	 (ros::Time::now() - ts).toSec() < max_plan_wait_time_ )
   {
     ros::spinOnce();
     usleep(0.1*1e6);
   }

   bool res = plan_received_;
   if(res) 
   {
     parsePlan(latest_plan_, _plan_msg);

     for(auto id : _plan_msg.items)
       printf("Plan item line: %f -- %s -- %f \n",
	      id.time,
	      id.action.c_str(),
	      id.duration);
   }
   
   reset();

   return res;
}

bool PlannerClient::parsePlan(const std::string &_plan_string,
			      rosplan_ext_msgs::Plan &_msg)
{
  // Reset
  _msg.items.clear();
  
  int curr, next;
  std::string line;
  std::istringstream planfile(_plan_string);
    
  while (std::getline(planfile, line)) {
    
    if (line.length()<2)
      break;
    
    // check to see if the line looks like a planned action
    if (line.find("[", 0) == std::string::npos
	|| line.find("]", 0) == std::string::npos
	|| line.find("(", 0) == std::string::npos
	|| line.find(")", 0) == std::string::npos
	|| line.find(":", 0) == std::string::npos)
      continue;
    
    
    rosplan_ext_msgs::PlanItem item;

    // dispatchTime
    curr=line.find(":");
    double dispatchTime = (double)atof(line.substr(0,curr).c_str());
    item.time = dispatchTime;

    // Action
    curr = line.find("(");
    next = line.find(")");

    item.action = (line.substr(curr, next-curr+1)).c_str();
      
    // duration
    curr=line.find("[",curr)+1;
    next=line.find("]",curr);
    item.duration = (double)atof(line.substr(curr,next-curr).c_str());
    
    _msg.items.push_back(item);
  } // while

  return true;
}


  
} // end namespace

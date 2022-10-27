/**
 * @file run_astrobee_nav_problem.cpp
 */
#include <ros/ros.h>
#include <rosplan_clients/PlannerClient.h>
#include <rosplan_clients/DomainClient.h>
#include <rosplan_clients/ExecutorClient.h>
#include <rosplan_ext_msgs/Plan.h>

/**
 * @class RunProblem
 */
class RunProblem {

public:
  RunProblem(ros::NodeHandle _pnh)
  {
    pnh_ = _pnh;
  }

  bool init()
  {
    printf("Init..\n");
    domain_expert_ = std::make_shared<rosplan::DomainClient>();
    planner_client_ = std::make_shared<rosplan::PlannerClient>();
    executor_client_ = std::make_shared<rosplan::ExecutorClient>();
    
    rosplan_ext_msgs::Plan plan;
    if(!planner_client_->getPlan(plan))
    {
      printf("Error - Plan was not retrieved \n");
      return false;
    }

    if (!executor_client_->start_plan_execution(plan))
      printf("Error starting the obtained plan");
    
    return true;
  }

  void step()
  {

  }
  
protected:
  ros::NodeHandle pnh_;
  std::shared_ptr<rosplan::DomainClient> domain_expert_;
  std::shared_ptr<rosplan::PlannerClient> planner_client_;
  std::shared_ptr<rosplan::ExecutorClient> executor_client_;
  
  //std::shared_ptr<rosplan::ProblemExpertClient> problem_expert_;
};

/*********************************/
int main(int argc, char* argv[])
{
  ros::init(argc, argv, "run_astrobee_nav_problem");  
  ros::NodeHandle pnh("~");
  
  RunProblem runner(pnh);
  ros::Rate rate(5.0);
  
  if (!runner.init())
    return 0;

  while(ros::ok())
  {
    runner.step();
    rate.sleep();
    ros::spinOnce();
  }

  return 0;
}

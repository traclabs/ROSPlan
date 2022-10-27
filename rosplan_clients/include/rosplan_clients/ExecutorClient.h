#pragma once

#include <ros/ros.h>
#include <rosplan_ext_msgs/Plan.h>

namespace rosplan
{

class ExecutorClient
{

 public:
  ExecutorClient();
  bool start_plan_execution(const rosplan_ext_msgs::Plan &_plan);

 protected:
  
};

} // namespace rosplan

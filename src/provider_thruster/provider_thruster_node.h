//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>
#include "provider_thruster/SetThruster.h"
#include "proc_control/ThrusterEffort.h"

namespace provider_thruster {

class ProviderThrusterNode {
 public:
  //============================================================================
  // P U B L I C   C / D T O R S

  ProviderThrusterNode(ros::NodeHandlePtr &nh);

  ~ProviderThrusterNode();

 private:
  ros::NodeHandlePtr nh_;

    void thrusterEffortCallback(const proc_control::ThrusterEffort::ConstPtr& msg);

    ros::Publisher rs485Publisher;

};
}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

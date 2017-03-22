//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>

namespace provider_thruster {

class ProviderThrusterNode {
 public:
  //============================================================================
  // P U B L I C   C / D T O R S

  ProviderThrusterNode(ros::NodeHandlePtr &nh);

  ~ProviderThrusterNode();

 private:
  ros::NodeHandlePtr nh_;

};
}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

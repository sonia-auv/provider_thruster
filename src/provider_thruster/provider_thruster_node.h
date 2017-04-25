//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>
#include "provider_thruster/ThrusterEffort.h"

namespace provider_thruster {

class ProviderThrusterNode {
 public:
  //============================================================================
  // P U B L I C   C / D T O R S

  ProviderThrusterNode(ros::NodeHandlePtr &nh);

  ~ProviderThrusterNode();

    void Spin();

    uint8_t getPower(int index)
    {
        return power[index];
    }

 private:
  ros::NodeHandlePtr nh_;

    ros::Subscriber thrusterEffortSubscriber;

  void thrusterEffortCallback(const ThrusterEffort::ConstPtr& msg);

  uint8_t power[8];
  ros::Publisher rs485Publisher;

};
}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

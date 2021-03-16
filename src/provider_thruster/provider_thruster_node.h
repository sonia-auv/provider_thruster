//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>
#include <std_msgs/UInt16MultiArray.h>
#include <sonia_common/SendRS485Msg.h>

#include <string>


namespace provider_thruster {

class ProviderThrusterNode {
  
  public:

    //============================================================================
    // P U B L I C   C / D T O R S

    ProviderThrusterNode(ros::NodeHandlePtr &nh);

    ~ProviderThrusterNode();

    void Spin();

  private:
    ros::NodeHandlePtr nh_;

      ros::Subscriber thrusterPwmSubscriber;

    void thrusterPwmCallback(const std_msgs::UInt16MultiArray & msg);

    sonia_common::SendRS485Msg rs485Msg;
    ros::Publisher rs485Publisher;
    ros::Publisher effortPublisher;

    uint8_t nb_thruster = 8;
    uint16_t default_pwm = 1500;
  };
}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

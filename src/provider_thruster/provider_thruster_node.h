//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>
#include <std_msgs/UInt16MultiArray.h>
#include <sonia_common/SendRS485Msg.h>
#include <std_srvs/Empty.h>
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

    sonia_common::SendRS485Msg rs485Msg;
    ros::Publisher rs485Publisher;
    ros::Publisher effortPublisher;

    // Pour le service Dry Test.
    sonia_common::ThrusterPwm pwmsMsg;
    ros::Publisher pwmPublisher;
    ros::ServiceServer dryTestService;

    uint8_t nb_thruster = 8;
    uint16_t default_pwm = 1500;

    bool dryTestServiceCallback(std_srvs::Empty::Request & req, std_srvs::Empty::Response & resp);
    void thrusterPwmCallback(const std_msgs::UInt16MultiArray & msg);

};

}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

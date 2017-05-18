//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include <string>

namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) : nh_(nh)
    {

        thrusterEffortSubscriber = nh->subscribe("/provider_thruster/thruster_effort", 1000, &ProviderThrusterNode::thrusterEffortCallback, this);

        this->rs485Publisher = nh->advertise<interface_rs485::SendRS485Msg>("/interface_rs485/dataRx", 1000);

        rs485Msg.cmd = interface_rs485::SendRS485Msg::CMD_ISI_power;
        rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;
        for(uint8_t i = 0; i < 8; i++) {
          power[i] = 100;
        }

    }

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::~ProviderThrusterNode() { }

    void ProviderThrusterNode::Spin()
    {
        ros::Rate r(10); // 10 Hz

        while (ros::ok())
        {
          ros::spinOnce();
          publishLastCommand();
          r.sleep();
        }
    }

    //------------------------------------------------------------------------------
    //
    void ProviderThrusterNode::publishLastCommand()
    {
      rs485Msg.data.clear();
      for(uint8_t i = 0; i < 8; i++) {
        rs485Msg.data.push_back(power[i]);
      }
      rs485Publisher.publish(rs485Msg);
    }

    //------------------------------------------------------------------------------
    //
    void ProviderThrusterNode::thrusterEffortCallback(const ThrusterEffort::ConstPtr& msg)
    {
        ROS_DEBUG("Message received : {ID: %u, effort: %i}", msg->ID, msg->effort);

        rs485Msg.cmd = interface_rs485::SendRS485Msg::CMD_ISI_power;

        int effort = msg->effort;

        if (effort < -100) {
          power[msg->ID - 1] = 0;
        }
        else if (effort > 100) {
          power[msg->ID - 1] = 200;
        }
        else {
          power[msg->ID - 1] = effort + 100;
        }

      rs485Msg.data.clear();
      for(uint8_t i = 0; i < 8; i++) {
        rs485Msg.data.push_back(power[i]);
      }

      rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;

      rs485Publisher.publish(rs485Msg);

    }
}





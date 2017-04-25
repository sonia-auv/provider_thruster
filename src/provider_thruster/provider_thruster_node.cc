//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include <string>
#include "interface_rs485/SendRS485Msg.h"

namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) : nh_(nh)
    {

        ros::Subscriber subscriber = nh->subscribe("/provider_thruster/thruster_effort", 1000, &ProviderThrusterNode::thrusterEffortCallback, this);

        this->rs485Publisher = nh->advertise<interface_rs485::SendRS485Msg>("/interface_rs485/dataRx", 1000);

        for(uint8_t i = 0; i < 8; i++) {
          power[i] = 100;
        }

        ros::Rate r(14); // 14 Hz

        while (ros::ok())
        {
            ros::spinOnce();
            r.sleep();
        }

    }

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::~ProviderThrusterNode() { }

    void ProviderThrusterNode::thrusterEffortCallback(const ThrusterEffort::ConstPtr& msg)
    {
        // Traitement du message à faire ici
        ROS_DEBUG("Message received : {ID: %u, effort: %i}", msg->ID, msg->effort);

        interface_rs485::SendRS485Msg rs485Msg;
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

      for(uint8_t i = 0; i < 8; i++) {
        rs485Msg.data.push_back(power[i]);
      }

      rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;

      this->rs485Publisher.publish(rs485Msg);

    }
}





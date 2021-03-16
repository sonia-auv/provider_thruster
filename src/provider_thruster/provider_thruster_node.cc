//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include <iostream>
#include <fstream>
#include <vector>


namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) :
        nh_(nh)
    {
        thrusterPwmSubscriber = nh->subscribe("/provider_thruster/thruster_pwm", 100, &ProviderThrusterNode::thrusterPwmCallback, this);

        this->rs485Publisher = nh->advertise<sonia_common::SendRS485Msg>("/interface_rs485/dataRx", 1000);
    }

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::~ProviderThrusterNode() { }

    void ProviderThrusterNode::Spin()
    {
        ros::Rate r(100); // 100 Hz

        while (ros::ok())
        {
          ros::spinOnce();
          r.sleep();
        }
    }
    //------------------------------------------------------------------------------
    //
    void ProviderThrusterNode::thrusterPwmCallback(const std_msgs::UInt16MultiArray & msg)
    {
        rs485Msg.cmd = sonia_common::SendRS485Msg::CMD_ISI_power;
        rs485Msg.data.clear();

        for(uint8_t i=0; i<nb_thruster; ++i)
        {
            rs485Msg.data.push_back(msg.data[i]>>8);
            rs485Msg.data.push_back(msg.data[i] & 0xFF);
        }

        rs485Msg.slave = sonia_common::SendRS485Msg::SLAVE_ISI_PWM;
        rs485Publisher.publish(rs485Msg);
    }
}






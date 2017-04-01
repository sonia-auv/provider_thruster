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
        u_char power = 0;

        if (effort < -100)
            power = 0;
        else if (effort > 100)
            power = 200;
        else
            power = effort + 100;


        rs485Msg.data.push_back(power);

        switch (msg->ID)
        {
            case ThrusterEffort::UNIQUE_ID_T1:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_0;
                break;
            case ThrusterEffort::UNIQUE_ID_T2:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_1;
                break;
            case ThrusterEffort::UNIQUE_ID_T3:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_2;
                break;
            case ThrusterEffort::UNIQUE_ID_T4:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_3;
                break;
            case ThrusterEffort::UNIQUE_ID_T5:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_4;
                break;
            case ThrusterEffort::UNIQUE_ID_T6:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_5;
                break;
            case ThrusterEffort::UNIQUE_ID_T7:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_6;
                break;
            case ThrusterEffort::UNIQUE_ID_T8:
                rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_7;
                break;

        }


        this->rs485Publisher.publish(rs485Msg);

    }
}





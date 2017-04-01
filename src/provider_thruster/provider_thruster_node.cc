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

        ros::Subscriber subscriber = nh->subscribe("ThrusterEffort", 1000, &ProviderThrusterNode::thrusterEffortCallback, this);

        this->rs485Publisher = nh->advertise<SetThruster>("SetThruster", 1000);

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

    void ProviderThrusterNode::thrusterEffortCallback(const proc_control::ThrusterEffort::ConstPtr& msg)
    {

        //bool estT1 = msg->ID == proc_control::ThrusterEffort::UNIQUE_ID_T1;

        // Traitement du message à faire ici
        ROS_INFO("Message recu : {name: %u, value: %i}", msg->ID, msg->effort);

        SetThruster thrusterMessage;

        switch (msg->ID)
        {
            case proc_control::ThrusterEffort::UNIQUE_ID_T1:
                thrusterMessage.name = "T1";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T2:
                thrusterMessage.name = "T2";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T3:
                thrusterMessage.name = "T3";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T4:
                thrusterMessage.name = "T4";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T5:
                thrusterMessage.name = "T5";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T6:
                thrusterMessage.name = "T6";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T7:
                thrusterMessage.name = "T7";
                break;
            case proc_control::ThrusterEffort::UNIQUE_ID_T8:
                thrusterMessage.name = "T8";
                break;

        }

        thrusterMessage.value = msg->effort;

        this->rs485Publisher.publish(thrusterMessage);

    }
}





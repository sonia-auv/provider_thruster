//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include "provider_thruster/SetThruster.h"
#include <string>
#include "interface_rs485/SendRS485Msg.h"

namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) : nh_(nh)
    {

        ros::Subscriber subscriber = nh->subscribe("SetThruster", 1000, &ProviderThrusterNode::setThrusterCallback, this);

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

    void ProviderThrusterNode::setThrusterCallback(const provider_thruster::SetThruster::ConstPtr& msg)
    {

        ROS_INFO("Message recu : {name: %s, value: %i}",msg->name.c_str(), msg->value);

        // Traitement du message à faire ici

        

    }
}





//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include "provider_thruster/SetThruster.h"

namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) : nh_(nh)
    {

        // Procéder à 14 Hz

        auto patate = nh->subscribe("SetThruster", 1000, &ProviderThrusterNode::setThrusterCallback, this);

        ros::spin();

    }

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::~ProviderThrusterNode() { }

    void ProviderThrusterNode::setThrusterCallback(const provider_thruster::SetThruster::ConstPtr& msg)
    {
        ROS_INFO("Message recu");
    }
}





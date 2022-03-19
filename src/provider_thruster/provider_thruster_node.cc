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
        dryTestService = nh->advertiseService("/provider_thruster/dry_test", &ProviderThrusterNode::dryTestServiceCallback, this);
        pwmPublisher = nh->advertise<std_msgs::UInt16MultiArray>("/provider_thruster/thruster_pwm", 1000);
        

        this->rs485Publisher = nh->advertise<sonia_common::SendRS485Msg>("/interface_rs485/dataRx", 1000);

        const char* auv = std::getenv("AUV");

        if (strcmp(auv, "AUV8") == 0){
            SLAVE = sonia_common::SendRS485Msg::SLAVE_ESC;    
        }

        else if (strcmp(auv, "AUV7") == 0){
            SLAVE = sonia_common::SendRS485Msg::SLAVE_PWR_MANAGEMENT;
        }

        else if (strcmp(auv, "LOCAL") == 0){
            SLAVE = sonia_common::SendRS485Msg::SLAVE_PWR_MANAGEMENT;
        }
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
        rs485Msg.slave = SLAVE;
        rs485Msg.cmd = sonia_common::SendRS485Msg::CMD_PWM;
        rs485Msg.data.clear();

        for(uint8_t i=0; i<nb_thruster; ++i)
        {
            rs485Msg.data.push_back(msg.data[i]>>8);
            rs485Msg.data.push_back(msg.data[i] & 0xFF);
        }

        rs485Publisher.publish(rs485Msg);
    }

    bool ProviderThrusterNode::dryTestServiceCallback(std_srvs::Empty::Request & req, std_srvs::Empty::Response & resp)
    {
        std::vector<uint16_t> vect = {default_pwm, default_pwm, default_pwm, default_pwm, default_pwm, default_pwm, default_pwm, default_pwm};
        std_msgs::UInt16MultiArray pwmsMsg;
        pwmsMsg.data.clear();
        pwmsMsg.data.insert(pwmsMsg.data.end(), vect.begin(), vect.end());
        
        for(uint8_t i=0; i < nb_thruster; ++i)
        {
            pwmsMsg.data[i] = dryTestPwm;
            pwmPublisher.publish(pwmsMsg);
            thrusterPwmCallback(pwmsMsg);
            ros::Duration(dryTestOnTime).sleep();
            pwmsMsg.data[i] = default_pwm;
            pwmPublisher.publish(pwmsMsg);
            thrusterPwmCallback(pwmsMsg);
            ros::Duration(dryTestDelay).sleep();
        }
        return true;
    }
}






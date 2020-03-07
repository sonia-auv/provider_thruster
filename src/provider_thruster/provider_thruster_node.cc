//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) :
        nh_(nh),
        motors_out(8,1),
        motors_in(8, 1),
        fichier{"T1","T2","T3","T4","T5","T6","T7","T8"},
        calcul(8,6)
    {

        int j=0;
        for(auto&t : fichier){
            std::vector<double> value;
            ros::param::get("/provider_thruster/" + t, value);

            for (uint8_t i = 0; i < 6; i++) {
                calcul(j,i) = value[i];
            }

            j++;
        }


        thrusterEffortSubscriber = nh->subscribe("/provider_thruster/thruster_effort", 1000, &ProviderThrusterNode::thrusterEffortCallback, this);
        effortSubscriber = nh->subscribe("/provider_thruster/thruster_effort_vector", 1000, &ProviderThrusterNode::thrusterVectorEffortCallback, this);

        this->rs485Publisher = nh->advertise<interface_rs485::SendRS485Msg>("/interface_rs485/dataRx", 1000);
        effortPublisher = nh->advertise<ThrusterEffort>("/provider_thruster/effort", 1000);

        rs485Msg.cmd = interface_rs485::SendRS485Msg::CMD_ISI_power;
        rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;
        for(uint8_t i = 0; i < 8; i++) {
            motors_out[i] = 100;
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
        rs485Msg.data.push_back(motors_out[i]);
      }
      rs485Publisher.publish(rs485Msg);
    }

    //------------------------------------------------------------------------------
    // This is the code used when proc_control sends a command
    void ProviderThrusterNode::thrusterVectorEffortCallback(const geometry_msgs::Wrench & msg)
    {
        ThrusterEffort effortMsg;

        rs485Msg.cmd = interface_rs485::SendRS485Msg::CMD_ISI_power;

        vecteur[0]=msg.force.x;
        vecteur[1]=msg.force.y;
        vecteur[2]=msg.force.z;
        vecteur[3]=msg.torque.x;
        vecteur[4]=msg.torque.y;
        vecteur[5]=msg.torque.z;

        motors_in = calcul * vecteur;

        rs485Msg.data.clear();
        for(uint8_t j=0;j<8;j++) {

            if (motors_in [j] <-35) {
                motors_out[j] = 65;

            } else if (motors_in[j] > 35) {
                motors_out[j] = 135;

            } else {
                motors_out[j] = motors_in[j] + 100;
            }
            rs485Msg.data.push_back(motors_out[j]);
            
            effortMsg.ID = j+1;
            effortMsg.effort = motors_out[j]-100;
            effortPublisher.publish(effortMsg);
        }

      rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;

      rs485Publisher.publish(rs485Msg);

    }


    //This code is mainly used for dry_test

    void ProviderThrusterNode::thrusterEffortCallback(const ThrusterEffort& msg)
    {
        ROS_DEBUG("Message received : {ID: %u, effort: %i}", msg.ID, msg.effort);

        rs485Msg.cmd = interface_rs485::SendRS485Msg::CMD_ISI_power;

        ThrusterEffort motor_out;

        if (msg.effort < -35) {
            motor_out.effort = 65;
        }
        else if (msg.effort > 35) {
            motor_out.effort = 135;
        }
        else {
            motor_out.effort = msg.effort + 100;
        }

        motors_out[msg.ID - 1] = motor_out.effort;
        motor_out.effort -= 100;
        motor_out.ID = msg.ID;

        rs485Msg.data.clear();
        for(uint8_t i = 0; i < 8; i++) {
            rs485Msg.data.push_back(motors_out[i]);
        }

        rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;

        rs485Publisher.publish(rs485Msg);
        effortPublisher.publish(motor_out);

    }
}






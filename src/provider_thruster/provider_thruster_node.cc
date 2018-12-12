//
// Created by bullshark on 3/21/17.
//

#include "provider_thruster/provider_thruster_node.h"
#include <string>
#include <iostream>
#include <fstream>

namespace provider_thruster {

    //==============================================================================
    // C / D T O R S   S E C T I O N

    //------------------------------------------------------------------------------
    //
    ProviderThrusterNode::ProviderThrusterNode(ros::NodeHandlePtr &nh) :
        nh_(nh),
        fichier{"T1","T2","T3","T4","T5","T6","T7","T8"},
        calcul(8,6)
    {

        YAML::Node node = YAML::LoadFile(file_path_);

        int j=0;
        for(auto&t : fichier){
            auto thruster = node[t];
            assert(thruster.Type() == YAML::NodeType::Sequence);
           // std::array<double, 6> force_array = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            for (uint8_t i = 0; i < 6; i++) {
                calcul(j,i) = thruster[i].as<double>();
            }

            j++;
        }


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
    void ProviderThrusterNode::thrusterEffortCallback(const geometry_msgs::Wrench & msg)
    {

        rs485Msg.cmd = interface_rs485::SendRS485Msg::CMD_ISI_power;

        vecteur[0]=msg.force.x;
        vecteur[1]=msg.force.y;
        vecteur[2]=msg.force.z;
        vecteur[3]=msg.torque.x;
        vecteur[4]=msg.torque.y;
        vecteur[5]=msg.torque.z;

        motors_in = calcul*vecteur;

        rs485Msg.data.clear();
        for(uint8_t j=0;j<8;j++) {

            if (motors_in [j] <-100) {
                motors_out[j] = 0;

            } else if (motors_in[j] > 100) {
                motors_out[j] = 200;

            } else {
                motors_out[j] = motors_in[j] + 100;
            }
            rs485Msg.data.push_back(motors_out(j,1));
        }

      rs485Msg.data.clear();


      rs485Msg.slave = interface_rs485::SendRS485Msg::SLAVE_ISI_PWM;

      rs485Publisher.publish(rs485Msg);

    }
}





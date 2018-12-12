//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>
#include <geometry_msgs/Wrench.h>
#include "provider_thruster/ThrusterEffort.h"
#include "interface_rs485/SendRS485Msg.h"
#include <eigen3/Eigen/Eigen>
#include <yaml-cpp/yaml.h>
#include <string>


namespace provider_thruster {

class ProviderThrusterNode {
 public:

    typedef Eigen::Matrix<double, Eigen::Dynamic,6>  MatrixXd;
    typedef Eigen::Matrix<uint8_t , Eigen::Dynamic,1>  motor_output;
    typedef Eigen::Matrix<double , Eigen::Dynamic,1>  motor_input;
    typedef Eigen::Matrix<double, 6,1>  Vector6d;
    typedef std::vector<std::string> tab_string;
  //============================================================================
  // P U B L I C   C / D T O R S



  ProviderThrusterNode(ros::NodeHandlePtr &nh);

  ~ProviderThrusterNode();

    void Spin();

    uint8_t getPower(int index)
    {
        return power[index];
    }

 private:
  ros::NodeHandlePtr nh_;

    ros::Subscriber thrusterEffortSubscriber;

  void thrusterEffortCallback(const ThrusterEffort::ConstPtr& msg);
  void thrustervectoreffortCallback(const geometry_msgs::Wrench & msg);
  void publishLastCommand();


  interface_rs485::SendRS485Msg rs485Msg;
  uint8_t power[8];
  ros::Publisher rs485Publisher;

  const std::string file_path_ = std::string(std::getenv("ROS_SONIA_WS") ) + "/src" + "/provider_thruster" + "/config" + "/thruster.yaml";
  motor_output motors_out;
  motor_input motors_in;
  tab_string fichier;
  MatrixXd calcul;
  Vector6d vecteur;


};
}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

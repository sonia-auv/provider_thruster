//
// Created by bullshark on 3/21/17.
//

#ifndef PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H
#define PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

#include <ros/ros.h>
#include <geometry_msgs/Wrench.h>
#include <sonia_common/ThrusterEffort.h>
#include <sonia_common/SendRS485Msg.h>
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
        return motors_out[index];
    }

 private:
  ros::NodeHandlePtr nh_;

    ros::Subscriber thrusterEffortSubscriber;
    ros::Subscriber effortSubscriber;

  void thrusterEffortCallback(const sonia_common::ThrusterEffort& msg);
  void thrustervectoreffortCallback(const geometry_msgs::Wrench & msg);
  void publishLastCommand();


  sonia_common::SendRS485Msg rs485Msg;
  ros::Publisher rs485Publisher;
  ros::Publisher effortPublisher;

  motor_output motors_out;
  motor_input motors_in;
  tab_string fichier;
  MatrixXd calcul;
  Vector6d vecteur;


};
}  // namespace provider_thruster

#endif //PROVIDER_THRUSTER_PROVIDER_THRUSTER_NODE_H

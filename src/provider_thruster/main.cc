
// ROS includes
#include "ros/ros.h"
#include "provider_thruster/provider_thruster_node.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "provider_thruster_node");
  ros::NodeHandlePtr nh(new ros::NodeHandle("~"));
  provider_thruster::ProviderThrusterNode ptn(nh);
  ptn.Spin();

  return 0;
}

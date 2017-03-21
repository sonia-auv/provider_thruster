
// ROS includes
#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "provider_sonar_node");
  ros::NodeHandlePtr nh(new ros::NodeHandle("~"));

    std::cout << "Hello World!";

  return 0;
}

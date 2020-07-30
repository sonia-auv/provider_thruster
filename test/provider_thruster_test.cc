//
// Created by coumarc9 on 4/11/17.
//

#include <gtest/gtest.h>
#include <sonia_common/ThrusterEffort.h>
#include <provider_thruster/provider_thruster_node.h>
#include "ros/ros.h"

class ThrusterEffortMock
{
public:

    ThrusterEffortMock(ros::NodeHandlePtr &nh): nh(nh)
    {
        thrusterEffortPublisher = nh->advertise<sonia_common::ThrusterEffort>("/provider_thruster/thruster_effort", 1000);
    }
    ~ThrusterEffortMock()
    {

    }

    // Test with minimum values
    void initializeMockTest1()
    {

        sonia_common::ThrusterEffort message1;

        message1.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T1;
        message1.effort = -120;

        messages.push_back(message1);

        sonia_common::ThrusterEffort message2;

        message2.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T2;
        message2.effort = -101;

        messages.push_back(message2);

        sonia_common::ThrusterEffort message3;

        message3.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T3;
        message3.effort = -100;

        messages.push_back(message3);

        sonia_common::ThrusterEffort message4;

        message4.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T4;
        message4.effort = -100;

        messages.push_back(message4);

        sonia_common::ThrusterEffort message5;

        message5.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T5;
        message5.effort = -100;

        messages.push_back(message5);

        sonia_common::ThrusterEffort message6;

        message6.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T6;
        message6.effort = -100;

        messages.push_back(message6);

        sonia_common::ThrusterEffort message7;

        message7.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T7;
        message7.effort = -100;

        messages.push_back(message7);

        sonia_common::ThrusterEffort message8;

        message8.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T8;
        message8.effort = -100;

        messages.push_back(message8);

    }

    // Test with values in range
    void initializeMockTest2()
    {

        sonia_common::ThrusterEffort message1;

        message1.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T1;
        message1.effort = -99;

        messages.push_back(message1);

        sonia_common::ThrusterEffort message2;

        message2.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T2;
        message2.effort = -75;

        messages.push_back(message2);

        sonia_common::ThrusterEffort message3;

        message3.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T3;
        message3.effort = -50;

        messages.push_back(message3);

        sonia_common::ThrusterEffort message4;

        message4.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T4;
        message4.effort = 0;

        messages.push_back(message4);

        sonia_common::ThrusterEffort message5;

        message5.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T5;
        message5.effort = 25;

        messages.push_back(message5);

        sonia_common::ThrusterEffort message6;

        message6.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T6;
        message6.effort = 50;

        messages.push_back(message6);

        sonia_common::ThrusterEffort message7;

        message7.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T7;
        message7.effort = 75;

        messages.push_back(message7);

        sonia_common::ThrusterEffort message8;

        message8.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T8;
        message8.effort = 99;

        messages.push_back(message8);

    }

    // Test with maximum values
    void initializeMockTest3()
    {

        sonia_common::ThrusterEffort message1;

        message1.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T1;
        message1.effort = 100;

        messages.push_back(message1);

        sonia_common::ThrusterEffort message2;

        message2.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T2;
        message2.effort = 101;

        messages.push_back(message2);

        sonia_common::ThrusterEffort message3;

        message3.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T3;
        message3.effort = 102;

        messages.push_back(message3);

        sonia_common::ThrusterEffort message4;

        message4.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T4;
        message4.effort = 110;

        messages.push_back(message4);

        sonia_common::ThrusterEffort message5;

        message5.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T5;
        message5.effort = 150;

        messages.push_back(message5);

        sonia_common::ThrusterEffort message6;

        message6.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T6;
        message6.effort = 100;

        messages.push_back(message6);

        sonia_common::ThrusterEffort message7;

        message7.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T7;
        message7.effort = 100;

        messages.push_back(message7);

        sonia_common::ThrusterEffort message8;

        message8.ID = sonia_common::ThrusterEffort::UNIQUE_ID_T8;
        message8.effort = 100;

        messages.push_back(message8);

    }


    void publish()
    {
        for (uint8_t i = 0; i < messages.size(); ++i) {
            thrusterEffortPublisher.publish(messages[i]);
        }

    }

private:

    ros::NodeHandlePtr nh;

    ros::Publisher thrusterEffortPublisher;

    std::vector<sonia_common::ThrusterEffort> messages;

};

TEST(Suite, testMinimumValues) {

    ros::NodeHandlePtr nh(new ros::NodeHandle("~"));

    ThrusterEffortMock mock(nh);

    provider_thruster::ProviderThrusterNode node(nh);

    ros::Rate loop_rate(1);

    mock.initializeMockTest1();
    mock.publish();

    loop_rate.sleep();

    ros::spinOnce();

    for (int i = 0; i < 8; ++i) {

        auto power = node.getPower(i);
        ASSERT_EQ(power, 0);
    }

}

TEST(Suite, testValuesInRange) {

    ros::NodeHandlePtr nh(new ros::NodeHandle("~"));

    ThrusterEffortMock mock(nh);

    provider_thruster::ProviderThrusterNode node(nh);

    ros::Rate loop_rate(1);

    mock.initializeMockTest2();
    mock.publish();

    loop_rate.sleep();

    ros::spinOnce();

    uint8_t values[8] = {1, 25,50,100,125,150, 175,199};

    for (int i = 0; i < 8; ++i) {

        auto power = node.getPower(i);
        ASSERT_EQ(power, values[i]);
    }

}

TEST(Suite, testMaximumValues) {

    ros::NodeHandlePtr nh(new ros::NodeHandle("~"));

    ThrusterEffortMock mock(nh);

    provider_thruster::ProviderThrusterNode node(nh);

    ros::Rate loop_rate(1);

    mock.initializeMockTest3();
    mock.publish();

    loop_rate.sleep();

    ros::spinOnce();

    for (int i = 0; i < 8; ++i) {

        auto power = node.getPower(i);
        ASSERT_EQ(power, 200);
    }

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    ros::init(argc, argv, "provider_thruster_node");
    // Mettre dans tous les tests
    // ros::NodeHandlePtr nh(new ros::NodeHandle("~"));
    return RUN_ALL_TESTS();
}
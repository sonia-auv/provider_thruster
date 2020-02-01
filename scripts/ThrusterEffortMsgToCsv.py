#!/usr/bin/env python

import rospy
import os
from provider_thruster.msg import ThrusterEffort


class ThrusterEffortMsgToCsv:

    def __init__(self):

        home = os.path.expanduser("~")

        self.csv_file = open(home + "/parse.csv", "w")

        self.write_header()

        rospy.init_node("provider_thruster_effort_csv")

        self.subscriber = rospy.Subscriber("/provider_thruster/effort", ThrusterEffort, self.callback)

        self.loop()

    def loop(self):

        rate = rospy.Rate(100)

        while not rospy.is_shutdown():
            rate.sleep()

        self.csv_file.close()

    def write_header(self):
        self.write_line("ID;effort")

    def write_line(self, line):
        self.csv_file.write(line + "\n")


    def callback(self, object):

        ID = object.ID
        effort = object.effort

        elements = [ID, effort]

        line = ';'.join(map(str, elements))

        self.write_line(line)



if __name__ == "__main__":
    element = ThrusterEffortMsgToCsv()

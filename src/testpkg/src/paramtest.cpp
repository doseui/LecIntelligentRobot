#include "ros/ros.h"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "param_test");
    ros::NodeHandle n;

    double param1;
    std::string name;
    bool paramBool;

    n.getParam("/param1", param1);
    n.getParam("/name", name);
    n.getParam("param_bool", paramBool);

    ROS_INFO("param1 : %lf", param1);
    ROS_INFO("name : %s", name.c_str());
    ROS_INFO("param_bool : %d" ,paramBool);
}
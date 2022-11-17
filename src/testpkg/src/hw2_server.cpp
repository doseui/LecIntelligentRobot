// hw2_server.cpp
#include "ros/ros.h"
#include "testpkg/hw2_srv.h"

#define CONST_PI 3.141592


bool CalcArea(testpkg::hw2_srv::Request &req,
         testpkg::hw2_srv::Response &res)
{
    res.area = req.radius * req.radius * CONST_PI;
    ROS_INFO("request: radius=%ld", (long int)req.radius);
    ROS_INFO("sending back response: [%lf]", (double)res.area);

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "hw2_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("CircleArea", CalcArea);
    
    ROS_INFO("Ready to calc circle area.");
    ros::spin();

    return 0;
}
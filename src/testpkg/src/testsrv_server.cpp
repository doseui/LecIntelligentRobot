// testsrv_server.cpp
#include "ros/ros.h"
#include "testpkg/testsrv.h"

bool add(testpkg::testsrv::Request &req,
         testpkg::testsrv::Response &res)
{
    // res.sum = req.a + req.b;
    // ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
    res.sum = req.a + req.b;
    ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
    ROS_INFO("sending back response: [%ld]", (long int)res.sum);

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "testsrv_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("add_two_ints", add);
    
    ROS_INFO("Ready to add two ints.");
    ros::spin();

    return 0;
}
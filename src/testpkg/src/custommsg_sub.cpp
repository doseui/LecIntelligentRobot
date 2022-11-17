#include "ros/ros.h"
#include "testpkg/testmsg.h"
#include <iostream>

void msgCallback(const testpkg::testmsg::ConstPtr& msg)
{
    std::cout << "callback!\n";
    std::cout << "msg->header.frame_id " << msg->header.frame_id << "\n";
    std::cout << "msg->header.seq " << msg->header.seq << "\n";
    std::cout << "msg->header.stamp " << msg->header.stamp << "\n";
    std::cout << "msg->x " << msg->x << "\n";
    std::cout << "msg->y " << msg->y << "\n";

    for (int i = 0; i < msg->testarray.size(); i++)
    {
        std::cout << " " << msg->testarray.at(i);
    }

    std::cout << std::endl;
}


int main(int argc, char **argv)
{ 
    ros::init(argc, argv, "custommsg_sub");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("custommsg", 1000, msgCallback);
    ros::spin();

    return 0;
}
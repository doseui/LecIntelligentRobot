#include "ros/ros.h"
#include "testpkg/testmsg.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

std::vector<int> storedVector;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "custommsg_pub");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<testpkg::testmsg>("custommsg",1);
    ros::Rate loop_rate(10); // hz

    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        storedVector.push_back(i);  // 멤버함수 push_back : 벡터의 끝에 새로운 element를 추가한다.
    }                               // 여기서는 {0,1,2,3,4}를 만든다

    while(ros::ok())
    {
        testpkg::testmsg pub_data;
        pub_data.header.frame_id = "/map";
        pub_data.header.seq = count;
        pub_data.header.stamp = ros::Time::now();
        pub_data.x = 10;
        pub_data.y = 20;
        storedVector.push_back(count*2);    // 새로운 element 추가
        storedVector.erase(storedVector.begin());   // 시작 element를 제거
        pub_data.testarray = storedVector;
        
        chatter_pub.publish(pub_data);
        std::cout << "pub!" << std::endl;
        ros::spinOnce();
        loop_rate.sleep();
        ++count;

    }
    return 0;
}
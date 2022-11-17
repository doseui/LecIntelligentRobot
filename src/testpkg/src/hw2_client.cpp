// hw2_client.cpp
#include "ros/ros.h"
#include "testpkg/hw2_srv.h"
#include "testpkg/radiusArea.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

std::vector<int> storedVectorIn;
std::vector<double> storedVectorOut;

int main(int argc, char ** argv)
{
    ros::init(argc, argv, "hw2_client");
    ros::NodeHandle n;
    
    ros::ServiceClient client = n.serviceClient<testpkg::hw2_srv>("CircleArea");
    testpkg::hw2_srv srv;

    ros::Publisher hw2_radius_pub = n.advertise<testpkg::radiusArea>("RadiusAndArea", 1000);    // publisher를 선언한다.
    ros::Rate loop_rate(1); // loop의 주기 1 hz
    testpkg::radiusArea pub_data;


    int size = 5;
    int count = 0;
    while(ros::ok())
    {
        
        // n개의 반지름 생성 및 넓이 계산 (ex. n = 5)
        for(int i = 0; i < size; i++)
        {
            int randomRadius = std::rand() % 100;
            srv.request.radius = randomRadius;
            storedVectorIn.push_back(randomRadius);
            if(storedVectorIn.size() > size)
                storedVectorIn.erase(storedVectorIn.begin());


            if (client.call(srv))
            {
                double randomArea = srv.response.area;
                storedVectorOut.push_back(randomArea);
                if(storedVectorOut.size() > size)
                    storedVectorOut.erase(storedVectorOut.begin());
                    
                ROS_INFO("Area: %lf", randomArea);
            }
            else
            {
                ROS_ERROR("Failed to call service CircleArea");
                return 1;
            }
        }
        
        pub_data.header.frame_id = "/radius & circle area";
        pub_data.header.seq = count;
        pub_data.header.stamp = ros::Time::now();

        pub_data.radius = storedVectorIn;
        pub_data.area = storedVectorOut;

        hw2_radius_pub.publish(pub_data);
        std::cout << "pub!" << std::endl;
        ros::spinOnce();
        loop_rate.sleep();

        ++count;
    }

    return 0;
}
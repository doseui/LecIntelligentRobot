// 3번 노드 : A와 B를 subscribe한 후, A+B를 연산하여 C로 publish
#include "ros/ros.h"            // ROS 관련 헤더
#include "std_msgs/Int64.h"     // 표준 자료형 메시지(Int64 msg) 패키지

int64_t numA, numB, numC;

/*
 * 받은 메시지 데이터를 터미널에 출력하는 함수
 * 매개변수 : std_msgs::int64 type 객체 msg
 */ 
void chatterCallbackA(const std_msgs::Int64::ConstPtr& msg)
{
    ROS_INFO("received msg from node1 (A) : [%d]", msg->data);  // ROS_INFO로 터미널 창에 출력
    numA = msg->data;
}
void chatterCallbackB(const std_msgs::Int64::ConstPtr& msg)
{
    ROS_INFO("received msg from node2 (B) : [%d]", msg->data);  // ROS_INFO로 터미널 창에 출력
    numB = msg->data;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "node3");
    ros::NodeHandle n;

    ros::Subscriber subA = n.subscribe("chatterA", 1000, chatterCallbackA);
    ros::Subscriber subB = n.subscribe("chatterB", 1000, chatterCallbackB);

    ros::Publisher chatter_pub = n.advertise<std_msgs::Int64>("chatterC", 1000);    // publisher를 선언한다.

    ros::Rate loop_rate(10); // hz

    int count = 0;

    while (ros::ok())
    {
        std_msgs::Int64 msg;   // 객체 선언

        msg.data = numA + numB; // A + B
        
        ROS_INFO("<NODE #3> send msg (C) = %d", msg.data);   // ROS_INFO로 터미널 창에 출력

        chatter_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();

        count++;
    }
    
    ros::spin();

    return 0;
}
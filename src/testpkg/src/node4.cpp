// 4번 노드 : C subscribe 누적 평균 출력
#include "ros/ros.h"            // ROS 관련 헤더
#include "std_msgs/Int64.h"     // 표준 자료형 메시지(Int64 msg) 패키지

void chatterCallback(const std_msgs::Int64::ConstPtr& msg)
{
    static double totalAvg = 0.;
    static int64_t sum = 0;
    static int64_t count = 1;

    sum = sum + msg->data;
    totalAvg = sum / count;

    ROS_INFO("send msg from node3 (C) =[%d], total average = [%lf]", msg->data, totalAvg);  // ROS_INFO로 터미널 창에 출력

    count++;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "node4");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatterC", 1000, chatterCallback);

    ros::spin();

    return 0;
}
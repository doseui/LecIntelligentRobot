// 1번 노드 : 1과 10 사이의 랜덤한 값을 A로 publish
#include "ros/ros.h"
#include "std_msgs/Int64.h" // Int64 msg 헤더 include

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node1");    // master에 등록. ROS를 초기화함. Node 이름 지정.
    ros::NodeHandle n;                 // 노드 핸들을 만든다
    ros::Publisher chatter_pub = n.advertise<std_msgs::Int64>("chatterA", 1000);    // publisher를 선언한다.
    ros::Rate loop_rate(10); // loop의 주기 10 hz
    
    int count = 0;

    while (ros::ok())
    {
        std_msgs::Int64 msg;   // 객체 선언

        int randNum = std::rand() % 10 + 1;   // 1 ~ 10 사이의 난수 생성

        msg.data = randNum;

        ROS_INFO("<NODE #1> send msg (A) = %d", msg.data);   // ROS_INFO로 터미널 창에 출력

        chatter_pub.publish(msg);   // 메시지 publish

        ros::spinOnce();
        loop_rate.sleep();          // loop 주기 외에 남은 시간 동안 sleep

        count++;                    // 루프 카운트 증가

    }

    return 0;
}
#include <ros/ros.h>
#include "simple_publisher.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "simple_publisher");
    ros::NodeHandle nh;
    ros::Rate loop_rate(2);

    SimplePublisher simple_publisher(&nh, "simple_topic/int32");

    int i = 0;

    while(ros::ok())
    {
        simple_publisher.msg.data = i;  // opcja 1
        simple_publisher.publish();     // opcja 1

        simple_publisher.publish(i);    // opcja 2

        std_msgs::Int32 msg;            // opcja 3
        msg.data = i;                   // opcja 3
        simple_publisher.publish(msg);  // opcja 3

        i++;
        loop_rate.sleep();

    }
    return 0;
}

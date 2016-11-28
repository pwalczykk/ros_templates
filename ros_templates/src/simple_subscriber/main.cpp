#include <ros/ros.h>
#include "simple_subscriber.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "simple_subscriber");
    ros::NodeHandle nh;

    SimpleSubscriber simple_subscriber(&nh, "simple_topic/int32");

    ros::spin();

    return 0;
}

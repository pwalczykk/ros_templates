#include <ros/ros.h>
#include "template_subscriber.hpp"
#include "ros_templates/my_message.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "template_subscriber");
    ros::NodeHandle nh;

    TemplateSubscriber <ros_templates::my_message>template_subscriber(&nh, "template_topic/my_message");

    ros::spin();

    return 0;
}

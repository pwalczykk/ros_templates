#include <ros/ros.h>
#include "template_publisher.hpp"
#include "ros_templates/my_message.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "template_publisher");
    ros::NodeHandle nh;
    ros::Rate loop_rate(2);

    TemplatePublisher <ros_templates::my_message>template_publisher(&nh, "template_topic/my_message");

    int i = 0;

    while(ros::ok())
    {
        // opcja 1
        template_publisher.msg.text_1 = "My cat is fat";
        template_publisher.msg.value_1 = i;
        template_publisher.msg.value_2 = i/3.0;
        template_publisher.msg.vector_1.clear();
        template_publisher.msg.vector_1.push_back(0);
        template_publisher.msg.vector_1.push_back(1);
        template_publisher.msg.vector_1.push_back(2);
        template_publisher.msg.vector_1.push_back(3);
        template_publisher.publish();

        // opcja 2
        ros_templates::my_message msg;
        msg.text_1 = "My cat is fat";
        msg.value_1 = i;
        msg.value_2 = i/7.0;
        msg.vector_1.push_back(4);
        msg.vector_1.push_back(5);
        msg.vector_1.push_back(6);
        msg.vector_1.push_back(7);
        msg.vector_1.push_back(8);
        msg.vector_1.push_back(9);
        template_publisher.publish(msg);

        i++;
        loop_rate.sleep();

    }
    return 0;
}

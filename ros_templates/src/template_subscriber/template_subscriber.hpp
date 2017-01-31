#ifndef TEMPLATE_SUBSCRIBER_HPP_
#define TEMPLATE_SUBSCRIBER_HPP_

#include <ros/ros.h>
#include <std_msgs/Int32.h>

template <typename ros_Message>
class TemplateSubscriber
{
protected:
    ros::NodeHandle *nh;
    ros::Subscriber sub;
public:
    ros_Message msg;

public:
    TemplateSubscriber(){}

    TemplateSubscriber(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->sub = nh->subscribe(topic, 100, &TemplateSubscriber::MsgInterrupt, this);
    }
    ~TemplateSubscriber(){}

    void MsgInterrupt(const ros_Message msg){
        this->msg = msg;
        ROS_INFO("RECIVED NEW MESSAGE");
    }
};

#endif

#ifndef TEMPLATE_SUBSCRIBER_HPP_
#define TEMPLATE_SUBSCRIBER_HPP_

#include <ros/ros.h>
#include <std_msgs/Int32.h>

template <typename ros_Message>
class ros_templatesubscriber
{
protected:
    ros::NodeHandle *nh;
    ros::Subscriber sub;
public:
    ros_Message msg;

public:
    ros_templatesubscriber(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->sub = nh->subscribe(topic, 100, &ros_templatesubscriber::MsgInterrupt, this);
    }
    ~ros_templatesubscriber(){}

    void MsgInterrupt(const ros_Message msg){
        this->msg = msg;
        ROS_INFO("RECIVED NEW MESSAGE");
    }
};

#endif

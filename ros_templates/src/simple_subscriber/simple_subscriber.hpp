#ifndef SIMPLE_SUBSCRIBER_HPP_
#define SIMPLE_SUBSCRIBER_HPP_

#include <ros/ros.h>
#include <std_msgs/Int32.h>

class SimpleSubscriber
{
protected:
    ros::NodeHandle *nh;
    ros::Subscriber sub;
public:
    std_msgs::Int32 msg;

public:
    SimpleSubscriber(){};

    SimpleSubscriber(ros::NodeHandle *nh, std::string topic){
        this->nh = nh;
        this->sub = nh->subscribe(topic, 100, &SimpleSubscriber::MsgInterrupt, this);
    }
    ~SimpleSubscriber(){}

    void MsgInterrupt(const std_msgs::Int32 msg){
        this->msg.data = msg.data;
        ROS_INFO("RECIVED MESSAGE: %d", this->msg.data);
    }
};

#endif

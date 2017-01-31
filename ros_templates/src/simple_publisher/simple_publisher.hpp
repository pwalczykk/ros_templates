#ifndef SIMPLE_PUBLISHER_HPP_
#define SIMPLE_PUBLISHER_HPP_

#include <ros/ros.h>
#include <std_msgs/Int32.h>

class SimplePublisher
{
protected:
    ros::NodeHandle *nh;
    ros::Publisher pub;
public:
    std_msgs::Int32 msg;

public:
    SimplePublisher(){}

    SimplePublisher(ros::NodeHandle* nh, std::string topic)
    {
        this->nh = nh;
        this->pub = nh->advertise<std_msgs::Int32>(topic, 100);
    }

    void publish()
    {
        pub.publish(this->msg);
    }

    void publish(int msg_data)
    {
        this->msg.data = msg_data;
        pub.publish(this->msg);
    }

    void publish(std_msgs::Int32 msg)
    {
        this->msg = msg;
        pub.publish(this->msg);
    }
};

#endif

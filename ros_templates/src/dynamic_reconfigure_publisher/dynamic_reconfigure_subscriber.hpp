#ifndef SUBSCRIBER_DRC_HPP_
#define SUBSCRIBER_DRC_HPP_

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <ros_templates/dynamic_reconfigure_guiConfig.h>

#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

#include "template_publisher.hpp"

class DynamicReconfigureSubscriber
{
    ros::NodeHandle *nh;
    dynamic_reconfigure::Server<ros_templates::dynamic_reconfigure_guiConfig> server;
    dynamic_reconfigure::Server<ros_templates::dynamic_reconfigure_guiConfig>::CallbackType f;


    TemplatePublisher <std_msgs::Bool> * pub_bool;
    TemplatePublisher <std_msgs::Int32> * pub_int;
    TemplatePublisher <std_msgs::Float64> * pub_float;
    TemplatePublisher <std_msgs::String> * pub_string;
    TemplatePublisher <std_msgs::Int32> * pub_enum;

public:
    DynamicReconfigureSubscriber(ros::NodeHandle *nh){
        this->nh = nh;

        this->pub_bool =    new TemplatePublisher <std_msgs::Bool> (nh, "dynamic_reconfigure/parameter/bool");
        this->pub_int =     new TemplatePublisher <std_msgs::Int32> (nh, "dynamic_reconfigure/parameter/int");
        this->pub_float =   new TemplatePublisher <std_msgs::Float64> (nh, "dynamic_reconfigure/parameter/float");
        this->pub_string =  new TemplatePublisher <std_msgs::String> (nh, "dynamic_reconfigure/parameter/string");
        this->pub_enum =    new TemplatePublisher <std_msgs::Int32> (nh, "dynamic_reconfigure/parameter/enum");

        f = boost::bind(&DynamicReconfigureSubscriber::dynamicReconfigureCallback, this,_1, _2);
        server.setCallback(f);


    };

    ~DynamicReconfigureSubscriber(){
        delete pub_bool;
        delete pub_int;
        delete pub_float;
        delete pub_string;
        delete pub_enum;
    }

    void dynamicReconfigureCallback(ros_templates::dynamic_reconfigure_guiConfig &config, uint32_t level){
        if(config.bool_value != pub_bool->msg.data){
            pub_bool->msg.data = config.bool_value;
            pub_bool->publish();
        }
        if(config.int_value != pub_int->msg.data){
            pub_int->msg.data = config.int_value;
            pub_int->publish();
        }
        if(config.float_value != pub_float->msg.data){
            pub_float->msg.data = config.float_value;
            pub_float->publish();
        }
        if(config.string_value != pub_string->msg.data){
            pub_string->msg.data = config.string_value;
            pub_string->publish();
        }
        if(config.enum_value != pub_enum->msg.data){
            pub_enum->msg.data = config.enum_value;
            pub_enum->publish();
        }
    }
};

#endif

#ifndef IMAGE_SUBSCRIBER_HPP_
#define IMAGE_SUBSCRIBER_HPP_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

class ImageSubscriber
{
protected:
    ros::NodeHandle *nh;
    image_transport::ImageTransport *it;
    image_transport::Subscriber sub;
    std::string window;
public:
    cv::Mat image;

public:
    ImageSubscriber(){}

    ImageSubscriber(ros::NodeHandle *nh, image_transport::ImageTransport *it, std::string topic, std::string window){
        this->nh = nh;
        this->it = it;
        this->window = window;
        sub = it->subscribe(topic, 1, &ImageSubscriber::MsgInterrupt, this);
        cv::namedWindow(this->window, CV_WINDOW_NORMAL);
        cv::setWindowProperty(this->window, CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    }

    ~ImageSubscriber(){
        cv::destroyWindow(this->window);
    }

    void ResizeWindow(int width, int length){
        cv::resizeWindow(this->window, width, length);
    }

    void MoveWindow(int x, int y){
        cv::moveWindow(this->window, x, y);
    }

    void MsgInterrupt(const sensor_msgs::ImageConstPtr& msg){
        try{
            this->image = cv_bridge::toCvShare(msg, "bgr8")->image;
            cv::imshow(this->window, this->image);
            cv::waitKey(10);
        }
        catch (cv_bridge::Exception& e){
             ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
        }
    }
};

#endif

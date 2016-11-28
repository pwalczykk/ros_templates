#ifndef IMAGEPUBLISHER_HPP_
#define IMAGEPUBLISHER_HPP_

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_msgs/Header.h>

#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

#include <sstream>

#include "camera_handler.hpp"

class ImagePublisher : public CameraHandler
{
protected:
    ros::NodeHandle* nh;
    image_transport::ImageTransport* it;
    image_transport::Publisher pub_img;

public:
    sensor_msgs::ImagePtr img;
    std_msgs::Header header;

public:
    ImagePublisher(ros::NodeHandle* nh, image_transport::ImageTransport *it, int cam_num, std::string topic) : CameraHandler(cam_num)
    {
        this->nh = nh;
        this->it = it;

        pub_img = it->advertise(topic, 1);

        header.seq = 0;
        header.frame_id = "";

    }

    void PublishImage()
    {
        header.seq++;
        header.stamp = ros::Time::now();

        CameraHandler::Capture();
        cv::waitKey(1);

        img = cv_bridge::CvImage(header, "bgr8", CameraHandler::frame).toImageMsg();

        pub_img.publish(img);
    }
};

#endif

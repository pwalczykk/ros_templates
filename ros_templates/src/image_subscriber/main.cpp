#include <ros/ros.h>
#include "image_subscriber.hpp"

int main(int argc, char** argv){
    ros::init(argc, argv, "image_subscriber");
    ros::NodeHandle nh("");
    image_transport::ImageTransport it(nh);

    // Parameter: window name
    std::string window_name;
    nh.param("image_subscriber/window_name", window_name, (std::string)"camera");

    // Parameter: topic name
    std::string topic;
    nh.param("image_subscriber/topic", topic, (std::string)"camera/image");

    // Parameters: window size:
    int width;
    int height;
    nh.param("image_subscriber/width", width, 640);
    nh.param("image_subscriber/height", height, 480);

    // Parameter: window's top-left corner position:
    int x;
    int y;
    nh.param("image_subscriber/x", x, 10);
    nh.param("image_subscriber/y", y, 10);

    ImageSubscriber image_subscriber(&nh, &it, topic, window_name);
    image_subscriber.ResizeWindow(width, height);
    image_subscriber.MoveWindow(x, y);

    ros::spin();

    return 0;
}

#include <ros/ros.h>
#include "template_publisher.hpp"
#include "dynamic_reconfigure_subscriber.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "dynamic_reconfigure_publisher");
    ros::NodeHandle nh;

    DynamicReconfigureSubscriber drs(&nh);

    ros::spin();
}

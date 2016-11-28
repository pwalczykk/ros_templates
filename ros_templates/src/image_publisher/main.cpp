#include <ros/ros.h>
#include <image_transport/image_transport.h>

#include "camera_handler.hpp"
#include "image_publisher.hpp"
#include "camera_info_publisher.hpp"
// #include "synchronizer.hpp"

int main(int argc, char** argv){

    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    ros::Rate loop_rate(30);
    image_transport::ImageTransport it(nh);

    // Number of camera device, eg. "/dev/video0" for camera number 0
    int cam_num;
    nh.param("image_publisher/camera_number", cam_num, 0);

    // Parameter: image topic name
    std::string image_topic;
    nh.param("image_publisher/image_topic", image_topic, (std::string)"camera/image");

    // Parameter: info topic name
    std::string info_topic;
    nh.param("image_publisher/info_topic", info_topic, (std::string)"camera/image");

    // Parameters: camera resolution:
    int width;
    int height;
    nh.param("image_publisher/width", width, 640);
    nh.param("image_publisher/height", height, 480);

    // Parameters: fps
    int fps;
    nh.param("image_publisher/fps", fps, 30);

    // Camera image
    ImagePublisher cam(&nh, &it, cam_num, image_topic);
    cam.CameraHandler::Init();
    cam.CameraHandler::Set(width, height, fps);

    // Camera info - calibration matrixes required for stereovision
    CameraInfoPublisher cam_info(&nh, cam_num, &cam.header, width, height, info_topic);

    double K[9];
    double R[9];
    double P[12];
    int binning_x = 0;
    int binning_y = 0;

    nh.param("image_publisher/K0", cam_info.msg.K[0], (double)0.0);
    nh.param("image_publisher/K1", cam_info.msg.K[1], (double)0.0);
    nh.param("image_publisher/K2", cam_info.msg.K[2], (double)0.0);
    nh.param("image_publisher/K3", cam_info.msg.K[3], (double)0.0);
    nh.param("image_publisher/K4", cam_info.msg.K[4], (double)0.0);
    nh.param("image_publisher/K5", cam_info.msg.K[5], (double)0.0);
    nh.param("image_publisher/K6", cam_info.msg.K[6], (double)0.0);
    nh.param("image_publisher/K7", cam_info.msg.K[7], (double)0.0);
    nh.param("image_publisher/K8", cam_info.msg.K[8], (double)0.0);

    nh.param("image_publisher/R0", cam_info.msg.R[0], (double)0.0);
    nh.param("image_publisher/R1", cam_info.msg.R[1], (double)0.0);
    nh.param("image_publisher/R2", cam_info.msg.R[2], (double)0.0);
    nh.param("image_publisher/R3", cam_info.msg.R[3], (double)0.0);
    nh.param("image_publisher/R4", cam_info.msg.R[4], (double)0.0);
    nh.param("image_publisher/R5", cam_info.msg.R[5], (double)0.0);
    nh.param("image_publisher/R6", cam_info.msg.R[6], (double)0.0);
    nh.param("image_publisher/R7", cam_info.msg.R[7], (double)0.0);
    nh.param("image_publisher/R8", cam_info.msg.R[8], (double)0.0);

    nh.param("image_publisher/P0", cam_info.msg.P[0], (double)0.0);
    nh.param("image_publisher/P1", cam_info.msg.P[1], (double)0.0);
    nh.param("image_publisher/P2", cam_info.msg.P[2], (double)0.0);
    nh.param("image_publisher/P3", cam_info.msg.P[3], (double)0.0);
    nh.param("image_publisher/P4", cam_info.msg.P[4], (double)0.0);
    nh.param("image_publisher/P5", cam_info.msg.P[5], (double)0.0);
    nh.param("image_publisher/P6", cam_info.msg.P[6], (double)0.0);
    nh.param("image_publisher/P7", cam_info.msg.P[7], (double)0.0);
    nh.param("image_publisher/P8", cam_info.msg.P[8], (double)0.0);
    nh.param("image_publisher/P9", cam_info.msg.P[9], (double)0.0);
    nh.param("image_publisher/P10", cam_info.msg.P[10], (double)0.0);
    nh.param("image_publisher/P11", cam_info.msg.P[11], (double)0.0);

    nh.param("image_publisher/binning_x", binning_x, (int)0);   cam_info.msg.binning_x = binning_x;
    nh.param("image_publisher/binning_y", binning_y, (int)0);   cam_info.msg.binning_y = binning_y;

    // // Synchronizer - waits for std_msgs::Bool message with value "True"
    // // After reciving this message waits "delay_ms" miliseconds and starts transmission
    // int delay_ms;
    // nh.param("image_publisher/delay_ms", delay_ms, 0);
    //
    // Synchronizer synchronizer("camera/synchronizer/start", &nh);
    // synchronizer.WaitForSynchro(delay_ms);

    while(ros::ok()){
        cam.PublishImage();
        cam_info.PublishInfo();
        loop_rate.sleep();
    }

    cam.CameraHandler::Release();
    return 0;
}

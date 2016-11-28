cmake_minimum_required(VERSION 2.8.3)
project(ros_templates)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    message_generation
    dynamic_reconfigure
    cv_bridge
    image_transport
)

generate_dynamic_reconfigure_options(
    src/dynamic_reconfigure_publisher/dynamic_reconfigure_gui.cfg
)

add_message_files(
    FILES
    my_message.msg
)

generate_messages(
    DEPENDENCIES
    std_msgs
)

catkin_package(
    CATKIN_DEPENDS message_runtime
)

find_package(OpenCV 3.0.0 REQUIRED)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS} ${std_msgs_INCLUDE_DIRS})

add_executable(simple_publisher
    src/simple_publisher/main.cpp)
target_link_libraries(simple_publisher ${catkin_LIBRARIES})

add_executable(simple_subscriber
    src/simple_subscriber/main.cpp)
target_link_libraries(simple_subscriber ${catkin_LIBRARIES})

add_executable(template_publisher
    src/template_publisher/main.cpp)
target_link_libraries(template_publisher ${catkin_LIBRARIES})
add_dependencies(template_publisher ${ros_templates_EXPORTED_TARGETS})

add_executable(template_subscriber
    src/template_subscriber/main.cpp)
target_link_libraries(template_subscriber ${catkin_LIBRARIES})
add_dependencies(template_subscriber ${ros_templates_EXPORTED_TARGETS})

add_executable(dynamic_reconfigure_publisher
    src/dynamic_reconfigure_publisher/main.cpp)
target_link_libraries(dynamic_reconfigure_publisher ${catkin_LIBRARIES})
add_dependencies(dynamic_reconfigure_publisher ${ros_templates_EXPORTED_TARGETS})

add_executable(image_publisher
    src/image_publisher/main.cpp)
target_link_libraries(image_publisher ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})

add_executable(image_subscriber
    src/image_subscriber/main.cpp)
target_link_libraries(image_subscriber ${OpenCV_LIBRARIES} ${catkin_LIBRARIES})

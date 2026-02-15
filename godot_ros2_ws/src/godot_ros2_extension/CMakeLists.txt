cmake_minimum_required(VERSION 3.16)
project(godot_ros2_extension)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Path to godot-cpp
set(GODOT_CPP_PATH "${CMAKE_SOURCE_DIR}/../../third_party/godot-cpp")
set(GODOT_HEADERS_PATH "${CMAKE_SOURCE_DIR}/../../third_party/godot-headers")

include_directories(
    ${GODOT_CPP_PATH}/include
    ${GODOT_CPP_PATH}/gen/include
    ${GODOT_HEADERS_PATH}
)

add_library(godot_ros2_extension SHARED
    src/ros_node.cpp
    src/register_types.cpp
)

target_link_libraries(godot_ros2_extension
    ${GODOT_CPP_PATH}/bin/libgodot-cpp.linux.template_debug.x86_64.a
)

ament_target_dependencies(godot_ros2_extension
    rclcpp
    std_msgs
)

install(TARGETS godot_ros2_extension
    LIBRARY DESTINATION lib
)

ament_package()


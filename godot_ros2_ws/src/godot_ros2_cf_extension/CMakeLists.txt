cmake_minimum_required(VERSION 3.16)
project(godot_ros2_cf_extension)

# --- Find ROS2 dependencies ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# --- Paths to Godot C++ bindings ---
set(GODOT_CPP_PATH "${CMAKE_SOURCE_DIR}/../../third_party/godot-cpp")
set(GODOT_HEADERS_PATH "${CMAKE_SOURCE_DIR}/../../third_party/godot-headers")

# Include directories for compilation
include_directories(
    ${GODOT_CPP_PATH}/include
    ${GODOT_CPP_PATH}/gen/include
    ${GODOT_HEADERS_PATH}
    ${rclcpp_INCLUDE_DIRS}
    ${std_msgs_INCLUDE_DIRS}
    ${geometry_msgs_INCLUDE_DIRS}
)

# --- Add shared library for Godot ---
add_library(godot_ros2_cf_extension SHARED
    src/ros_node.cpp
    src/register_types.cpp   # your gdextension entry point
)

# --- Link Godot C++ static library ---
target_link_libraries(godot_ros2_cf_extension
    ${GODOT_CPP_PATH}/bin/libgodot-cpp.linux.template_debug.x86_64.a
)

# --- Link ROS2 libraries ---
ament_target_dependencies(godot_ros2_cf_extension
    rclcpp
    std_msgs
    geometry_msgs
)

# --- Required for GDNative / GDExtension ---
set_target_properties(godot_ros2_cf_extension PROPERTIES
    PREFIX ""            # Remove default "lib" prefix
    OUTPUT_NAME "libgodot_ros2_cf_extension"
    POSITION_INDEPENDENT_CODE ON
)

# --- Install shared library into ROS2 workspace ---
install(TARGETS godot_ros2_cf_extension
    LIBRARY DESTINATION lib
)

ament_package()

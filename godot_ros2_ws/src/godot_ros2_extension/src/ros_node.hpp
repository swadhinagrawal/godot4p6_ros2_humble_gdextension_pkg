#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <thread>

namespace godot {

class RosNode : public Node {
    GDCLASS(RosNode, Node)

private:
    rclcpp::Node::SharedPtr node_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    std::thread spin_thread_;
    bool running_;

protected:
    static void _bind_methods();

public:
    RosNode();
    ~RosNode();

    void start_ros();
    void publish_string(String message);
};

}


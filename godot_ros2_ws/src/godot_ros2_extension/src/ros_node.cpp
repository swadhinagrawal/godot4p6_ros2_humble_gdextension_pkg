#include "ros_node.hpp"

using namespace godot;

RosNode::RosNode() {
    running_ = false;
}

RosNode::~RosNode() {
    if (running_) {
        rclcpp::shutdown();
        spin_thread_.join();
    }
}

void RosNode::start_ros() {
    if (!rclcpp::ok()) {
        rclcpp::init(0, nullptr);
    }

    node_ = rclcpp::Node::make_shared("godot_node");

    publisher_ = node_->create_publisher<std_msgs::msg::String>(
        "godot_chatter", 10);

    running_ = true;

    spin_thread_ = std::thread([this]() {
        rclcpp::spin(node_);
    });
}

void RosNode::publish_string(String message) {
    std_msgs::msg::String msg;
    msg.data = message.utf8().get_data();
    publisher_->publish(msg);
}

void RosNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("start_ros"), &RosNode::start_ros);
    ClassDB::bind_method(D_METHOD("publish_string", "message"), &RosNode::publish_string);
}


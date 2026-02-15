#ifndef GODOT_ROS_CF__ROS_NODE_HPP
#define GODOT_ROS_CF__ROS_NODE_HPP
#pragma once

// #include <godot_cpp/classes/node.hpp>
// #include <godot_cpp/core/class_db.hpp>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#include <thread>

#include <geometry_msgs/msg/twist.hpp>
#include <godot_cpp/classes/node.hpp>
#include <variant>
#include <map>

namespace godot {

using SupportedSubscriberTypes = std::variant<
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr
>;

class RosNode : public Node {
    GDCLASS(RosNode, Node)

private:
    std::shared_ptr<rclcpp::Node> m_node;
    String node_name = "crazyflie_ros_node";

    std::map<String, SupportedSubscriberTypes> m_subscribers;

    Vector3 last_linear_cmd = Vector3(0,0,0);
    Vector3 last_angular_cmd = Vector3(0,0,0);

protected:
    static void _bind_methods();

public:
    void init_rclcpp_node(const String &name);
    void spin_some();
    void create_subscriber(const String &topic_name, Object* godot_object, const String &callback_method);

    String get_node_name() { return node_name; }
    Vector3 get_last_linear_cmd() { return last_linear_cmd; }
    Vector3 get_last_angular_cmd() { return last_angular_cmd; }
};

} // namespace godot

#endif

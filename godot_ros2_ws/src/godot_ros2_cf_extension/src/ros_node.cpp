#include "ros_node.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <iostream>

namespace godot {

// void RosNode::_bind_methods() {
//     ClassDB::bind_method(D_METHOD("init_rclcpp_node", "name"), &RosNode::init_rclcpp_node);
//     ClassDB::bind_method(D_METHOD("spin_some"), &RosNode::spin_some);
//     ClassDB::bind_method(D_METHOD("create_subscriber", "topic", "object", "method"), &RosNode::create_subscriber);

//     ClassDB::bind_method(D_METHOD("get_node_name"), &RosNode::get_node_name);
//     ClassDB::bind_method(D_METHOD("get_last_linear_cmd"), &RosNode::get_last_linear_cmd);
//     ClassDB::bind_method(D_METHOD("get_last_angular_cmd"), &RosNode::get_last_angular_cmd);

//     ADD_PROPERTY(PropertyInfo(Variant::STRING, "node_name"), nullptr, "get_node_name");
//     ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "last_linear_cmd"), nullptr, "get_last_linear_cmd");
//     ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "last_angular_cmd"), nullptr, "get_last_angular_cmd");
// }

void RosNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("init_rclcpp_node", "name"), &RosNode::init_rclcpp_node);
    ClassDB::bind_method(D_METHOD("spin_some"), &RosNode::spin_some);
    ClassDB::bind_method(D_METHOD("create_subscriber", "topic", "object", "method"), &RosNode::create_subscriber);

    ClassDB::bind_method(D_METHOD("get_node_name"), &RosNode::get_node_name);
    ClassDB::bind_method(D_METHOD("get_last_linear_cmd"), &RosNode::get_last_linear_cmd);
    ClassDB::bind_method(D_METHOD("get_last_angular_cmd"), &RosNode::get_last_angular_cmd);

    // Expose properties to inspector
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "node_name"), StringName(), "get_node_name");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "last_linear_cmd"), StringName(), "get_last_linear_cmd");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "last_angular_cmd"), StringName(), "get_last_angular_cmd");
}


void RosNode::init_rclcpp_node(const String &name) {
    if (!rclcpp::ok()) rclcpp::init(0, nullptr);
    node_name = name;
    m_node = std::make_shared<rclcpp::Node>(name.utf8().get_data());
}

void RosNode::spin_some() {
    if (m_node) rclcpp::spin_some(m_node);
}

void RosNode::create_subscriber(const String &topic_name, Object* godot_object, const String &callback_method) {
    if (!m_node) {
        std::cerr << "ROS node not initialized!" << std::endl;
        return;
    }

    auto sub = m_node->create_subscription<geometry_msgs::msg::Twist>(
        topic_name.utf8().get_data(),
        10,
        [godot_object, callback_method, this](geometry_msgs::msg::Twist::SharedPtr msg) {
            last_linear_cmd = Vector3(msg->linear.x, msg->linear.y, msg->linear.z);
            last_angular_cmd = Vector3(msg->angular.x, msg->angular.y, msg->angular.z);
            godot_object->call(callback_method, last_linear_cmd, last_angular_cmd);
        }
    );

    m_subscribers[topic_name] = sub;
}

} // namespace godot

// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>

// include ROS 1
#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-parameter"
#endif
#include "ros/ros.h"
#ifdef __clang__
# pragma clang diagnostic pop
#endif

// include ROS 2
#include "rclcpp/rclcpp.hpp"

#include "ros1_bridge/bridge.hpp"


int main(int argc, char * argv[])
{
  // ROS 1 node
  ros::init(argc, argv, "ros2_to_ros1_bridge_nuc");
  ros::NodeHandle ros1_node;

  // ROS 2 node
  rclcpp::init(argc, argv);
  auto ros2_node = rclcpp::Node::make_shared("ros2_to_ros1_bridge_nuc");

  // bridge one example topic
  // std::string topic_name = "chatter";
  // std::string ros1_type_name = "std_msgs/String";
  // std::string ros2_type_name = "std_msgs/msg/String";
  // size_t queue_size = 10;

  size_t queue_size = 10;


  std::string topic_name_origin = "/camera/camera/color/image_raw/compressed";
  std::string topic_name_ros1 = "/ros1/color/image_raw/compressed";
  std::string ros1_type_name = "sensor_msgs/CompressedImage";
  std::string ros2_type_name = "sensor_msgs/msg/CompressedImage";

  auto handles = ros1_bridge::create_bridge_from_2_to_1(
      ros2_node, ros1_node,
      ros2_type_name, topic_name_origin, 10,
      ros1_type_name, topic_name_ros1, 10);

  // std::string topic_name_2 = "/orbbec_camera/depth/image_raw/compressed";
  // std::string ros1_type_name_2 = "sensor_msgs/CompressedImage";
  // std::string ros2_type_name_2 = "sensor_msgs/msg/CompressedImage";

  // auto handles_2 = ros1_bridge::create_bridge_from_2_to_1(
  //   ros1_node, ros2_node, ros1_type_name_2, ros2_type_name_2, topic_name_2, queue_size);
  
  std::string topic_name_depth_origin = "/camera/camera/aligned_depth_to_color/image_raw/compressedDepth";
  std::string topic_name_depth_ros1 = "/ros1/depth/image_raw/compressedDepth";
  std::string ros1_type_name_depth = "sensor_msgs/CompressedImage";
  std::string ros2_type_name_depth = "sensor_msgs/msg/CompressedImage";

  auto handles_depth = ros1_bridge::create_bridge_from_2_to_1(
      ros2_node, ros1_node,
      ros2_type_name_depth, topic_name_depth_origin, 10,
      ros1_type_name_depth, topic_name_depth_ros1, 10);
  
  std::string topic_name_cam_info_origin = "/camera/camera/color/camera_info";
  std::string topic_name_cam_info_ros1 = "/ros1/color/camera_info";
  std::string ros1_type_name_cam_info = "sensor_msgs/CameraInfo";
  std::string ros2_type_name_cam_info = "sensor_msgs/msg/CameraInfo";

  auto handles_cam_info = ros1_bridge::create_bridge_from_2_to_1(
      ros2_node, ros1_node,
      ros2_type_name_cam_info, topic_name_cam_info_origin, 10,
      ros1_type_name_cam_info, topic_name_cam_info_ros1, 10);
  
  std::string topic_name_odom_origin = "/Odometry";
  std::string topic_name_odom_ros1 = "/ros1/Odometry";
  std::string ros1_type_name_odom = "nav_msgs/Odometry";
  std::string ros2_type_name_odom = "nav_msgs/msg/Odometry";

  auto handles_odom = ros1_bridge::create_bridge_from_2_to_1(
      ros2_node, ros1_node,
      ros2_type_name_odom, topic_name_odom_origin, 10,
      ros1_type_name_odom, topic_name_odom_ros1, 10);
  
  // ROS 1 asynchronous spinner
  ros::AsyncSpinner async_spinner(1);
  async_spinner.start();

  // ROS 2 spinning loop
  rclcpp::executors::SingleThreadedExecutor executor;
  while (ros1_node.ok() && rclcpp::ok()) {
    executor.spin_node_once(ros2_node, std::chrono::milliseconds(1000));
  }

  return 0;
}

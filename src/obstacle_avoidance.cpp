// MIT License

// Copyright (c) 2022 Guru Nandhan A D P

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

/**
 * @file obstacle_avoidance.cpp
 * @author Guru Nandhan A D P(guruadp@umd.edu)
 * @brief this program avoids the obstacle 
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "geometry_msgs/msg/twist.hpp"    // Twist
#include "rclcpp/rclcpp.hpp"              // ROS Core Libraries
#include "sensor_msgs/msg/laser_scan.hpp" // Laser Scan

using std::placeholders::_1;

class ObstacleAvoidance : public rclcpp::Node {
public:
  ObstacleAvoidance() : Node("ObstacleAvoidance") {

    auto default_qos = rclcpp::QoS(rclcpp::SystemDefaultsQoS());
    subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "laser_scan", default_qos,
        std::bind(&ObstacleAvoidance::topic_callback, this, _1));
    publisher_ =
        this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
  }

private:
  void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr _msg) {
    // 200 readings, from right to left, from -57 to 57 degress
    // calculate new velocity cmd
    float min = 10;
    for (int i = 0; i < 200; i++) { float current = _msg->ranges[i];
      if (current < min) { min = current; } } auto message = this->calculateVelMsg(min);
    publisher_->publish(message);
  }
  geometry_msgs::msg::Twist calculateVelMsg(float distance) {
    auto msg = geometry_msgs::msg::Twist();
    // logic
    RCLCPP_INFO(this->get_logger(), "Distance is: '%f'", distance);
    if (distance < 1) {
      // turn around
      msg.linear.x = 0;
      msg.angular.z = 0.3;
    } else {
      // go straight ahead
      msg.linear.x = 0.3;
      msg.angular.z = 0;
    }
    return msg;
  }
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ObstacleAvoidance>());
  rclcpp::shutdown();
  return 0;
}
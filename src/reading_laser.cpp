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

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

using std::placeholders::_1;

class ReadingLaser : public rclcpp::Node {

public:
  ReadingLaser() : Node("reading_laser") {

    auto default_qos = rclcpp::QoS(rclcpp::SystemDefaultsQoS());

    subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "laser_scan", default_qos,
        std::bind(&ReadingLaser::topic_callback, this, _1));
  }

private:
  void topic_callback(const sensor_msgs::msg::LaserScan::SharedPtr _msg) {
    RCLCPP_INFO(this->get_logger(), "I heard: '%f' '%f'", _msg->ranges[0],
                _msg->ranges[100]);
  }
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
//   auto node = std::make_shared();
//   RCLCPP_INFO(node->get_logger(), "Hello my friends");
  rclcpp::spin(std::make_shared<ReadingLaser>());
  rclcpp::shutdown();
  return 0;
}
#include <rclcpp/rclcpp.hpp>

#include "std_msgs/msg/string.hpp"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::node::Node::make_shared("bugged_talker");
    auto pub = node->create_publisher<std_msgs::msg::String>("asi_clock", rmw_qos_profile_sensor_data);

    rclcpp::WallRate rate(5);
	  static uint32_t publisher_count = 0;
	  std_msgs::msg::String msg;
    while (rclcpp::ok())
    {
	    msg.data = "Hello, world! " + std::to_string(publisher_count++);
      std::cout << "publishing " << publisher_count << "secs" << std::endl;
      pub->publish(msg);
      rclcpp::spin_some(node);
      rate.sleep();
	    publisher_count++;
    }

    return EXIT_SUCCESS;
}

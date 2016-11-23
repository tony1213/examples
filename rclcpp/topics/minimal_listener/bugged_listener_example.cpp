#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

void listener_cb(const std_msgs::msg::String::SharedPtr msg) {
    std::cout << "data is " << msg->data << "\n";
}

int main(int argc, char* argv[]) {

    rclcpp::init(argc, argv);
    auto node = rclcpp::node::Node::make_shared("bugged_listener");
    auto subscription = node->create_subscription<std_msgs::msg::String>("asi_clock", listener_cb, rmw_qos_profile_sensor_data);

    // rclcpp::WallRate wallRate(10);

    rclcpp::sleep_for(std::chrono::milliseconds(5000));

    uint64_t i = 0U;
    while (rclcpp::ok())
    {
      std::cout << "before spin some " << i << std::endl;
      rclcpp::spin_some(node);
      std::cout << "after spin some " << i << std::endl;
      ++i;
      // wallRate.sleep();
      rclcpp::utilities::sleep_for(std::chrono::milliseconds(500));
    }
    return EXIT_SUCCESS;
}

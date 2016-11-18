// Copyright 2014 Open Source Robotics Foundation, Inc.
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

#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "example_interfaces/srv/add_two_ints.hpp"

void handle_add_two_ints(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
  std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
  (void)request_header;
  std::cout << "Incoming request" << std::endl;
  std::cout << "a: " << request->a << " b: " << request->b << std::endl;
  response->sum = request->a + request->b;
}

void handle_add_two_ints2(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
  std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response,
  int i)
{
  (void)request_header;
  std::cout << "Incoming request" << std::endl;
  std::cout << "a: " << request->a << " b: " << request->b << " i: " << i << std::endl;
  response->sum = request->a + request->b;
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("add_two_ints_server");

  std::function<void(const std::shared_ptr<rmw_request_id_t>,
    const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>,
    std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>)> fcn;
  fcn = std::bind(handle_add_two_ints, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", fcn);

  // the next block does not compile
  // {
  //   int i = 1;
  //   std::function<void(const std::shared_ptr<rmw_request_id_t>,
  //     const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>,
  //     std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>, int)> fcn;
  //   fcn = std::bind(handle_add_two_ints2, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, i);

  //   node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints_with_args", fcn);
  // }

  // workaround solution
  // note the missing 4th template argument (int) in the function declaration
  {
    int i = 1;
    std::function<void(const std::shared_ptr<rmw_request_id_t>,
      const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>,
      std::shared_ptr<example_interfaces::srv::AddTwoInts::Response>)> fcn;
    fcn = std::bind(handle_add_two_ints2, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, i);

    node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints_args", fcn);
  }

  rclcpp::spin(node);

  return 0;
}

# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys

import rclpy

from std_msgs.msg import String


def main(argv=sys.argv[1:]):
    if argv is None:
        node_name = 'secure_subscriber'
    else:
        node_name = argv[0]
    rclpy.init()

    node = rclpy.create_node(node_name)

    sub = node.create_subscription(
        String, 'chatter', lambda msg: print('I heard: [%s]' % msg.data))
    assert sub  # prevent unused warning

    while rclpy.ok():
        rclpy.spin_once(node)

if __name__ == '__main__':
    main()

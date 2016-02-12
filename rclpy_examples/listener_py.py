import sys

import rclpy
from rclpy.qos import qos_profile_default
from std_msgs.msg import String


def chatter_callback(msg):
    print('I heard: [%s]' % msg.data)

def main(args=None):
    if args is None:
        args = sys.argv

    rclpy.init(args)

    node = rclpy.create_node('listener')

    sub = node.create_subscription(String, 'chatter', chatter_callback, qos_profile_default)

    rclpy.spin(node)

if __name__ == '__main__':
    main()

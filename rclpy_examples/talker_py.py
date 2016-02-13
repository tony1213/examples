import sys
from time import sleep

import rclpy
from rclpy.qos import qos_profile_default
from std_msgs.msg import String


def main(args=None):
    if args is None:
        args = sys.argv

    rclpy.init(args)

    node = rclpy.create_node('talker')

    chatter_pub = node.create_publisher(String, 'chatter', qos_profile_default)

    msg = String()

    i = 1
    while True:
        msg.data = 'Hello World: {0}'.format(i)
        i += 1
        print('Publishing: "{0}"'.format(msg.data))
        chatter_pub.publish(msg)
        sleep(1)

if __name__ == '__main__':
    main()

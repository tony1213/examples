import os
import sys
from multiprocessing import Process
from multiprocessing import Queue
from unittest import TestCase

from listener_py import main as listener_main
from talker_py import main as talker_main

os.environ['OSPL_VERBOSITY'] = '8'  # 8 = OS_NONE

def talker_process(queue):
    sys.stdout = queue
    talker_main()

def listener_process(queue):
    sys.stdout = queue
    listener_main()


class QueueHandler:
    def __init__(self):
        self.queue = Queue()

    def write(self, msg):
        self.queue.put(msg)
        if msg.startswith('I heard'):
            self.talker.terminate()
            sys.exit()

    def flush(self):
        sys.__stdout__.flush()


def test_talker_listener():
    queue_handler = QueueHandler()
    talker = Process(target=talker_process, args=(queue_handler,))
    listener = Process(target=listener_process, args=(queue_handler,))
    queue_handler.talker = talker
    queue_handler.listener = listener
    talker.start()
    listener.start()

    talker.join()
    listener.join()

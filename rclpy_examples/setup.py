from setuptools import find_packages
from setuptools import setup

setup(
    name='rclpy_examples',
    version='0.0.0',
    packages=[''],
    install_requires=['setuptools'],
    author='Esteve Fernandez',
    author_email='esteve@osrfoundation.org',
    maintainer='Esteve Fernandez',
    maintainer_email='esteve@osrfoundation.org',
    keywords=['ROS'],
    classifiers=[
        'Intended Audience :: Developers',
        'License :: OSI Approved :: Apache Software License',
        'Programming Language :: Python',
        'Topic :: Software Development',
    ],
    description='Package containing examples of how to use the rclpy API.',
    license='Apache License, Version 2.0',
    test_suite='nose.collector',
    test_require=['nose'],
    entry_points={
        'console_scripts': [
            'listener_py = listener_py:main',
            'talker_py = talker_py:main',
        ],
    },
)

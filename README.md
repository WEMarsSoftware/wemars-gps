# WEMars GPS Code

## Hardware
* Arduino Nano
* Nvidia Jetson TX1

## gps_ros
### Dependencies:
Arduino side:
* [NeoGPS](https://github.com/SlashDevin/NeoGPS)
* [NeoSWSerial](https://github.com/SlashDevin/NeoSWSerial)
* [ROS libraries for Arduino](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)
Host side:
* [ROS Kinetic Distribution](http://wiki.ros.org/kinetic/Installation/Ubuntu) ([here](http://wiki.ros.org/Installation/UbuntuARM) for Jetson TX1)

### Usage:
*  Connect Arduino to host
*  On host computer:
 * roscore
 * rosrun rosserial_python serial_node.py /dev/ttyUSB0

## gps_simple
### Dependencies:
Arduino side:
* [Adafruit GPS Library](https://github.com/adafruit/Adafruit_GPS)

### Usage:
* Connect Arduino to host
* SSH into host
* Run `cat /dev/ttyS0` on host
 

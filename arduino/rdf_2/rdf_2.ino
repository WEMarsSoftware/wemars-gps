#define ROS 0

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

#if ROS

#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

#endif

RH_ASK driver;

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
#if ROS
    nh.initNode();
    nh.advertise(chatter);
#endif
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
        int i;
        // Message with a good checksum received, dump it.
        Serial.print("Message: ");
        Serial.println((char*)buf);  
#if ROS
        str_msg.data = hello;
        chatter.publish( &str_msg );
        nh.spinOnce();
#endif

    }
}

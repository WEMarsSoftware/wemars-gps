#include <TinyGPS++.h>

//serial pins
#define RXD2 16 //TX2
#define TXD2 17 //RX2

int timer; 

TinyGPSPlus gps;

void setup() {
  //begin serials
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); //gps recommended baud rate 9600

  Serial.println("GPS START...");
  Serial.println();

  timer = millis();//start timer
}

void loop() {
  
  //while there are values saved in the serial buffer
  while(Serial2.available() > 0){ 
      byte gpsData = Serial2.read();
      gps.encode(gpsData);//read and encode data from serial  
  }

  //if 3 seconds have passed
  if(millis() - timer >= 3000){
    timer = millis(); //reset timer
    Serial.println("BLINK"); //onboard LED broken

    //if there is no connection with satalite
      if (gps.location.lat() == 0 || gps.location.lng() == 0){
        Serial.println("GPS connecting...");
      }
      else{
        //print gps location
        Serial.print("Latitude = "); 
        Serial.print(gps.location.lat(), 6);
        Serial.print(" Longitude = "); 
        Serial.println(gps.location.lng(), 6);
      }
  }
  

}

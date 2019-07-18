#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>;

//network credentials
const char* ssid = "partybus";
const char* password = "allaboard"; 

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncWebSocketClient * globalClient = NULL; //client for server

int wifi_status; //status of wifi 

bool server_connect = false; //if server is connected

bool led_status = false; //if onboard LED is on/off
unsigned int timer;


#define LED 2 //pin for builtin LED
const int button_pin = 4;


//if there is a websocket event
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){

  //if the websocket has connected
  if(type == WS_EVT_CONNECT){
 
    Serial.println("Websocket client connection received");
    globalClient = client; //declare client
    server_connect = true; 

  //if the websocket has disconnected
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    globalClient = NULL; //to avoid errors
    server_connect = false;
  }
}



void setup() {

  pinMode(LED, OUTPUT); //setbuiltin LED
  digitalWrite(LED,HIGH); //keep board LED solid until connected
  timer = millis(); //start timer
  pinMode(button_pin, INPUT);
  //attachInterrupt(0, pin_ISR, CHANGE);
  
  Serial.begin(115200);


  Serial.print("Connecting to WiFi network...");
  digitalWrite(LED,LOW);


  //need this to write to client
  if(!SPIFFS.begin(true)){
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }


  boolean flag = true;
  
  //loop until wifi connected
  while(flag){
    //if 3 seconds have passed since timer started/reset
    if (millis() - timer >= 3000){
      timer = millis(); //reset timer
      //try to connect to WiFi 
      wifi_status = WiFi.begin(ssid,password);
      if (wifi_status == WL_CONNECTED){
        Serial.println("Wifi connected");
        flag = false; //end loop
      }
      else{
        Serial.print(".");//add period as waitbar
      }
    }
  }
  Serial.println("IP:" + WiFi.localIP().toString()); //print IP of esp32

  //start server
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ws.html", "text/html");
  });
  server.begin();

}

void loop() {
  
  
  //if time passed since reset is more than blink rate
  if (millis() - timer >= 10000){
    //if LED was on
    if(led_status){
      digitalWrite(LED,LOW); //turn off
    }
    else{
      digitalWrite(LED,HIGH); //turn on
    }
    Serial.println("BLINK");
    if(server_connect){
      Serial.println("BORK at " + String(millis())); //onboard led is missing
      globalClient->text("BORK at " + String(millis())); //send text to client
    }

    led_status = !led_status; //invert LED status
    timer = millis(); //reset timer
  }

}

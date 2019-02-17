////https://gist.github.com/dogrocker/f998dde4dbac923c47c1
//https://github.com/chriscook8/esp-arduino-apboot

#include <WiFi.h>
#include <WiFiClient.h> 
#include <WebServer.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <Servo.h>
/* Create a WiFi access point and provide a web server on it. */
/*
extern "C" {//FOR SOFT RESET
#include "user_interface.h" //FOR SOFT RESET
//http://www.esp8266.com/viewtopic.php?p=13165
}
*/

enum car_speed
{
    LOW_SPEED = 140,
    MEDIUM_SPEED = 190,
    HIGH_SPEED =  250
};
enum MOTOR_STATE  
{
  STOP,
  FORWARD_FAST,
  FORWARD_SLOW,
  BACKWARD,
  STRAIGHT,
  LEFT_60DEG,
  LEFT_30DEG,  
  RIGHT_60DEG,
  RIGHT_30DEG  
};

const char* motorCommands[]=
{
  "STRAIGHT",
  "FORWARD",  
  "BACK",
  "RIGHT_30_DEG",//relative to straight direction, forward
  "RIGHT_60_DEG",
  "LEFT_30_DEG",
  "LEFT_60_DEG",
  "STOP"  
};

int collisionAvoidanceDistance = 15; //15 cms
boolean collisionDetected =false;
boolean enableCollisionDetection = true;
int distance=0;

const int MANUAL = 0;
const int AUTOMATIC = 1;

int carMovement = MANUAL;
int currentCardirection = STOP;
int carSpeed=165;
const long trackDetectionInterval = 100;//100;

long currentMillis=0;   
int packetSize = 0;  
String commandFromApp="";

const int UDP_TX_PACKET_MAX_SIZE = 24;
const char *ssid = "onsemicar";
const char *password = "onsemi@123";

WebServer server(8888);
unsigned int localPort = 8888;
WiFiUDP UDP; 
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "5"; // a string to send back
int serv0=0;;


/* Just a little test message.  Go to http://192.168.4.1 in a web browser
* connected to this access point to see it.
* 
*/

                                                                                                                                     
void connectUDP();

void setup() 
{
  Serial.begin(115200);
  EEPROM.begin(512);
  Serial.println();  

  Serial.print("Configuring access point...");
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  connectUDP();    
  initialiseIRSensor();
  initialiseMotor();  
  servoInit();
  initUltasonicSensor();
}

void loop() 
{   
   server.handleClient();
   
   if(udpConnected)
   {
    // if there data available, read a packet
      packetSize = UDP.parsePacket();   
    
      if(packetSize)
      {
        readUDPData();//read any message sent from mobile app
        carControl(commandFromApp);      
      }
   }
   
   if ((millis() - currentMillis) >= trackDetectionInterval)
   {
      if(carMovement == AUTOMATIC)
      {
          lineFollowerBrain();
      }
      
      currentMillis = millis();      
   }    
   
   if(enableCollisionDetection == true)
   {
     distance = getDistance();
     if(( distance <= collisionAvoidanceDistance ) && collisionDetected == false)
     {        
        motorOperation("STOP");
        collisionDetected = true;
     }
     else if((distance > collisionAvoidanceDistance ) && collisionDetected == true)
     {
          collisionDetected = false;
     }
     else
     {
       // Serial.print("distance: ");
       // Serial.println(distance);
     }
   }   
}

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

char flag1;
String esid;
String s="";
const int UDP_TX_PACKET_MAX_SIZE = 24;

const char *ssid = "onsemicar";
const char *password = "onsemi@123";

enum MOTOR_STATE  
{
  STOP,
  FORWARD_FAST,
  FORWARD_SLOW,
  BACKWARD,  
  LEFT_SLOW,
  LEFT_FAST,  
  RIGHT_SLOW,
  RIGHT_FAST
};


int current_direction = STOP;

int speed_A=165, speed_B=165;

Servo servo1;  // create servo object to control a servo

WebServer server(8888);
unsigned int localPort = 8888;
WiFiUDP UDP; 
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "5"; // a string to send back
int serv0=0;;
int serv1=0;;
int serv=0;
int serv2=0;
int led3=0; 
int led2=0; 
int led1=0; 
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
* connected to this access point to see it.
* 
*/
const long interval = 1000;//100;
                                                                                                                                     
void connectUDP();
/*
void handleRoot() 
{
  server.send(200, "text/html", "<h1>You are connected</h1>");
} 
*/ 
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
  //server.on("/", handleRoot);
 // server.begin();
 // Serial.println("HTTP server started");
  connectUDP();  
  
  initialiseIRSensor();
  initialiseMotor();  
  servoInit();
   //testOutPins();
   //current_direction = FORWARD;
}

void loop() 
{  
   static long currentMillis;
   static byte statCounter = 0;
   static boolean val;   
   
   if (millis() - currentMillis >= interval)
   {
      lineFollowerBrain();
      servoControl();
     /* switch(current_direction)
      {
          case FORWARD:
              motorOperation("FORWARD",speed_A,speed_B);
              current_direction = BACKWARD;
          break;
          case BACKWARD:
              motorOperation("BACK",speed_A,speed_B);
              current_direction = LEFT;
          break;
          case LEFT:
              motorOperation("LEFT",speed_A,speed_B);
              current_direction = RIGHT;
          break;
          case RIGHT:
              motorOperation("RIGHT",speed_A,speed_B);
              current_direction = STOP;
          break;  
          case STOP:
              motorOperation("STOP",speed_A,speed_B);
              current_direction = FORWARD;
          break;         
          
      }*/
      currentMillis = millis();
      Serial.println(".");
   }
  
  server.handleClient();
  if(udpConnected)
  {
    // if thereâ€™s data available, read a packet
    int packetSize = UDP.parsePacket();   
    
    if(packetSize)
    {
      Serial.println("");
      Serial.print("Received packet of size ");
      Serial.print("From ");
      IPAddress remote = UDP.remoteIP();
      for (int i =0; i < 4; i++)
      {
        Serial.print(remote[i], DEC);
        if (i < 3)
        {        
          Serial.print(".");
        }
      }
      Serial.print(", port ");
      Serial.println(UDP.remotePort());

      // read the packet into packetBufffer
      UDP.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
      Serial.println("Contents:");
      
      if(packetSize>1 && packetSize<3)
      {      
          serv0=packetBuffer[0];
          serv0= serv0-48;
          serv1=packetBuffer[1];     
          serv1= serv1-48;
          serv=  serv1 +(serv0*10);     
      }
  
      if(packetSize>2 && packetSize<4)
      {      
          serv0=packetBuffer[0];
          serv0= serv0-48;
          serv1=packetBuffer[1];      
          serv1= serv1-48;
          serv2=packetBuffer[2];      
          serv2= serv2-48;
          serv=  serv2+(serv1*10) +(serv0*100);
        
      }
      if(packetSize>3 && packetSize<5)
      {        
          serv0=packetBuffer[0];
          serv0= serv0-48; 
          serv1=packetBuffer[1];        
          serv1= serv1-48;
          serv2=packetBuffer[2];        
          serv2= serv2-48;
          char serv3=packetBuffer[3];
          serv3= serv3-48;
          serv= serv3+ (serv2*10)+(serv1*100) +(serv0*1000);
      }  
      if(packetSize>0 && packetSize<2)
      {    
          serv=packetBuffer[0];
          serv=serv-48;
      }  
      s =""; 
      for(int j=0;j<packetSize;j++)
      {  
          s += (String)packetBuffer[j];  
      }
      Serial.println("string");
      Serial.println(s);
      
      if (s == "fwd")
      {
        Serial.println("moving forward");
        motorOperation("FORWARD",speed_A,speed_B);
      }
      else if(s == "back")
      {
        Serial.println("moving back");
        motorOperation("BACK",speed_A,speed_B);
      }
      else if(s == "left")
      {
        Serial.println("moving left");
        motorOperation("LEFT",speed_A,speed_B);
      }
      else if(s == "right")
      {
        Serial.println("moving right");
        motorOperation("RIGHT",speed_A,speed_B);
      }
      else if(s == "stop")
      {
          Serial.println("stopping");
          motorOperation("STOP",speed_A,speed_B);

      }
      else if(s == "speedL")
      {
          motorOperation("SPEEDL",speed_A,speed_B);  
      }
      else if(s == "speedM")
      {
           motorOperation("SPEEDM",speed_A,speed_B);
      }
      else if(s == "speedH")
      {
           motorOperation("SPEEDH",speed_A,speed_B);
      }
    }
  }
}
void connectUDP(void)
{    
    Serial.println("Connecting to UDP..");
    
    if(UDP.begin(localPort) == 1)
    {
        udpConnected = true;
        Serial.println("Connection successful");        
    }
    else
    {
      Serial.println("Connection failed..");
    }    
}
  
  
  
  
  
  


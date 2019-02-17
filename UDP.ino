
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


void readUDPData(void)
{
      int serv1=0;;
      int serv=0;
      int serv2=0;
      
      
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
      commandFromApp =""; 
      for(int j=0;j<packetSize;j++)
      {  
          commandFromApp += (String)packetBuffer[j];  
      }
      Serial.println("app command: ");
      Serial.println(commandFromApp);
  
}

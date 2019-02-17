
void carControl(String command)
{
      if (command == "fwd")
      {
        Serial.println("moving forward");        
        motorOperation("FORWARD");        
      }
      else if(command == "back")
      {
        Serial.println("moving back");        
        motorOperation("BACK");
      }
      else if(command == "left")
      {
        Serial.println("steering left");        
        steeringControl("LEFT");
      }
      else if(command == "right")
      {
        Serial.println("steering right");
        steeringControl("RIGHT");
      }

      else if(command == "stop")
      {
          Serial.println("stopping");
          motorOperation("STOP");
      }
      else if(command == "speedL")
      {
          motorOperation("SPEEDL");  
      }
      else if(command == "speedM")
      {
           motorOperation("SPEEDM");
      }
      else if(command == "speedH")
      {
           motorOperation("SPEEDH");
      }  
      else if(command == "manual")
      {
         if(carMovement != MANUAL)
         {           
            carMovement = MANUAL;
            resetSteering();
            motorOperation("STOP");
         }
      }
      else if(command == "automatic")
      {
           carMovement = AUTOMATIC;
      }
      else if(command == "safetyEnable")
      {
        enableCollisionDetection = true; 
      }      
      else if(command == "safetyDisable")
      {
         enableCollisionDetection = false; 
         collisionDetected = false;  
      }
      else
      {
        Serial.print("Invalid command");     
        Serial.println(command);     
      }
  
}

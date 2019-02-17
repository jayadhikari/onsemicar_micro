const int MOTOR_DIR_A = 21;
const int MOTOR_PWM_A = 19;
const int MOTOR_BRK_A = 18;

const int MOTOR_DIR_B = 4;
const int MOTOR_PWM_B = 16;
const int MOTOR_BRK_B = 15;

const int MOTOR_A_PWM_CHANNEL = 2;
const int MOTOR_B_PWM_CHANNEL = 3;

const int PWM_CHANNEL_FREQ = 5000;
const int PWM_CHANNEL_RESOLUTION = 8;

const int MOTOR_DIR_FORWARD = 0;
const int MOTOR_DIR_REVERSE = 1;


void initialiseMotor(void) 
{
   pinMode(MOTOR_DIR_A, OUTPUT);
   pinMode(MOTOR_PWM_A, OUTPUT);   
   pinMode(MOTOR_BRK_A, OUTPUT);
   
   pinMode(MOTOR_DIR_B, OUTPUT);   
   pinMode(MOTOR_PWM_B, OUTPUT);
   pinMode(MOTOR_BRK_B, OUTPUT);
   
  // configure LED PWM functionalitites
   ledcSetup(MOTOR_A_PWM_CHANNEL, PWM_CHANNEL_FREQ, PWM_CHANNEL_RESOLUTION);
   ledcSetup(MOTOR_B_PWM_CHANNEL, PWM_CHANNEL_FREQ, PWM_CHANNEL_RESOLUTION);

   // attach the channel to the GPIO2 to be controlled
   ledcAttachPin(MOTOR_PWM_A, MOTOR_A_PWM_CHANNEL);
   ledcAttachPin(MOTOR_PWM_B, MOTOR_B_PWM_CHANNEL);

   ledcWrite(MOTOR_A_PWM_CHANNEL, 0);
   ledcWrite(MOTOR_B_PWM_CHANNEL, 0);   
}
void removeBrake(void)
{
    digitalWrite(MOTOR_BRK_A, LOW);
    digitalWrite(MOTOR_BRK_B, LOW);  
}
void applyBrakes(void)
{
    digitalWrite(MOTOR_BRK_A, HIGH);
    digitalWrite(MOTOR_BRK_B, HIGH);  
}
void speedControl(int speedVal)
{
    ledcWrite(MOTOR_A_PWM_CHANNEL, speedVal);//stop the current rotation first
    ledcWrite(MOTOR_B_PWM_CHANNEL, speedVal);//stop the current rotation first      
}
void motorOperation(String command)
{
    Serial.println(command); 
    speedControl(0);    
    applyBrakes(); 
      
    delay(100);

    if(collisionDetected == false)
    {    
      if(command == "FORWARD")
      {   //Serial.println("forwarding...");
          digitalWrite(MOTOR_DIR_A, MOTOR_DIR_FORWARD); 
          digitalWrite(MOTOR_DIR_B, MOTOR_DIR_FORWARD); 
          removeBrake();  
          speedControl(carSpeed);              
      }
      else if(command == "BACK")
      {        
          digitalWrite(MOTOR_DIR_A, MOTOR_DIR_REVERSE); 
          digitalWrite(MOTOR_DIR_B, MOTOR_DIR_REVERSE); 
          removeBrake();
          speedControl(carSpeed);
       }    
       else if(command == "STOP")
       {
        
       }  
       else if(command == "SPEEDL")
       {
            carSpeed = LOW_SPEED;          
            ledcWrite(MOTOR_A_PWM_CHANNEL, carSpeed);
            ledcWrite(MOTOR_B_PWM_CHANNEL, carSpeed); 
       }
       else if(command == "SPEEDM")
       {         
            carSpeed = MEDIUM_SPEED;
            ledcWrite(MOTOR_A_PWM_CHANNEL, carSpeed);
            ledcWrite(MOTOR_B_PWM_CHANNEL, carSpeed); 
       }
       else if(command == "SPEEDH")
       {
            carSpeed = HIGH_SPEED;          
            ledcWrite(MOTOR_A_PWM_CHANNEL, carSpeed);
            ledcWrite(MOTOR_B_PWM_CHANNEL, carSpeed); 
       }    
    }   
}




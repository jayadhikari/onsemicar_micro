const int MOTOR_ENABLE_A = D3;
const int MOTOR_ENABLE_B = D4;

const int MOTORA_FWD_PIN = D6;
const int MOTORA_REV_PIN = D5;

const int MOTORB_FWD_PIN = D7;
const int MOTORB_REV_PIN = D8;

int speed_A=600,speed_B=600;

void initialiseMotor(void)
{
   pinMode(MOTOR_ENABLE_A, OUTPUT);
   pinMode(MOTOR_ENABLE_B, OUTPUT);
   
   pinMode(MOTORA_FWD_PIN, OUTPUT);
   pinMode(MOTORA_REV_PIN, OUTPUT);
   
   pinMode(MOTORB_FWD_PIN, OUTPUT);
   pinMode(MOTORB_REV_PIN, OUTPUT);

   analogWrite(MOTOR_ENABLE_A, 0);
   analogWrite(MOTOR_ENABLE_B, 0);   
}

void motorOperation(String command)
{
    Serial.println(command);         
   analogWrite(MOTOR_ENABLE_A, speed_A);
   analogWrite(MOTOR_ENABLE_B, speed_B); 
        
    if(command == "FORWARD")
    {                  
        Serial.println("forwarding...");
        digitalWrite(MOTORA_FWD_PIN, HIGH); 
        digitalWrite(MOTORA_REV_PIN, LOW); 
        
        digitalWrite(MOTORB_FWD_PIN, HIGH); 
        digitalWrite(MOTORB_REV_PIN, LOW);  
    }
    else if(command == "BACK")
    {
        digitalWrite(MOTORA_FWD_PIN, LOW); //fwd
        digitalWrite(MOTORA_REV_PIN, HIGH); //fwd
        
        digitalWrite(MOTORB_FWD_PIN, LOW); 
        digitalWrite(MOTORB_REV_PIN, HIGH); 
     }
     else if(command == "LEFT")
     {
        digitalWrite(MOTORA_FWD_PIN, LOW); 
        digitalWrite(MOTORA_REV_PIN, HIGH); 
        
        digitalWrite(MOTORB_FWD_PIN, HIGH); 
        digitalWrite(MOTORB_REV_PIN, LOW); 
     }
     else if(command == "RIGHT")
     {      
        digitalWrite(MOTORA_FWD_PIN, HIGH); 
        digitalWrite(MOTORA_REV_PIN, LOW); 
        
        digitalWrite(MOTORB_FWD_PIN, LOW); 
        digitalWrite(MOTORB_REV_PIN, HIGH);         
     }
     else if(command == "ROTATE")
     {
        digitalWrite(MOTORA_FWD_PIN, HIGH); 
        digitalWrite(MOTORA_REV_PIN, LOW); 
        digitalWrite(MOTORB_FWD_PIN, LOW); 
        digitalWrite(MOTORB_REV_PIN, LOW); 
     }
     else if(command == "STOP")
     {
        analogWrite(MOTOR_ENABLE_A, 0);
        analogWrite(MOTOR_ENABLE_B, 0);
        digitalWrite(MOTORA_FWD_PIN, LOW); 
        digitalWrite(MOTORA_REV_PIN, LOW); 
        digitalWrite(MOTORB_FWD_PIN, LOW); 
        digitalWrite(MOTORB_REV_PIN, LOW); 
     }  
     else if(command == "SPEEDL")
     {
          speed_A = 512;
          speed_B = 512;
          analogWrite(MOTOR_ENABLE_A, speed_A);
          analogWrite(MOTOR_ENABLE_B, speed_B); 
     }
     else if(command == "SPEEDM")
     {
          speed_A = 800;
          speed_B = 800;
          analogWrite(MOTOR_ENABLE_A, speed_A);
          analogWrite(MOTOR_ENABLE_B, speed_B); 
     }
     else if(command == "SPEEDH")
     {
          speed_A = 1000;
          speed_B = 1000;
          analogWrite(MOTOR_ENABLE_A, speed_A);
          analogWrite(MOTOR_ENABLE_B, speed_B); 
     }
     else
     {
        analogWrite(MOTOR_ENABLE_A, 0);
        analogWrite(MOTOR_ENABLE_B, 0);
     }
}

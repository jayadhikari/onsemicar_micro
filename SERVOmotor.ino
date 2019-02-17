#include <Servo.h>

const int servopin = 23;

enum steering_position
{
    POS_STRAIGHT = 75,
    POS_LEFT_30 = 120,
    POS_LEFT_60 = 150,
    POS_RIGHT_30 = 45,
    POS_RIGHT_60 = 15    
};

int steeringAngle = POS_STRAIGHT;

static int steeringPosCount = 0;
static int prevSteeringPosCount = 0;


Servo carSteering;  // create servo object to control a servo

void resetSteering(void)
{
  steeringAngle = POS_STRAIGHT;
  steeringPosCount = 0;
  prevSteeringPosCount = 0;
  carSteering.write(steeringAngle);
}

void servoInit(void) 
{
    carSteering.attach(servopin);  // attaches the servo on pin 13 to the servo object   
    resetSteering();
}


void steeringControl(String command) 
{   
       
    if(command == "LEFT" && steeringPosCount > -2)
    {
       steeringPosCount--;            
    }
    else if(command == "RIGHT" && steeringPosCount < 2)
    {
       steeringPosCount++;     
    }  
    else if(steeringPosCount < -2 || steeringPosCount > 2)
    {
        steeringPosCount = 0;//correct error in steering   
    }

    if(steeringPosCount != prevSteeringPosCount)//no need to rewrite same steering angle 
    {        
        prevSteeringPosCount = steeringPosCount;
        
        if(steeringPosCount == -2)
        {
            steeringAngle = POS_LEFT_60;
        }
        else if(steeringPosCount == -1)
        {
          steeringAngle = POS_LEFT_30;
        }
        else if(steeringPosCount == 0)
        {
            steeringAngle = POS_STRAIGHT;
        }    
        else if(steeringPosCount == 1)
        {
            steeringAngle = POS_RIGHT_30;
        }
        else if(steeringPosCount == 2)
        {
            steeringAngle = POS_RIGHT_60;
        }
                
        if(steeringPosCount >= -2 && steeringPosCount <= 2)
        {
          Serial.print("steering angle: ");
          carSteering.write(steeringAngle);
          Serial.print(steeringAngle);
        }
    }     
}
void steeringAngleControl(String command)
{
    if(command == "RIGHT_30_DEG")
    {
        steeringAngle = POS_RIGHT_30;
    }
    else if(command == "RIGHT_60_DEG")
    {
        steeringAngle = POS_RIGHT_60;
    }
    else if(command == "LEFT_30_DEG")
    {
        steeringAngle = POS_LEFT_30;
    }
    else if(command == "LEFT_60_DEG")
    {
      steeringAngle = POS_LEFT_60;
    }
    else if(command == "STRAIGHT")
    {
       steeringAngle = POS_STRAIGHT;  
    }

    if(steeringAngle <=120 && steeringAngle >= 30 )
    {
        carSteering.write(steeringAngle);
    }
}


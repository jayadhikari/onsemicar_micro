#include <Servo.h>


// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

const int servopin = 23;

void servoInit(void) 
{
    servo1.attach(servopin);  // attaches the servo on pin 13 to the servo object
    servo1.write(75);
}
static boolean left=1, right=0;
int angle =75;
void servoControl(void) 
{
    if(left)
    {
        angle = angle+15;
        if(angle <= 135)
        {
          servo1.write(angle);
          Serial.println(angle); 
        }
        else
        {
          left = 0;right = 1; 
        }
    }
    else if(right)
    {
      
      angle = angle-15;
      if(angle >= 15)
      {
        servo1.write(angle);
        Serial.println(angle); 
      }
      else
      {
          left =1; right = 0;
      }
    }      
}


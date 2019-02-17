const int triggerPin = 33;
const int echoPin = 36;

// defines variables
long duration;

boolean collectSample = true;


int count = 0;

const int SAMPLE_COUNT = 100;
int cmBoxCar[SAMPLE_COUNT];

long microsecondsToInches(long microseconds) 
{
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) 
{
   return microseconds / 29 / 2;
}
void initUltasonicSensor(void)
{
  
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
}
int  getDistance(void)
{
      static int prevCm;
      int cm=0;
      
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH); 
     
      
      // Calculating the distance
      cm = (duration*0.034/2);

      if(collectSample ==  true)
      {//do this for first time only after boot
        cmBoxCar[count++] = cm;
        if(count >=SAMPLE_COUNT)
        {
           collectSample = false; 
        }
      }
      else
      {
        for(count = SAMPLE_COUNT -2; count >= 0; count--)
        {
          cmBoxCar[count+1] = cmBoxCar[count];//shift previous samples further in the array
        } 
        cmBoxCar[0] = cm;//get new sample in first position of array
      }
      
      if(collectSample == false)
      {
        cm = 0;
        for(count =0; count < SAMPLE_COUNT ;count++)
        {
          cm += cmBoxCar[count];
        }
        cm = cm / SAMPLE_COUNT;

        if(prevCm != cm)
        {   
          prevCm = cm;
         // Serial.print("distance cm=");
          //Serial.println(cm);
        }
        
      }     
      
      //Serial.print("distance inches=");
     // Serial.println(inches);
      return (cm);
}



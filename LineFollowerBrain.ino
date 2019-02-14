           
boolean right_outer = 0;
boolean right_inner = 0;
boolean centre = 0;
boolean left_inner = 0;
boolean left_outer = 0;



void read_IRData(void)
{
      /*left0 = adc1_get_raw(ADC1_CHANNEL_0);
      left1 = adc1_get_raw(ADC1_CHANNEL_3);
      centre0 = adc1_get_raw(ADC1_CHANNEL_4);
      centre1 = adc1_get_raw(ADC1_CHANNEL_5);
      right0 = adc1_get_raw(ADC1_CHANNEL_6);
      right1 = adc1_get_raw(ADC1_CHANNEL_7);
*/
      right_outer = 0;
      right_inner = 0;
      centre = 0;
      left_inner = 0;
      left_outer = 0;
      
      right_outer = digitalRead(IR_O1);
      right_inner = digitalRead(IR_O2);
      centre      = digitalRead(IR_O3);
      left_inner  = digitalRead(IR_O4);
      left_outer  = digitalRead(IR_O5);
      
      Serial.print("O1:");
      Serial.print(right_outer);
      Serial.print(" ");
      Serial.print("O2:");
      Serial.print(right_inner);
      Serial.print(" ");
      Serial.print("O3:");
      Serial.print(centre);
      Serial.print(" ");
      Serial.print("O4:");
      Serial.print(left_inner);
      Serial.print(" ");
      Serial.print("O5:");
      Serial.println(left_outer);
      
}
void lineFollowerBrain(void)
{
  static int movDir=STOP,prevMovDir=STOP;

  read_IRData();    
  
  if((left_outer == 0 && left_inner == 0) && (centre == 1) && (right_outer == 0 && right_inner == 0))
  {
    movDir = FORWARD_FAST;
  }
  else if((left_outer == 1 && left_inner == 1) && (centre == 1 ) && (right_outer == 1 && right_inner == 1))
  {
      movDir = STOP;
  }  
  else if((left_outer == 0 && left_inner == 0) && (centre == 0) && (right_outer == 0 && right_inner == 0))
  {    
      movDir = STOP;      
      if(prevMovDir == FORWARD_FAST || prevMovDir == FORWARD_SLOW || prevMovDir == LEFT_SLOW || prevMovDir == LEFT_FAST || prevMovDir == RIGHT_SLOW || prevMovDir == RIGHT_FAST)
      {
            Serial.print("prev mov direction can be used = ");
            Serial.println(prevMovDir);
      }
  }
  else if((left_outer == 0 && left_inner == 1) && (centre == 1 ) && (right_outer == 0 && right_inner == 1))
  {
      movDir = FORWARD_FAST;
  }
  else if(((left_outer == 0 && left_inner == 1) && centre == 1) 
            || ((right_outer == 0 && right_inner == 1 ) && centre == 1))
  {    
      movDir = FORWARD_SLOW;
  }
  else if(((left_outer == 0 && left_inner == 1) && centre == 0 ) || ((left_outer == 1 && left_inner == 1) && centre == 1))
  {    
      movDir = LEFT_SLOW;
  }
  else if(left_outer == 1 && left_inner == 0)
  {    
      movDir = LEFT_FAST;
  }
  else if((right_outer == 0 && right_inner == 1  && centre == 0) || (right_outer == 1 && right_inner == 1  && centre == 1))
  {
      //turn right          
      movDir = RIGHT_SLOW;
  }
  else if(right_outer == 1 && right_inner == 0)
  {
      //turn right          
      movDir = RIGHT_FAST;
  }  

  if(prevMovDir != movDir)
  {//invoke motor command if the motor state has to be changed
    prevMovDir  = movDir;
    switch(movDir)
    {
      case  RIGHT_SLOW:
          motorOperation("RIGHT",50,50); 
      break;   
      case  RIGHT_FAST:
          motorOperation("RIGHT",60,60); 
      break;        
      case   LEFT_SLOW:      
          motorOperation("LEFT",50,50); 
      break;
      case   LEFT_FAST:      
          motorOperation("LEFT",60,60); 
      break;  
      case   FORWARD_SLOW:
          motorOperation("FORWARD",60,60);  
      break;
      case   FORWARD_FAST:
          motorOperation("FORWARD",70,70);  
      break;
      
      case   STOP:
          motorOperation("STOP",0,0);
      break;            
    }
  }    
}

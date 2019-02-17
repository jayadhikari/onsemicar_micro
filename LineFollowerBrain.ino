           

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
      movDir = LEFT_60DEG;
  }
  else if(left_outer == 1 && left_inner == 0)
  {    
      movDir = LEFT_30DEG;
  }
  else if((right_outer == 0 && right_inner == 1  && centre == 0) || (right_outer == 1 && right_inner == 1  && centre == 1))
  {
      //turn right          
      movDir = RIGHT_60DEG;
  }
  else if(right_outer == 1 && right_inner == 0)
  {
      //turn right          
      movDir = RIGHT_30DEG;
  }  

  if(prevMovDir != movDir)
  {//invoke motor command if the motor state has to be changed
    prevMovDir  = movDir;
    
    switch(movDir)
    {
      case  RIGHT_60DEG:
          steeringAngleControl("RIGHT_60_DEG");          
      break;   
      case  RIGHT_30DEG:
          steeringAngleControl("RIGHT_30_DEG");          
      break;        
      case  LEFT_60DEG:
          steeringAngleControl("LEFT_60_DEG");                
      break;
      case  LEFT_30DEG:      
          steeringAngleControl("LEFT_30_DEG");          
      break;  
      case  FORWARD_SLOW:
          steeringAngleControl("STRAIGHT");          
      break;
      case  FORWARD_FAST:
          steeringControl("STRAIGHT");          
      break;      
      case  STOP:
          motorOperation("STOP");
      break;            
    }
    if(movDir != STOP)
    {
      motorOperation("FORWARD"); 
    }
  }    
}

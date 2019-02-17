#include <driver/adc.h>

const int IR_O5 = 14;//
const int IR_O4 = 13;//
const int IR_O3 = 34;//
const int IR_O2 = 35;//
const int IR_O1 = 32;//
const int IR_Calibration = 27;//ADC1_CH7
/****ADC channel 2 of ESP32 is not usable when wifi is active****/

boolean right_outer = 0;
boolean right_inner = 0;
boolean centre = 0;
boolean left_inner = 0;
boolean left_outer = 0;

void initialiseIRSensor(void)
{
   pinMode(IR_O1, INPUT);
   pinMode(IR_O2, INPUT);   
   pinMode(IR_O3, INPUT);
   pinMode(IR_O4, INPUT);     
   pinMode(IR_O5, INPUT);
   pinMode(IR_Calibration, OUTPUT);
}

void read_IRData(void)
{    
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


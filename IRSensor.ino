#include <driver/adc.h>

const int IR_O5 = 14;//
const int IR_O4 = 13;//
const int IR_O3 = 34;//
const int IR_O2 = 35;//
const int IR_O1 = 32;//
const int IR_Calibration = 27;//ADC1_CH7
/****ADC channel 2 of ESP32 is not usable when wifi is active****/




void initialiseIRSensor(void)
{
   pinMode(IR_O1, INPUT);
   pinMode(IR_O2, INPUT);   
   pinMode(IR_O3, INPUT);
   pinMode(IR_O4, INPUT);     
   pinMode(IR_O5, INPUT);
   pinMode(IR_Calibration, OUTPUT);
}


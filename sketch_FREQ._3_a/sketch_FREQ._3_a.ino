/* 
    glovisol - ARDUINO ZERO FREQUENCY/INPUT VOLTAGE 
    / OUTPUT DUTY CYCLE SKETCH EXAMPLE
    Ver.3.0 06/03/2017 --- GENUINO ZERO (c.c.) 
    Provides variable duty cycle squarewave on output pin 7
    modulated by voltage at input pin A5.Frequency adjusted  
    by REG_TCCO_PER and STATIC Duty Cycle (50%)adjusted by  
    REG_TCC0_CCB3 - This sketch: FREQUENCY = 400 Hz;
    ANALOG PIN INPUT = A5; INPUT VOLTAGE RANGE: 0 - 2500 mV; 
    DUTY CYCLE OUTPUT @ PIN 7: 0 - 100% e.g. 0 - 3.3V.
    Klinz action on pin 3 used to check regular sketch load */

#include <Arduino.h>
#include <Freq.h>  
Freq led;

//DECLARE VARIABLES
int ledPin = 3;
int (timex) = 10;

//INPUTS
int sensorValue_5 = A5;
int Vy_5 = 0;


 //OPERATION

void Setting_1 (int HZ)
{
 /*Each timer counts up to a maximum or TOP value set by the PER register,
  this determines the frequency of the PWM operation:
  20000 = 50Hz, 10000 = 100Hz, 2500  = 400Hz, 2702 = 370Hz */
  REG_TCC0_PER = HZ;      // Frequency setting
  while(TCC0->SYNCBUSY.bit.PER);
}

void Setting_2(int PW)
{
 /* The CCBx register value corresponds to the pulsewidth in microseconds (us)*/
    REG_TCC0_CCB3 = PW;       // TCC0 CCB3 - Duyt Cycle setting
  while(TCC0->SYNCBUSY.bit.CCB3);
} 

void loop() 
{
 Setting_1(1000); //Frequency setting
 Setting_2(200); //Static Duty Cycle set @ 50%: e.g. PW =1/2 HZ
 int readValue_5 = analogRead(sensorValue_5);
 Vy_5 = map(readValue_5, 0, 2500, 0, 8000);
 REG_TCC0_CCB3 = Vy_5;      
 while(TCC0->SYNCBUSY.bit.CCB3);
 delay(timex);
 led.klinz(500); 
}



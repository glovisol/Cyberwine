/* 
    glovisol - ARDUINO ZERO FREQUENCY/DUTY CYCLE SKETCH EXAMPLE
    Ver. 2.5 03/03/2017 --- GENUINO ZERO (c.c.) 
    Provides variable duty cycle squarewave on output pin 7. 
    Frequency adjusted  by REG_TCCO_PER and Duty Cycle adjusted 
    by  REG_TCC0_CCB3 - Klinz action on pin 3 used to check regular
    sketch load */

#include <Arduino.h>
#include <Freq.h>  
Freq led;

//DECLARE VARIABLES
int ledPin = 3;
int (timex) = 10;

 //OPERATION
void loop() 
{
 Setting_1(999);
 Setting_2(330);
 led.klinz(500); 
}

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



/*
 * File:   PWM.c
 * Author: Vagner Rodrigues
 *
 * Created on 25 de Fevereiro de 2021, 17:35
 */

#include "PWM.h"
#define _XTAL_FREQ 4000000
#define TMR2PRESCALE 4

void PWM_Init(long freq)
{
  PR2 = (_XTAL_FREQ/(freq*4*TMR2PRESCALE)) - 1;  
}

void PWM1_Duty(unsigned int duty, unsigned int freq)
{ 
  PWM_Init(freq);
  if(duty<1024)
  {    
    duty = ((float)duty/1023.0)*(_XTAL_FREQ/(freq*TMR2PRESCALE));    
    CCP1X = duty & 0b00000010;
    CCP1Y = duty & 0b00000001;
    CCPR1L = (unsigned char)duty>>2;
  }
}

void PWM2_Duty(unsigned int duty, unsigned int freq)
{
  PWM_Init(freq);
  if(duty<1024)
  {
    duty = ((float)duty/1023.0)*(_XTAL_FREQ/(freq*TMR2PRESCALE));
    CCP2X = duty & 0b00000010;;
    CCP2Y = duty & 0b00000001;;
    CCPR2L = (unsigned char)duty>>2;
  }
}

void PWM1_Start(void)
{
  CCP1M3 = 1;
  CCP1M2 = 1;
  #if TMR2PRESCALAR == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALAR == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
  TMR2ON = 1;
  TRISC2 = 0;
}

void PWM2_Start()
{
  CCP2M3 = 1;
  CCP2M2 = 1;
  #if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
  #elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
  #endif
    TMR2ON = 1;
    TRISC1 = 0;
}

void PWM1_Stop(void)
{
  CCP1M3 = 0;
  CCP1M2 = 0;
}

void PWM2_Stop()
{
  CCP2M3 = 0;
  CCP2M2 = 0;
}

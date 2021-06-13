/*
 * File:   adc.c
 * Author: Vagner Rodrigues
 *
 * Created on 24 de Fevereiro de 2021, 21:35
 */

#include "adc.h"
#define _XTAL_FREQ 4000000

void ADC_Init(void)
{
   ADCON1 = 0x80;
   ADCON0 = 0xC1;     
}

unsigned int ADC_Read(unsigned char channel)
{
   if(channel > 7)
     return 0;

   ADCON0 &= 0xC5;
   ADCON0 |= channel<<3;
   __delay_ms(2);
   GO_nDONE = 1;
   while(GO_nDONE);
   return ((unsigned int)(ADRESH<<8)+ADRESL);
}
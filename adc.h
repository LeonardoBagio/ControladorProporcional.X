/* 
 * File:   adc.h
 * Author: Vagner Rodrigues
 *
 * Created on 24 de Fevereiro de 2021, 21:35
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

/*  Protótipo das funções   */ 
void ADC_Init(void);
unsigned int ADC_Read(unsigned char channel);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


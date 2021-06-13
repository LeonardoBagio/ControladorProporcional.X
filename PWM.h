/* 
 * File:   PWM.h
 * Author: Vagner Rodrigues
 *
 * Created on 25 de Fevereiro de 2021, 17:37
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#define TMR2PRESCALE 4

void PWM_Init(long freq);
void PWM1_Duty(unsigned int duty, unsigned int freq);
void PWM1_Start(void);
void PWM1_Stop(void);
void PWM2_Duty(unsigned int duty, unsigned int freq);
void PWM2_Start(void);
void PWM2_Stop(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */


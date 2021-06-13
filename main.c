#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "adc.h"
#include "PWM.h"
#include "lcd.h"
#define _XTAL_FREQ 4000000
#define S1 RB0
#define S2 RB1
#define S3 RB2
#define S4 RB3

int temperatura;
int menu = 1;

int setPoint = 4200;
int kp = 90;
char setPoint_string[32];
char kp_string[32];

const unsigned char digito[10] = {
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00000111, //7
    0b01111111, //8
    0b01101111, //9
};

void atualizaDisplay(unsigned int tempSet){
    int milhar = tempSet/1000;
    int centena = (tempSet%1000)/100;
    int dezena = ((tempSet%1000)%100)/10;
    int unidade = ((tempSet%1000)%100)%10;
    PORTD = digito[milhar];
    RB7 = 1;
    __delay_ms(10);
    RB7 = 0;
    PORTD = digito[centena];
    RB6 = 1;
    __delay_ms(10);
    RB6 = 0;
    PORTD = digito[dezena];
    RB5 = 1;
    __delay_ms(10);
    RB5 = 0;
    PORTD = digito[unidade];
    RB4 = 1;
    __delay_ms(10);
    RB4 = 0;
}

void controlarValores(){
    static char S1Anterior;
    static char S1Atual;
    static char S2Anterior;
    static char S2Atual;
    static char S3Anterior;
    static char S3Atual;
    static char S4Anterior;
    static char S4Atual;    
    
    S1Atual = S1;

    if((S1Atual)&&(!S1Anterior)){
        if (menu != 1){
            setPoint += 100;
        } else {
            kp += 100;
        }
    }

    S1Anterior = S1Atual;
    S2Atual = S2;

    if((S2Atual)&&(!S2Anterior)){
        if (menu != 1){
            setPoint -= 100;
        } else {
            kp -= 100;
        }
    }

    S2Anterior = S2Atual;
    S3Atual = S3;

    if((S3Atual)&&(!S3Anterior)){
        if (menu != 1){
            setPoint += 10;
        } else {
            kp +=10;
        }
    }

    S3Anterior = S3Atual;
    S4Atual = S4;
    
    if((S4Atual)&&(!S4Anterior)){
        if (menu == 1){
            menu = 2;
        } else {
            menu = 1;
        }
    }   
    
    S4Anterior = S4Atual;    
}

int controleMaximoMinimo(int valor){
    if (valor < 0){
        valor = 0;
    }
    
    if (valor > 1023){
        valor = 1023;
    }
    
    return valor;
}

void limpar(){
    lcd_cmd(L_CLR);
}

void iniciarLcd(){
    lcd_init();
    lcd_cmd(L1_digito1);
    lcd_str("TEMP:");
    lcd_cmd(L2_digito1);
    lcd_str("  KP:");
    lcd_cmd(L1_digito6);
}

void imprimirValoresLcd(){
    sprintf(setPoint_string, "%d", setPoint);
    sprintf(kp_string, "%d", kp);
    
    lcd_cmd(L1_digito6);
    lcd_str(setPoint_string);
    lcd_cmd(L2_digito6);
    lcd_str(kp_string);
    
    if (menu != 1){
        lcd_cmd(L1_digito10);
    } else {
        lcd_cmd(L2_digito10);
    }
}

void main(void) {
    TRISA = 0xFF;
    TRISB = 0x0F;
    TRISC = 0x00;
    TRISD = 0x00;
    TRISE = 0x00;
    int cooler;
    float erro;
    float up;
    
    ADC_Init();
    PWM1_Start();
    PWM2_Start();
    iniciarLcd();
    
    while(1){
        controlarValores();
        temperatura = (ADC_Read(0)*10/8 - 150);
        cooler      = (unsigned int)ADC_Read(1);
        erro        = (setPoint/10) - temperatura;
        up          = kp * erro;
        
        cooler      = controleMaximoMinimo(cooler);
        temperatura = controleMaximoMinimo(temperatura);
        up          = controleMaximoMinimo(up);
        
        PWM1_Duty(up, 4000);
        PWM2_Duty(cooler, 4000);
        imprimirValoresLcd();
        //atualizaDisplay(setPoint);
    }
    
    return;
}
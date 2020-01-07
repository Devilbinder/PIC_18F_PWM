#include <xc.h>
#include <pic18f4520.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "conbits.h"

uint16_t pwm_count = 0; 
uint16_t pwm_mode = 0;


void pwm_set(uint16_t duty){
    CCP2CONbits.DC2B = (uint8_t)(duty & 0x0003);
    CCPR2L = (uint8_t)(duty >> 2); 
}

void main(void){
    OSCCONbits.IRCF = 0x07;
    OSCCONbits.SCS = 0x03;
    while(OSCCONbits.IOFS!=1);
    
    TRISB=0;
    LATB=0xFF;
    
    TRISCbits.RC1 = 0;
    
    T2CONbits.T2OUTPS=0;
    T2CONbits.T2CKPS = 0;
    
    PR2=19;
    CCP2CONbits.DC2B = 0;
    CCP2CONbits.CCP2M=0x0C;
    CCPR2L = 0;
    
    T2CONbits.TMR2ON = 1;
   
    while(1){

        if(pwm_mode == 1){
            pwm_count--;
        }
        pwm_set(pwm_count);
        if(pwm_mode == 0){
            pwm_count++;
        }
        __delay_ms(25);
        if(pwm_count >= 0x004F){
            pwm_mode = 1;
        }
        if(pwm_count == 0){
            pwm_mode = 0;
        }
            
        
    } 
}




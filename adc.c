/*
 * File:   adc.c
 * Author: Rahul Chimata, Nico Garcia-Bompadre, Sander Versteele, and Daud Khan
 *
 * Initializes ADCs for photoresistors and joystick, also resets bits every time one is used.
 */

#include "adc.h"
#include "xc.h"

//
//initialize adc
void adc_init_Photo(void) {
    AD1PCFG = 0xFFFF;     
    TRISAbits.TRISA0 = 1;     // RA0 as input (photoresistor 1)
    TRISAbits.TRISA1 = 1;     // RA1 as input (photoresistor 2)
    TRISAbits.TRISA2 = 1;     // RA2 as input (photoresistor 3)
    TRISAbits.TRISA3 = 1;     // RA3 as input (photoresistor 4)
    AD1PCFGbits.PCFG11 = 0;    // AN0 as analog input
    AD1PCFGbits.PCFG12 = 0;    // AN1 as analog input
    AD1PCFGbits.PCFG9 = 0;    // AN9 as analog input
    AD1PCFGbits.PCFG10 = 0;    // AN10 as analog input

    AD1CON2bits.VCFG = 0b000; // Use AVDD/AVSS as references
    AD1CON3bits.ADCS = 0b100; // Tad = 2*Tcy * ADCS<2:0> = 8 * Tcy
    AD1CON1bits.SSRC = 0b111; // Auto-convert after sampling
    AD1CON3bits.SAMC = 16;    // Auto-sample time = 16 * Tad
    AD1CON1bits.FORM = 0b00; // Integer output

    AD1CON1bits.ADON = 1;     // Turn ADC ON
}

//read adc value from desired channel
//inputs: channel for adc (0 for AN0, 1 for AN1, 9 for AN9, 10 for AN10)
//outputs: value red on desired photoresistor
unsigned long read_adc(int channel) {
  AD1CHSbits.CH0SA = channel;
  AD1CON1bits.SAMP = 1;
  while (!AD1CON1bits.DONE);
  AD1CON1bits.SAMP = 0;
  return ADC1BUF0;
}

//initilaize joystick
void adc_init_Joy(void){
    AD1PCFG = 0xFFFF;               // Clear Bits
    AD1PCFGbits.PCFG0 = 0;          // AN0 as analog input
    AD1PCFGbits.PCFG1 = 0;          // AN1 as analog input

    AD1CON1 = 0;                   // Reset ADC control register
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;

    AD1CON1bits.SSRC = 0b010;      // Internal counter (conversion starts automatically)
    AD1CON1bits.ASAM = 1;          // Auto-start sampling
    
    AD1CON2 = 0;
    AD1CON2bits.CSCNA = 1; 
    AD1CON2bits.SMPI = 1;
    
    AD1CON3 = 0;
    AD1CON3bits.SAMC = 1;          // Auto-sample time = 1 TAD
    AD1CON3bits.ADCS = 1;          // ADC conversion clock select
    
    AD1CHS = 0;                    // Connect AN0 to CH0 input (horizontal)
   
    AD1CSSL = 0x03;                // Enable scanning on AN0 and AN1 (horizontal and vertical)
    
    IFS0bits.AD1IF = 0;            // Clear interrupt flag
    IEC0bits.AD1IE = 1;            // Enable ADC interrupt
    AD1CON1bits.ADON = 1;          // Turn on ADC module
}

//Reset ADC1 module
void reset_adc(void) {
    // Turn off the ADC module
    AD1CON1bits.ADON = 0;

    // Reset all ADC1 control registers to their default values
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1CHS = 0;
    AD1CSSL = 0;
    IFS0bits.AD1IF = 0; // Clear ADC interrupt flag
    IEC0bits.AD1IE = 0; // Disable ADC interrupt (optional, but good practice)
}

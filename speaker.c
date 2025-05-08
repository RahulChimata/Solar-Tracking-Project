/*
 * File:   speaker.c
 * Author: svers
 *
 * Created on May 2, 2025, 9:58 AM
 */


#include "xc.h"

void buzzerOn(void) {
    LATBbits.LATB4 = 1; // RB4 high 
}

void buzzerOff(void) {
    LATBbits.LATB4 = 0; // set RB4 low
} 
void delay_us(unsigned int us) {
    for (int i = 0; i < us; i++) {
        asm("repeat #15"); // adjust this value based on clock speed
        asm("nop");
    }
}

void playTone(unsigned int frequency, unsigned int duration_ms) {
    unsigned int period = 1000000 / frequency; // calculate period in microseconds
    unsigned int half_period = period / 2;

    unsigned long numCycles = (unsigned long)duration_ms * 1000 / period;

    for (unsigned long i = 0; i < numCycles; i++) {
        buzzerOn();
        delay_us(half_period); //delay
        buzzerOff();
        delay_us(half_period); 
    }
}


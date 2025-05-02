/*
 * File:   servo.c
 * Author: Rahul Chimata, Nico Garcia-Bompadre, Sander Versteele, and Daud Khan
 *
 * Initialize servos and set them to desried values.
 */

#include "servo.h"
#include "xc.h"

//set up horizontal servo
void initServo1(void) {
    TRISBbits.TRISB6 = 0; // Servo 1 pin as output
    // Timer 3 setup
    T3CON = 0;
    T3CONbits.TCKPS = 0b01; // Prescaler 1:8
    PR3 = 40000 - 1;       // Period for ~20ms
    TMR3 = 0;

    OC1CON = 0;              // Turn off OC1 for now
    OC1R = 1500;             // Initial servo position (center)
    OC1RS = 1500;            // PWM duty cycle
    OC1CONbits.OCTSEL = 0b1; // Use Timer 3 for compare source
    OC1CONbits.OCM = 0b110;  // Output compare PWM w/o faults

    T3CONbits.TON = 1;       // Start Timer 3 for OC1 and OC2
}

//set up vertical servo
void initServo2(void) {
    TRISBbits.TRISB7 = 0; // Servo 2 pin as output
    // Configure OC2
    OC2CON = 0;
    OC2R = 1500;
    OC2RS = 1500;
    OC2CONbits.OCTSEL = 0b1; // Use Timer 3 for compare source (same timer as other OC)
    OC2CONbits.OCM = 0b110;  // Output compare PWM w/o faults
}

//set servo one to angle
//inputs: desired value
void setServo1(int Val) {
    OC1RS = Val;
}

//set servo 2 to angle with output compare 2
//inputs: desired angle
void setServo2(int Val) {
    OC2RS = Val;
}

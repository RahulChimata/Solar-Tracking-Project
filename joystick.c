/*
 * File:   joystick.c
 * Author: Rahul Chimata, Nico Garcia-Bompadre, Sander Versteele, and Daud Khan
 *
 * Set up joystick and corresponding interrupts, also has manual servo control function.
 */

#include "joystick.h"
#include "servo.h"
#include "solar.h"
#include "xc.h"


#define SERVO_MIN 1000
#define SERVO_MAX 5000

volatile unsigned int verticalValue;
volatile unsigned int horizontalValue;


//set up adc ISR
//samples for joystick pos coords
void __attribute__ ((__interrupt__)) _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0;             // Clear ADC1 interrupt flag
    
    // Read ADC results
    horizontalValue = ADC1BUF0;    // Read ADC result from AN0 for Horizontal
    verticalValue = ADC1BUF1;      // Read ADC result from AN1 for Vertical
}

// Timer2 Interrupt Service Routine (ISR)
//activates ADC when overflow happens
void __attribute__ ((__interrupt__)) _T2Interrupt(void){
    _T2IF = 0;                      // Clear Timer2 interrupt flag
    AD1CON1bits.SAMP = 1;           // Start ADC sampling
}

//set bits for joystick initialization
void joyStickSetup(){
    CLKDIVbits.RCDIV = 0;
    
    // Button initializer 
    TRISAbits.TRISA3 = 1;   // Set RA3 as input for the button press
    CNPU2bits.CN29PUE = 1;
    
    // I2C Setup
    I2C1CONbits.I2CEN = 0;         // Disable I2C1
    I2C1BRG = 0x9D;                // Set I2C1 Baud Rate to 100kHz
    _MI2C1IF = 0;                  // Clear I2C1 interrupt flag
    
    // Timer 2 Setup 
    T2CON = 0;
    TMR2 = 0;
    _T2IF = 0;
    T2CONbits.TCKPS = 0b10;        // Prescaler 1:64
    PR2 = 24999;                   // Value for interrupt (1 ms)
    IEC0bits.T2IE = 1;             // Enable Timer2 interrupt
    T2CONbits.TON = 1;             // Start Timer2
}

// Declare persistent position variables
static unsigned long curPos1 = SERVO_MIN;
static unsigned long curPos2 = SERVO_MAX / 2 + 700;

//manually control servos with joystick
void manualServo() {
    // Control Servo 1 with vertical (up/down)
    if (verticalValue > 600 && curPos1 < SERVO_MAX) {
        curPos1 += 30;
        
    } else if (verticalValue < 400 && curPos1 > SERVO_MIN) {
        curPos1 -= 30;
    }

    // Control Servo 2 with horizontal (left/right)
    if (horizontalValue > 600 && curPos2 < SERVO_MAX) {
        curPos2 += 30;
    } else if (horizontalValue < 400 && curPos2 > (SERVO_MAX / 2 + 700)) {
        curPos2 -= 30;
    }
    
    //set servos to desired position
    setServo1(curPos1);
    setServo2(curPos2);
    
    //reset adc to read lightscan, wait 5 s
    if(PORTAbits.RA3 == 0) {
        reset_adc();
        adc_init_Photo();
        lightScan();
        curPos1 = getPos1();
        curPos2 = getPos2();
        delay(5000);
    }
}

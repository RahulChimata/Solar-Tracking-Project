/*
 * File:   Final_Main.c
 * Author: Rahul Chimata, Nico Garcia-Bompadre, Sander Versteele, and Daud Khan
 *
 * Main function, sets up PIC and runs code.
 */

#include "xc.h"
#include "stdio.h"
#include "servo.h"
#include "adc.h"
#include "joystick.h"
#include "solar.h"


// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1             // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF           // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF             // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF              // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF           // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI          // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF          // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON          // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME         // Clock Switching and Monitor (Clock switching is enabled,
                                        // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL         // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

// Define servo limits
#define SERVO_MIN 1000
#define SERVO_MAX 5000


//set up PIC board
void setup(void) {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; // All digital inputs and outputs

    // Configure PPS for Servo 1
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR3bits.RP6R = 18;  // Use Pin RP6 for Output Compare 1 = "18"
    // Configure PPS for Servo 2)
    RPOR3bits.RP7R = 19 ; // Use Pin RP7 for Output Compare 2 = "19"
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
}

int main(void) {
    setup();
    initServo1();
    initServo2();
    adc_init_Joy();
    joyStickSetup();
    
    setServo1(SERVO_MIN);
    setServo2(SERVO_MAX / 2 + 700);
    
    while(1){
        delay(10);

        manualServo();      //start with manual servo movement
    }

    return 0;
}

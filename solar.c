/*
 * File:   solar.c
 * Author: Rahul Chimata, Nico Garcia-Bompadre, Sander Versteele, and Daud Khan
 *
 * Does the light scan, where device rotates fully and moves to brightest position.
 */

#include "solar.h"
#include "servo.h"
#include "adc.h"
#include "xc.h"

// Define servo limits
#define SERVO_MIN 1000
#define SERVO_MAX 5000

volatile unsigned long highPos1 = SERVO_MIN;
volatile unsigned long highPos2 = SERVO_MAX;

//get position of horizontal servo
unsigned long getPos1(){
    return highPos1;
}

//get position of vertical servoE
unsigned long getPos2(){
    return highPos2;
}
//delay function
//input: desired amount of ms
void delay(int ms) {
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < 1600; j++);
    }
}

// Does a Default Scan to find brightest light position
void lightScan(){
    
    unsigned long max_voltage1 = 0;
    unsigned long max_voltage2 = 0;
    highPos1 = SERVO_MIN;
    highPos2 = SERVO_MAX;
    int curPos = SERVO_MIN;
    
    unsigned long getVoltage;
    
    setServo1(SERVO_MIN);
    setServo2(SERVO_MAX / 2 + 700);

    //:::::::::::::::::::::SERVO 1:::::::::::::::::::::::::::::::::::::::::::::::::::
    //move thru each servo val from 1000 to 5000
    for (curPos = SERVO_MIN; curPos <= SERVO_MAX; curPos += 25) {
        setServo1(curPos);
        delay(10);
        getVoltage = read_adc(9) + read_adc(12) + read_adc(11) + read_adc(10);
        if (getVoltage > max_voltage1) {          //check if light is brighter than before
            max_voltage1 = getVoltage;
            highPos1 = curPos;                    //save location of brightest light
        }
        delay(10);

        //backup emergency move (prevent extra movement)
        if (curPos > SERVO_MAX) {
            curPos = SERVO_MIN;
        }
        
    }
    
    //set servo to where light detected
    setServo1(highPos1);

    //::::::::::::::::::::::SERVO 2:::::::::::::::::::::::::::::::::::::::::::::::::::
    //move thru each servo val from 180 deg to 90
    for (curPos = SERVO_MAX / 2 + 700; curPos <= SERVO_MAX; curPos += 25) {
        setServo2(curPos);
        delay(10);
        getVoltage = read_adc(9) + read_adc(12) + read_adc(11) + read_adc(10);
        if (getVoltage > max_voltage2) {          //check if light is brighter than before
            max_voltage2 = getVoltage;
            highPos2 = curPos;                    //save location of brightest light
        }
        delay(10);

    }
    
    //set servo to where light was detected
    setServo2(highPos2);
    
    //delay(5000);
    
    //reset adc to read joystick values
    reset_adc();
    adc_init_Joy();
}

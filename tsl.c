#include <p24FJ64GA002.h>

#include "tsl.h"
#include "stdint.h"
#define I2C_READ_ERROR 0xFFFF

void tslInit2561(){
    tslWrite(0x80, 0b00000011);
}

uint16_t tslRead2561(uint16_t command){
    uint8_t dataLow = 0;
    uint8_t dataHigh = 0;
    uint16_t dataFull;
    
    // Start Condition
    I2C2CONbits.SEN = 1; 
    while(I2C2CONbits.SEN);
    
    // Slave Address + Wr bit = 0
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01010010 ; // Slave Address 0b0101001 + 0, Using Ground Address
    while (!IFS3bits.MI2C2IF || I2C2STATbits.TRSTAT);
    
    // Command Code
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = command ; // Register of Interest to read from
    while(!IFS3bits.MI2C2IF ||  I2C2STATbits.TRSTAT);
    
    // Slave Address + Rd bit = 1
    I2C2CONbits.RSEN = 1; 
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01010011 ; // Slave Address 0b0101001 + 1
    while (!IFS3bits.MI2C2IF || I2C2STATbits.TRSTAT);
    
//    // Receive
//    I2C2CONbits.RCEN = 1; 
//    while(!I2C2STATbits.RBF);
//    dataLow = I2C2RCV;
//    
//    // First Ack
//    I2C2CONbits.ACKDT = 0;
//    I2C2CONbits.ACKEN = 1;
//    while(I2C2CONbits.ACKEN);
    
    
    // Receive
    I2C2CONbits.RCEN = 1; 
    while(!I2C2STATbits.RBF);
    dataHigh = I2C2RCV;
    
    // Second Ack
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
    while(I2C2CONbits.ACKEN);
   
    // End Conditions
    IFS3bits.MI2C2IF = 0; 
    I2C2CONbits.PEN = 1; 
    while(I2C2CONbits.PEN);
//    dataFull = ((uint16_t)dataHigh << 8) | dataLow;
    return dataHigh;
}


void tslInit2591(){
    tslWrite(0xA0, 0x03);
}

uint8_t tslRead2591(uint8_t command){
    uint8_t dataFull;
    
    // Start Condition
    I2C2CONbits.SEN = 1; 
    while(I2C2CONbits.SEN);
    
    // Slave Address + Wr bit = 0
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01010010 ; // Slave Address 0b0101001 + 0, Using Ground Address
    while (!IFS3bits.MI2C2IF || I2C2STATbits.TRSTAT);
    
    // Command Code
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = command ; // Register of Interest to read from
    while(!IFS3bits.MI2C2IF ||  I2C2STATbits.TRSTAT);
    
    // Slave Address + Rd bit = 1
    I2C2CONbits.RSEN = 1; 
    
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01010011 ; // Slave Address 0b0101001 + 1
    while (!IFS3bits.MI2C2IF || I2C2STATbits.TRSTAT);
    
    // Receive
    I2C2CONbits.RCEN = 1; 
    while(!I2C2STATbits.RBF);
    dataFull = I2C2RCV;
    
    
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
    while(I2C2CONbits.ACKEN);
   
    // End Conditions
    IFS3bits.MI2C2IF = 0; 
    I2C2CONbits.PEN = 1; 
    while(I2C2CONbits.PEN);
    
    return dataFull;
}

void tslWrite(uint8_t Reg, uint8_t command){
    // Start Condition
    I2C2CONbits.SEN = 1; 
    while(I2C2CONbits.SEN);
    
    // Slave Address
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01010010 ; // Slave Address 0b0101001 + 0, Using Ground Address, Setting Write high
    while (!IFS3bits.MI2C2IF || I2C2STATbits.TRSTAT);
    
    // Command Code
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Reg ; // Register of Interest to Write to
    while(!IFS3bits.MI2C2IF ||  I2C2STATbits.TRSTAT);
    
    // Data Byte 
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = command ; // Command to write
    while(!IFS3bits.MI2C2IF ||  I2C2STATbits.TRSTAT);
    
    // End Conditions
    IFS3bits.MI2C2IF = 0; 
    I2C2CONbits.PEN = 1; 
    while(I2C2CONbits.PEN);
}




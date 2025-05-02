/* 
 * File:   servo.h
 * Author: rahul
 *
 * Created on May 1, 2025, 6:03 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif

void initServo1(void);

void initServo2(void);

void setServo1(int Val);

void setServo2(int Val);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

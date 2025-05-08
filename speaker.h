/* 
 * File:   speaker.h
 * Author: svers
 *
 * Created on May 2, 2025, 9:58 AM
 */

#ifndef SPEAKER_H
#define	SPEAKER_H

#ifdef	__cplusplus
extern "C" {
#endif
    void buzzerOn(void);
    void buzzerOff(void);
    void delay_us(unsigned int us);
    void playTone(unsigned int frequency, unsigned int duration_ms);
    




#ifdef	__cplusplus
}
#endif

#endif	/* SPEAKER_H */


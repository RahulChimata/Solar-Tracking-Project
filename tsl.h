/* 
 * File:   tsl.h
 * Author: rahul
 *
 * Created on April 17, 2025, 2:50 PM
 */

#ifndef TSL_H
#define	TSL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void tslInit2561();
    
    uint16_t tslRead2561(uint16_t command);
    
    void tslWrite(uint8_t Reg, uint8_t command);

    void tslInit2591();
    
    uint8_t tslRead2591(uint8_t command);
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* TSL_H */



#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void adc_init_Photo(void);

unsigned long read_adc(int channel);

void adc_init_Joy(void);

void reset_adc(void); 

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

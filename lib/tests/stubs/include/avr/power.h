
#ifndef _AVR_POWER_H_
#define _AVR_POWER_H_

#include<stdint.h>

#define power_adc_disable()
#define power_spi_disable()
#define power_timer0_disable()
#define power_timer1_disable()
#define power_timer2_disable()
#define power_twi_disable()

extern uint8_t SLEEP_MODE_PWR_DOWN;
extern uint8_t SLEEP_MODE_IDLE;

#endif //_AVR_POWER_H_


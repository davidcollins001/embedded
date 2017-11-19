
#include "sleep.h"


void sleep_now(unsigned char mode) {
    set_sleep_mode(mode);

    // power down services
    power_adc_disable();
    power_spi_disable();
    power_timer0_disable();
    power_timer1_disable();
    power_timer2_disable();
    power_twi_disable();

    sleep_enable();
    sleep_mode();

    // just woken up, yawn
    sleep_disable();
}


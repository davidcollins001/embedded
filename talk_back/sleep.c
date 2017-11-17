
#include "sleep.h"


void sleep_now(unsigned char mode) {
    set_sleep_mode(mode);

    // TODO: power down services

    sleep_enable();
    sleep_mode();

    // just woken up, yawn
    sleep_disable(); 
}


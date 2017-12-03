
#include "wdt.h"

uint8_t WDCE = 0x1;
uint8_t WDRF = 0x2;

uint8_t WDTO_8S = 0x1;

void wdt_enable(int mode) {}
void wdt_disable() {}
void wdt_reset() {}


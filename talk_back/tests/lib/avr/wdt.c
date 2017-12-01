
#include "wdt.h"

unsigned char WDCE = 0x1;
unsigned char WDRF = 0x2;

unsigned char WDTO_8S = 0x1;

void wdt_enable(int mode) {}
void wdt_disable() {}
void wdt_reset() {}


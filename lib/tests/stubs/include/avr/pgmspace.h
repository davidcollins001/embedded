
#ifndef AVR_PGMSPACE_
#define AVR_PGMSPACE_

// #include "../io.h"

#define PSTR(name) name

char pgm_read_byte(const char *data);
// char pgm_read_byte(const char *data) {
   // return *data;
// }

#endif //AVR_PGMSPACE_


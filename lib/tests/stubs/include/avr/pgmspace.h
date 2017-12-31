
#ifndef _AVR_PGMSPACE_H_
#define _AVR_PGMSPACE_H_

// #include "../io.h"

#define PSTR(name) name

char pgm_read_byte(const char *data);
// char pgm_read_byte(const char *data) {
   // return *data;
// }

#endif //_AVR_PGMSPACE_H_


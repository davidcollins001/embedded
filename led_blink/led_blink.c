
#include <avr/io.h>
#include <inttypes.h>

#include "../libnerdkits/delay.h"
#include "../libnerdkits/lcd.h"

// PIN DEFINITIONS:    
// //                     
// // PC4 -- LED anode    

int main(void) {

	// set portc as output
	DDRC |= (1 << PC4);


	while(1) {

		// switch led on
		PORTC |= (1 << PC4);
		delay_ms(500);

		// switch led off
		PORTC &= ~(1 << PC4);
		delay_ms(100);

	}


	return 0;
}

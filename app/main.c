#define F_CPU 16000000L /* CPU Clock speed */

#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#define LED_TOGGLE_DELAY 500

#define HIGH 0xFF

int main(void)
{
	/* Set all on PORTB as outputs */
	DDRB = HIGH;

	while(true){
		PORTB |= 1 << PB7;
		_delay_ms(LED_TOGGLE_DELAY);

		PORTB &= 0 << PB7;
		_delay_ms(LED_TOGGLE_DELAY);
	}
}

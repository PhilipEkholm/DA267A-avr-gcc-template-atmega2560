#define F_CPU 16000000L

#include <stdbool.h>

#include <avr/io.h>
#include <util/delay.h>

#define HIGH 0xFF
#define LOW 0x00

#define LED_TOGGLE_DELAY 500

int main(void)
{
	DDRC = HIGH;

	while(true){
		PORTC = HIGH;
		_delay_ms(LED_TOGGLE_DELAY);

		PORTC = LOW;
		_delay_ms(LED_TOGGLE_DELAY);
	}
}
//LED-blink for 8 LEDs 2 at a time
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRD=0b11111111;
    /* Replace with your application code */
    while (1) 
    {
		
		PORTD=0b10000001;
		_delay_ms(1000);
		PORTD=0b01000010;
		_delay_ms(1000);
		PORTD=0b00100100;
		_delay_ms(1000);
		PORTD=0b00011000;
		_delay_ms(1000);
		PORTD=0b00000000;
		_delay_ms(1000);
    }	
}
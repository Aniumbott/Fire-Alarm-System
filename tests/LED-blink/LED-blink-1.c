//Program to blink one LED
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRD=0B11111111;
    /* Replace with your application code */
    while (1) 
    {
		
		PORTD=0b00000001;
		_delay_ms(1000);
	   	PORTD=0b00000000;
	    	_delay_ms(1000);
    }
}

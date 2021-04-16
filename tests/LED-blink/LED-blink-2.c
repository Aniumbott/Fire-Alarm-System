//Same as LED-blink-1.c but another method
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void)
{
	DDRD |= 1<< PIND0;
    while (1) 
{
		
		DDRD^=1<<PIN0;
		_delay_ms(1000);
    }
}

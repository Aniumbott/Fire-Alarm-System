//If logic toggler set to 1 LED will glow.
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

int main()
{
	DDRD = 0b00000001;
	DDRA = 0b00000000;
	while (1)
	{
		if (bit_is_set(PINA,0))
		PORTD=0b00000001;
		else
		PORTD=0b00000000;
	}
}

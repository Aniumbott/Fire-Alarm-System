//If we set logic toggler to 1 messeg "Smoke Ditected" will be sent to the entered Mob. No.
#define F_CPU 8000000UL                        
#include <string.h>
#define BAUD_PRESCALE (((F_CPU / (9600 * 16UL))) - 1)
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

void UART_init(long UART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);                 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1)|(0<<UMSEL);         
	UBRRL = BAUD_PRESCALE;                     
	UBRRH = (BAUD_PRESCALE >> 8);                           
}

void uart_tx(char x)
{
	// Wait until the Transmitter is ready
	while (! (UCSRA & (1 << UDRE)) );
	UDR = x;
}
void uart_msg(char c[])                           
{
	int i = 0;
	for ( i=0; i < strlen(c); i++)
	{
		uart_tx (c[i]);
	}
}

int main (void)
{
	UART_init(9600);
	_delay_ms(500);
	while (1)
	{
		if (bit_is_set(PINA,0))
		{
			uart_msg("AT\r");
			_delay_ms(500);
			uart_msg ("AT+CMGF=1\r");
			_delay_ms(500);
			uart_msg ("AT+CMGS =  +91 6354129548\rSmoke Detected.\x1A");
		break;
		}
		
	
		else if (bit_is_set(PINC,0))
		{
			uart_msg("AT\r");
			_delay_ms(500);
			uart_msg ("AT+CMGF=1\r");
			_delay_ms(500);
			uart_msg ("AT+CMGS =  +91 6354129548\rRise in the temprature is observed.\x1A");
		break;
		}
	
		
		else if ((bit_is_set(PINA,0))&&(bit_is_set(PINC,0)))
		{
			uart_msg("AT\r");
			_delay_ms(500);
			uart_msg ("AT+CMGF=1\r");
			_delay_ms(500);
			uart_msg ("AT+CMGS =  +91 6354129548\rFire is Detected.\x1A");
		break;
		}
	}
}

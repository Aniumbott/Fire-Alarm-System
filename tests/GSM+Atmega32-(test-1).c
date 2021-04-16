//Programe 
#define F_CPU 8000000UL		
#include <string.h>
#define BAUD_PRESCALE (((F_CPU / (9600 * 16UL))) - 1)
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>
void USART_init(long USART_BAUDRATE)
{
		UCSRB |= (1 << RXEN) | (1 << TXEN);	
		UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1)|(0<<UMSEL);
		UBRRL = BAUD_PRESCALE;			
		UBRRH = (BAUD_PRESCALE >> 8);		
}
void usart_tx(char x)
{
	
		while (! (UCSRA & (1 << UDRE)) );
		UDR = x;
}
void usart_msg(char c[])
{
		int i = 0;
		for ( i=0; i < strlen(c); i++)
		{
			usart_tx (c[i]);
		}
}
int main (void)
{
		int a=13;
		USART_init(9600);
		_delay_ms(1000);
		usart_msg("AT\r");
		_delay_ms(1000);

}


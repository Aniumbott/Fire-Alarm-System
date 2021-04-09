/*
 * GccApplication1.cpp
 * Author : RP
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000UL
#define baud_prescale (((F_CPU/(BAUD*16UL)))-1)
void uart_init (long BAUD)
{
	UBRRH = (baud_prescale>>8);
	UBRRL = baud_prescale;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0)|(0<<UMSEL);
	
}
unsigned char uart_Receive( void )
{
	while ( !(UCSRA & (1<<RXC)) );
	return UDR;
}

int main ( void )
{
	uart_init (9600);
}


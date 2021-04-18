#define F_CPU 8000000UL
#define TRIGPOINT 128
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
	
	int b=0,a=0,b1=0,a1=0;
	
	DDRD = 0b00000001;
	DDRA = 0b00000000;
	ADMUX = 0b01100000;
	ADCSRA = 0b10000111;

	uart_msg("AT\r");
	_delay_ms(500);
	uart_msg ("AT+CMGF=1\r");
	_delay_ms(500);

while (1)
	{
		ADCSRA = ADCSRA | (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		if(ADCH > 55)
		{
			b=1;
		}
		
		a = bit_is_set(PINB,0);

		if ((a==1)&&(b==0)&&(a1==0))
		{
			uart_msg ("AT+CMGS =  +91 1234567890\rSmoke Detected.\x1A\r");
			a1=1;
		}
		
		
		else if ((b==1)&&(a==0)&&(b1==0))
		{
			uart_msg ("AT+CMGS =  +91 1234567890\rRise in the temperature is observed.\x1A\r");
			b1=1;
		}
		

		else if ((a==1)&&(b==1))
		{
			uart_msg ("AT+CMGS =  +91 1234567890\rFire is Detected.\x1A\r");
			break;
		}
		a=0;
		b=0;
		_delay_ms(5000);
	}
}

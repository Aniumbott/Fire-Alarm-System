#ifndef USART
#define USART

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#define USART_BAUDRATE 9600

#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include <avr/interrupt.h>

 void send_char(char* sendString);
 void init_usart(void);
 void send_byte( unsigned char data );
 void SendString(char *StringPtr);
 uint8_t receive(void);
 unsigned char * uartrecieve();
 
unsigned char *x;

void send_char(char* sendString)
{
	for (int i = 0; i < strlen(sendString); i++)
	{
		while (( UCSR0A & (1<<UDRE0))  == 0){};
		UDR0 = sendString[i];
	}
}

void init_usart(void)
{
	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
}

void send_byte( unsigned char data )
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

uint8_t receive(void)
{
	// Wait for byte to be received
	while(!(UCSR0A&(1<<RXC0))){};
	// Return received data
	return UDR0;
}

void SendString(char *StringPtr)
{
	while(*StringPtr != '\0')
	{
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE0)) );
		/* Put data into buffer, sends the data */
		UDR0 = *StringPtr;
		StringPtr++;
	}
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = *StringPtr;
}

unsigned char * uartrecieve()
{
	while ( !(UCSR0A & (1<<RXC0)) );
	while(UDR0 != '\0')
	{
		*x = UDR0;
		x++;
		while ( !(UCSR0A & (1<<RXC0)) );
	}
	*x = UDR0;
	return x;
}

#endif //USART
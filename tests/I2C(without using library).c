#define F_CPU 8000000UL
#include <string.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

void I2C_Init()
{
	TWBR = 0x48;
}

uint8_t I2C_Start(char write_address)
{
	uint8_t status;
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	status=TWSR&0xF8;
	if(status!=0x08)
	return 0;
	TWDR=write_address;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	status=TWSR&0xF8;
	if(status==0x18)
	return 1;
	if(status==0x20)
	return 2;
	else
	return 3;
}

uint8_t I2C_Read_Ack()
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}

uint8_t I2C_Read_Nack()
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}

uint8_t I2C_Repeated_Start(char read_address)
{
	uint8_t status;
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	status=TWSR&0xF8;
	if(status!=0x10)
	return 0;
	TWDR=read_address;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	status=TWSR&0xF8;
	if(status==0x40)
	return 1;
	if(status==0x48)
	return 2;
	else
	return 3;
}


uint8_t I2C_Write(char data)
{
	uint8_t status;
	TWDR=data;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	status=TWSR&0xF8;
	if(status==0x28)
	return 0;
	if(status==0x30)
	return 1;
	else
	return 2;
}

void I2C_Stop()
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
	while(TWCR&(1<<TWSTO));
}

void blink_led ()
{
	DDRD = 0b11111111;
	PORTD = 0b00000001;
	_delay_ms(1000);
	PORTD = 0x00;
	_delay_ms(1000);
}

int main(void)
{
	int MSB, LSB , data;
	I2C_Init();
	while(1)
	{
		if ( I2C_Start (0xEE) == 1)
		{
			if ( I2C_Write (0xF6) == 0)
			{
				if ( I2C_Repeated_Start (0xEF) == 1)
				{
					MSB = I2C_Read_Ack();
					LSB = I2C_Read_Nack();
				}
			}
		}
		I2C_Stop();
		if (MSB > 8 )
		{
			blink_led ();
		}
	}
}

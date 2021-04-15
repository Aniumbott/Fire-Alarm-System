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

char I2C_Read_Ack()  				
{
    TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); 	
    while(!(TWCR&(1<<TWINT))); 			
    return TWDR;           				
}

char I2C_Read_Nack()   				
{
    TWCR=(1<<TWEN)|(1<<TWINT);  		
    while(!(TWCR&(1<<TWINT))); 			
    return TWDR;       					
}

uint8_t I2C_Repeated_Start(charread_address) /* I2C repeated start function */
{
    uint8_t status;		/* Declare variable */
    TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);/* Enable TWI, generate start */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    status=TWSR&0xF8;		/* Read TWI status register */
    if(status!=0x10)		/* Check for repeated start transmitted */
    return 0;			/* Return 0 for repeated start condition fail */
    TWDR=read_address;		/* Write SLA+R in TWI data register */
    TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    status=TWSR&0xF8;		/* Read TWI status register */
    if(status==0x40)		/* Check for SLA+R transmitted &ack received */
    return 1;			/* Return 1 to indicate ack received */
    if(status==0x48)		/* Check for SLA+R transmitted &nack received */
    return 2;			/* Return 2 to indicate nack received */
    else
    return 3;			/* Else return 3 to indicate SLA+W failed */
}

void blink_led ()
{
	DDRD = 0b11111111;
	while (1)
	{
		PORTD = 0b00000001;
		_delay_ms(100);
	}
}

int main(void)
{
        int start;
	Char data;
    	I2C_Init();
	start = I2C_Start(0xEE);
        data = I2C_Read_Ack();
        If (data != '0')
	blink_led();
}

/*
 * Description:    i2c lib
 * Name:           i2c.c
 * Reference:      www.jump.to/fleury
 * Created:        16.1.2018
 * Author:         Ali Gholami
 * License:        Open-source 
 * Core:           8 bit ATMEL_MiCROCHIP
 * Last update:    8.2.2018
 * Test Des:       OK for atmega328p,8mhz
 * Website:        https://atmels.wordpress.com/
 */ 

#include <avr/io.h>
#include<util/twi.h>
#include "i2c.h"
#define F_CPU 8000000
#define F_SCL  100000 //100 kHz
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)
void init_i2c(void)
{
  /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
  
TWBR = (uint8_t)TWBR_val ;
}/* i2c_init */


uint8_t i2c_start(uint8_t addr)
{

	TWCR = 0;
	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START){ }
	
	// load slave address into data register
	TWDR = (addr);
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) ;
	
}


void i2c_stop(void)
{
    /* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));
}/* i2c_stop */


/*************************************************************************
  Send one byte to I2C device
  Input:    byte to be transfered
  Return:   0 write successful 
            1 write failed
*************************************************************************/
uint8_t i2c_write(uint8_t byte_data)
{	
    uint8_t   twst;
    
	// send data to the previously addressed device
	TWDR = byte_data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;
}/* i2c_write */

/*************************************************************************
 Read one byte from the I2C device, request more data from device 
 
 Return:  byte read from I2C device
*************************************************************************/
uint8_t i2c_readAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;
}/* i2c_readAck */

/*************************************************************************
 Read one byte from the I2C device, read is followed by a stop condition 
 
 Return:  byte read from I2C device
*************************************************************************/
uint8_t i2c_readNack(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;
}/* i2c_readNak */


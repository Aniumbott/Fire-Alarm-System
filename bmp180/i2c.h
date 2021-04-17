/*
 * Description:    i2c lib
 * Name:           i2cmaster.h
 * Reference:      www.jump.to/fleury
 * Created:        16.1.2018
 * Author:         Ali Gholami
 * License:        Open-source 
 * Core:           8 bit ATMEL_MiCROCHIP
 * Last update:    8.2.2018
 * Test Des:       OK for atmega328p,8mhz
 * Website:        https://atmels.wordpress.com/
 */ 

#ifndef I2C_H_
#define I2C_H_

void    init_i2c(void);
void    i2c_stop(void);
uint8_t i2c_start(uint8_t addr);
uint8_t i2c_write(uint8_t byte_data);
uint8_t i2c_readAck(void);
uint8_t i2c_readNack(void);

#endif /* I2C_H_ */
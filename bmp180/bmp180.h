/*
 * Description:    bmp180 lib for Atmel studio "temperature and pressure sensor"
 * Name:           BMP180.h
 * Reference:      www.controleverything.com
 * Created:        14.01.2018
 * Author:         Ali Gholami
 * License:        Open-source 
 * Core:           8 bit ATMEL_MiCROCHIP
 * Last update:    3.02.2018
 * Test Des:       OK for atmega328p,8mhz
 * Website:        https://atmels.wordpress.com/
 */ 

#ifndef BMP180_H_
#define BMP180_H_

#define BMP180_ADDR_w              0xEE
#define BMP180_ADDR_r              0xEF
#define	BMP180_REG_CONTROL         0xF4
#define	BMP180_REG_RESULT          0xF6
#define	BMP180_COMMAND_TEMPERATURE 0x2E
#define	BMP180_COMMAND_PRESSURE0   0x34
#define	BMP180_COMMAND_PRESSURE1   0x74
#define	BMP180_COMMAND_PRESSURE2   0xB4
#define	BMP180_COMMAND_PRESSURE3   0xF4

typedef struct
{
	float ctemp;
	float ftemp;
	float pressure;
	float altitude;
}bmp180;

//functions
void init_bmp180();
void bmp180_get_data(bmp180 *out);


#endif /* BMP180_H_ */
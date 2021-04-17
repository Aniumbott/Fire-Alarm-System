#define F_CPU 8000000
#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include "bmp180.h"
#include "i2c.h"
int coff[11] = {0};
unsigned int AC4 = 0, AC5 = 0, AC6 = 0;
unsigned int data[3] = {0};


void init_bmp180()
{
	  for (int i = 0; i < 11; i++)
	  {
		  i2c_start(BMP180_ADDR_w);
		  i2c_write((170 + (2 * i)));
		  i2c_stop();

		  i2c_start(BMP180_ADDR_r);
			  data[0] = i2c_readAck();
			  data[1] = i2c_readNack();
		      i2c_stop();

		  _delay_ms(50);
		  coff[i] = data[0] * 256 + data[1];
		  if ((coff[i] > 32767) && (i != 3) && (i != 4) && (i != 5))
		  {
			  coff[i] -= 65536;
		  }
	  }
	   AC4 = coff[3];
	   AC5 = coff[4];
	   AC6 = coff[5];
	   _delay_ms(300); 
}

void bmp180_get_data(bmp180 *out)
{

	 i2c_start(BMP180_ADDR_w);
	 i2c_write(BMP180_REG_CONTROL);     // Select measurement control register
	 i2c_write(BMP180_COMMAND_TEMPERATURE);                 // Enable temperature measurement
	 i2c_stop();
	 _delay_ms(100);

	 i2c_start(BMP180_ADDR_w);
	 i2c_write(BMP180_REG_RESULT); // Select data register
	 i2c_stop();


	i2c_start(BMP180_ADDR_r);
	 data[0] = i2c_readAck();
	 data[1] = i2c_readNack();
    i2c_stop();

	 // Convert the data
	 float temp = ((data[0] * 256.0) + data[1]);

	 i2c_start(BMP180_ADDR_w);
	 i2c_write(BMP180_REG_CONTROL); // Select measurement control register
	 i2c_write(BMP180_COMMAND_PRESSURE1);// Enable pressure measurement, OSS = 1
	 i2c_stop();
	 _delay_ms(100);
	 
	 i2c_start(BMP180_ADDR_w);
	 i2c_write(BMP180_REG_RESULT); // Select data register
     i2c_stop();
	 // Request 3 bytes of data
	i2c_start(BMP180_ADDR_r);
	data[0] = i2c_readAck();
	data[1] = i2c_readAck();
	data[2] = i2c_readNack();
    i2c_stop();   

	 // Convert the data
	 long long pres = (((long long)data[0] * (long long)65536) + ((long)data[1] * 256) + data[2]) / 128;

	 // Calibration for Temperature
	 double X1 = (temp - AC6) * AC5 / 32768.0;
	 double X2 = ((double)coff[9] * 2048.0) / (X1 + coff[10]);
	 double B5 = X1 + X2;
	 float cTmp = ((B5 + 8.0) / 16.0) / 10.0;
	 float fTmp = cTmp * 1.8 + 32;

	 // Calibration for Pressure
	 double B6 = B5 - 4000;
	 X1 = (coff[7] * ((long)B6 * (long)B6 / 4096.0)) / 2048.0;
	 X2 = coff[1] * B6 / 2048.0;
	 double X3 = X1 + X2;
	 double B3 = (((coff[0] * 4 + X3) * 2) + 2) / 4.0;
	 X1 = coff[2] * B6 / 8192.0;
	 X2 = (coff[6] * ((long)B6 * (long)B6 / 2048.0)) / 65536.0;
	 X3 = ((X1 + X2) + 2) / 4.0;
	 double B4 = AC4 * (X3 + 32768) / 32768.0;
	 long long B7 = (((unsigned long long )pres - (unsigned long long )B3) * ((unsigned long long )25000.0));
	 float pressure = 0.0;
	 if (B7 < 2147483648)
	 {
		 pressure = (B7 * 2) / B4;
	 }
	 else
	 {
		 pressure = (B7 / B4) * 2;
	 }
	 X1 = (pressure / 256.0) * (pressure / 256.0);
	 X1 = (X1 * 3038.0) / 65536.0;
	 X2 = ((-7357) * pressure) / 65536.0;
	 pressure = (pressure + (X1 + X2 + 3791) / 16.0) / 100;

	 // Calculate Altitude
	 float height = 44330 * (1 - pow((pressure / 1013.25), 0.1903));
	 out->ctemp=cTmp;
	 out->ftemp=fTmp;
	 out->pressure=pressure;
	 out->altitude=height;
}
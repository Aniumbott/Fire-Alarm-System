
#define  F_CPU 8000000
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "i2c.h"
#include "bmp180.h"
#include "usart.h"
void make_data();
bmp180 get_data;
char msg[64];
char ct[8],ft[8],a[8],p[8];
   
int main(void)
{
	
    init_i2c();
    init_bmp180();
    while (1) 
    {
       make_data();
	   _delay_ms(500);		
    }
}


void make_data()
{
		  bmp180_get_data(&get_data);
		  dtostrf(get_data.ctemp,2,2,ct);
		  dtostrf(get_data.altitude,2,2,a);
		  dtostrf(get_data.ftemp,2,2,ft);
		  dtostrf(get_data.pressure,2,2,p);
		
		strcat(msg,"Temp: ");
		strcat(msg,ct);   
		strcat(msg," *C");

		strcat(msg," Temp: ");  
		strcat(msg,ft);   
		strcat(msg," *F");
		
		strcat(msg," Pressure:" );  
		strcat(msg,p);   		
		strcat(msg," Pa");
		
		strcat(msg," Altitude: ");  
		strcat(msg,a);
		strcat(msg," meter");		

		send_char(msg);
		SendString("\n");
		memset(msg,0,64);
}

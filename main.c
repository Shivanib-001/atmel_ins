/*
 * multi_point_path.c
 *
 * Created: 24-10-2024 10:50:48
 * Author : sumit.chatterjee
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lcd.h"
#include "rtc.h"
#include "uart.h"
#include "nmea.h"
#ifndef F_CPU
#define F_CPU 16000000UL
#endif


/*------------------------- FUNCTIONS ----------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

double va_spd =0.0;

double out_spd,hypdis;

int kfix=0;
char fdat[32]={'\0'};
uint32_t clk_t=0;

ISR(TIMER0_OVF_vect){
	clk_t+=1;
	
}

int main(void)
{
    /* Replace with your application code */
	 UART_init(BaudRate(9600));

	 /*------------------------- CLOCK GENERATION ---------------------------------*/
	 TCCR0A =0x00;
	 TCCR0B |= (1<<CS01);
	 TIMSK0 |= (1<<TOIE0);
	 sei();
	 /*-----------------------------------------------------------------------------*/
	 PORTD &= (1 << PIND2)| (1 << PIND3) ;

	 
	 long int dat,tis;
	 double magk; /*return the float value of Magnetic heading*/
	 char * netLat='\0';
	 char * netLng='\0';
	 char * dirLat='\0';
	 char * dirLng='\0';
	 char * netspd='\0';
	 char * timk='\0';
	 char * dati='\0';
	 char * cou='\0';
	 char * magi='\0';


    while (1) 
    {
		id_vtg(&netLat,&netLng,&dirLat,&dirLng,&netspd,&timk,&dati,&cou,&magi);
               
			va_spd = atof(netspd);
			dat = atol(dati);
			tis = atol(timk);
			hypdis = atof(cou);
			magk = atof(magi);


			if(va_spd != 0.0  && hypdis != 0.0){
			
				sprintf(fdat,"H: %.2f ",hypdis);
				WriteString(fdat);

				
				out_spd = 1.852*va_spd;
				sprintf(fdat,"S: %.2f \n",out_spd);
				WriteString(fdat);
					
			}
		
    }
}




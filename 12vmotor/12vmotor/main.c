#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char speed = 0;
volatile char speed2 =0;
int state = 0;
char arr[10];
int i=0;


void DC_Motor(int speed)
{
	if(speed<  0) speed=  0;
	if(speed>100) speed=100;
	OCR1A=speed;
	OCR1B=0;
}

unsigned int distance;


void ready(void)
{
	TCCR1B=0x1A;
	TCCR1A=0x82; // 모터1
	OCR1A=50; // 모터 1
	
	ICR1=100;
	

}


int main(void)
{
	DDRB=0xf0;

	ready();
	while(1)
	{

		DC_Motor(100);
		_delay_ms(1000);
		DC_Motor(80);
		_delay_ms(1000);
		DC_Motor(50);
		_delay_ms(1000);
		DC_Motor(0);
		_delay_ms(1000);
		
	}

}
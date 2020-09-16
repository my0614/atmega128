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

void DC_Motor2(int speed2)
{
	if(speed2 < 0) speed2 = 0;
	if(speed2 > 100) speed2 = 100;
	OCR3A = speed2;
	OCR3B = 0;
}
unsigned int distance;


void ready(void)
{
	TCCR1B=0x1A;
	TCCR1A=0x82; // 모터1
	OCR1A=50; // 모터 1
	
	ICR1=100;
	
	
	OCR3A = 50; // 모터2

	TCCR3B = 0x1A;
	TCCR3A = 0x82;
	ICR3 = 100;
}


int main(void)
{
	DDRC = 0xff;
	int i,value=0;
	DDRB=0xf0;
	DDRE = 0x08;
	DDRC = 0xff;
	int toggle = 0;

	
	ready();

	value = 60;
	DC_Motor(value);
	
	while(1)
	{


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

char rx_char(void)
{
	while((UCSR0A & 0x80) == 0);
	return UDR0;
}

void tx_char(char tx_char)
{
	while((UCSR0A & 0x20)==0);
	UDR0 = tx_char; // 송신받을 값
}

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

void bluetooth(void)
{
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 103;
}

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
	
	

	ready();
	bluetooth();
	value = 80;
	while(1)
	{
		char txt=0;
		 txt = rx_char();
		 tx_char(txt);
		 
		if(txt == 'L')
		{
			PORTA  = 0x02;
			DC_Motor(0);
			DC_Motor2(80);
			//_delay_ms(1000);
			memset(arr,0,10);
		}
		
		if(txt == 'R')
		{
			PORTA  = 0x0F;
			DC_Motor(80);
			DC_Motor2(0);
			// _delay_ms(1000);
			
			memset(arr,0,10);
		}
		
		if(txt == 'F')
		{
			if(OCR1A == 0 || OCR3A == 0)
				value = 80;
			PORTA  = 0x00;
			DC_Motor(value);
			DC_Motor2(value);
			// _delay_ms(1000);
			memset(arr,0,10);
		}
		
		if(txt == 'B')
		{
			//if(OCR1A == 0 || OCR3A == 0)
				//value = 80;
			PORTA  = 0xFF;
			DC_Motor(80);
			//OCR3B = 80;
			DC_Motor2(80);
			//OCR1B = 80;
			
			memset(arr,0,10);	
		}
		
		if(txt == 'U') // 속도만 바꿔줌
		{
			value += 20;
			if(value >= 120) // 최대 speed
			{
				value = 100;
				PORTC = 0x00;
			}
			else
				PORTC = 0xff;
			PORTA  = 0xFF;
			memset(arr,0,10);
		}
		
		if(txt == 'D') // 속도만 바꿔줌
		{
			value -= 20;
			if(value <= 20) // 최대 speed
			{
				value = 20;
			}
			
			PORTA  = 0xFF;
			memset(arr,0,10);
		}
		
		if(txt == 'S')
		{
			PORTA  = 0xFF;
			DC_Motor(0);
			
			DC_Motor2(0);
			
			_delay_ms(1000);
			memset(arr,0,10);
		}
		
	}
}
~


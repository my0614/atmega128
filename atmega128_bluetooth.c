#include <avr/io.h>
#include <avr/interrupt.h>
#define  F_CPU  16000000UL
#include <util/delay.h>
volatile char speed=0;
volatile unsigned char flag; // 블루투스 변수

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

int num[10] = {
	
	0b11111001, //1
	0b10100100,// 2
	0b10110000 // 3
	
	
};

void DC_Motor(int speed)
{
	if(speed<  0) speed=  0;
	if(speed>100) speed=100;
	OCR1A=speed;
}

int Timer_Init(void)
{
	TCCR3A = (1 << COM3A1) | (1 << WGM11);
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31) | (1 << CS30);
	ICR3 = 4999; // ICR1 set to TOP
	OCR3A = 375; // 0 degree
	TCNT3 = 0X00; // Strating point
}

int main(void)
{	
	DDRD = 0xff;
	PORTD = 0xff;
	char txt;
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 103;
	int i, j = 0;
	DDRB=0xF0;
	DDRE = 0x08;
	TCCR1A=0xA2;		// 0010, Channel A- Enable
	TCCR1B=0x1A;		// 1100 -> 0010 + 1100 = 1110 -> Fast PWM, 64 presclaer
	OCR1A=0;			// DC
	OCR1B=0;			// Servo
	ICR1=100;
	Timer_Init();
	while(1)
	{
		txt = rx_char();
		tx_char(txt);
		
		if(txt == '1')
		{
			for(i=0;i<=100;i++) { DC_Motor(i); _delay_ms(100); }
			for(i=100;i>=0;i--) { DC_Motor(i); _delay_ms(100); }
			
		}
		/*
		OCR3A = 200;
		_delay_ms(400);
		
		OCR3A = 400;
		_delay_ms(400);
		
		OCR3A = 600;
		_delay_ms(400);

		OCR3A = 500;
		_delay_ms(400);
		
		for(int j = 0; j<3;j++)
		{
				PORTD = num[j];
				_delay_ms(1000);
		}
	*/
		
	}
	
}

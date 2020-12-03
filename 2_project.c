#define F_CPU 16000000UL
#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int blue=0, red=0, green=0;
int state = 0;
char arr[15];
int i=0;

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) |	(1<<RXCIE0);
}

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

ISR(USART0_RX_vect)
{
	unsigned char buf = UDR0;
	switch(buf)
	{
		case 0x02 : state = 1; return;
		case 0x03 : state = 0; i = 0;break;
	}
	
	if(state == 1)
	{
		arr[i] = buf;
		i++;
	}
}


unsigned int toggle = 0;

void main()
{
	DDRF=0x00;          // PD0 = sensor
	PORTF=0xff;
	DDRD=0xff;            // PB = LED
	PORTD = 0xff;
	sei();
	
	int count= 0;
	while(1)
	{
		// 터치센서 감지
		if((PINF & 0x01) == 0)
		{
			count++;
			_delay_ms(1500);
			break;
					
		}
		//적외선센서
		if((PINF & 0x02) == 0)
		{
			count++;
			_delay_ms(1500);
			break;
		}
		
		//볼스위치센서
		if((PINF & 0x04) == 0)
		{
			count++;
			_delay_ms(1500);
			break;
		}
		// 부저 2초간 delay
		if(count >= 3)
		{
			PORTD = 0x00;
			_delay_ms(2000); 
		}
}

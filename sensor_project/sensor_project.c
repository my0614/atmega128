


/*
 * sensor_project.c
 *
 * Created: 2020-10-22 오전 9:13:08
 * Author : MY
 */ 



#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1<<RXCIE0);
} // 8bit, no parity, 1 stop bit, TX enable, RX ISR enable

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	// wait for sending
	UDR0 = data; // send
}

void uart_string(char* str)
{
	while (*str)
	uart_write(*str++);
}

ISR(USART0_RX_vect)
{
	unsigned char buf = UDR0;
	uart_write(buf - 'a' + 'A');
}



void seting()
{
	DDRC=0x00;      // PC0 : soundsensor
	PORTC=0xff;
	DDRA = 0x00;
	DDRD = 0xff; // LED
	PORTD = 0xff;
	DDRG = 0x00;
	PORTG = 0xff; // 삼색LED
	
	
}

unsigned int sensor_count =0;
int toggle = 0;

int main(void)
{
	seting(); // port설정함수	
	uart_init(BAUDRATE(9600));

	sei();
		uart_string("hello");
	while(1)
	{
		char str[5] = {0,};
		if(sensor_count >= 3)
		{
				
			PORTA = 0xff;
		}
		if(!(PINC & 0x01)) // PINC0번
		{
			toggle = 1; // sound_sensor는 toggle 1번
		}
		
		
		if(!(PINC & 0x02))
		{
			toggle = 2;	// 노크모듈은 toggle 2번
		}
		
		
		
		switch(toggle)
		{
			case 1 :
			sensor_count++; toggle = 0; PORTD=0x01; _delay_ms(100); break;
			case 2 :
			sensor_count++; toggle = 0; PORTD = 0x02; _delay_ms(100);  break;
			
		}
		sprintf(str, "%d  ",sensor_count); // 문자열로 변환
		uart_string(str);
		
		
		
		
	}
}


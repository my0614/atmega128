
#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int state = 0;
char arr[10];
int i=0;
void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) |			(1<<RXCIE0);
}

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

int main(void)
{
	DDRA = 0xff;
	uart_init(BAUDRATE(9600));
	sei();
	while(1)
	{
		
				if(strcmp(arr,"L1OFF") ==0)
				{
					PORTA = 0x01;
					memset(arr,0,10);
				}
				
				if(strcmp(arr,"L1ON") ==0)
				{
					PORTA = 0x02;
					memset(arr,0,10);
				}
				
				if(strcmp(arr,"L2OFF") ==0)
				{
					PORTA = 0xfc;
					memset(arr,0,10);
				}
				
				if(strcmp(arr,"L2ON") ==0)
				{
					PORTA = 0xff;
					memset(arr,0,10);
					
				}
				
				if(strcmp(arr,"L3OFF") ==0)
				{
					PORTA = 0x0f;
					memset(arr,0,10);
					
				}
				
				if(strcmp(arr,"L3ON") ==0)
				{
					PORTA = 0x04;
					memset(arr,0,10);
				}
				
		_delay_ms(500);
				
			
	}
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

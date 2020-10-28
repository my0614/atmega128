#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile int tone;
char f_table[9] = {17, 43, 66, 77, 97, 114, 127, 137, 255};
int i=-1;

ISR(TIMER0_OVF_vect)
{
	PORTB ^= 1 << 5;
	TCNT0 = f_table[tone];
}

int main()
{
	DDRG = 0x00;
	DDRB = 0x20;
	TCCR0 = 0x03;
	TIMSK = 0x01;
	OCR0 = 128;
	sei();
	tone = 8;
	while (1)
	{
		while(PING & 0x01)
		{
			i++;
			tone = i;
			_delay_ms(3000);
		}
	}
}

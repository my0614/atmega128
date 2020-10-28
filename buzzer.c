#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB = 0x20;
	ICR1 = 783;
	OCR1A = 784;
	TCCR1A = 0xC2;
	TCCR1B = 0x1D;
	
	while(1)
	{
		OCR1A = 391;
		_delay_ms(3000);
		OCR1A = 784;
		_delay_ms(3000);	
	}


}

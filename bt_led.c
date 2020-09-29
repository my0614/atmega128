#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{

	DDRC  = 0xff; // 출력모드
	DDRB = 0x00; // 입력모드
	unsigned int toggle =0;
	PORTA  = 0xff;
	while (1)
	{
		if((PINB & 0x01) == 0) // 1
		{
			toggle = 1;
		}
		
		if((PINB & 0x02) == 0) //2
		{
			toggle = 2;
		}
		
		if((PINB & 0x04) == 0) //2
		{
			toggle = 3;
		}
		if((PINB & 0x08) == 0) //2
		{
			toggle = 4;
		}
		
		if((PINB & 0x10) == 0) // 1
		{
			toggle = 5;
		}
		
		if((PINB & 0x20) == 0) //2
		{
			toggle = 6;
		}
		
		if((PINB & 0x40) == 0) //2
		{
			toggle = 7;
		}
		if((PINB & 0x80) == 0) //2
		{
			toggle = 8;
		}
		

		switch(toggle)
		{
			case 1: PORTC = 0x01; _delay_ms(1000); break;
			case 2: PORTC = 0x02; _delay_ms(1000); break;
			case 3: PORTC = 0x04; _delay_ms(1000); break;
			case 4: PORTC = 0x08; _delay_ms(1000); break;
			case 5: PORTC = 0x10; _delay_ms(1000); break;
			case 6: PORTC = 0x20; _delay_ms(1000); break;
			case 7: PORTC = 0x40; _delay_ms(1000); break;
			case 8: PORTC = 0x80; _delay_ms(1000); break;
			
		}
		
	}
}

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{

	DDRC = 0xff; // 출력모드
	int led = 0x01;
	PORTC = 0xff; // 모두 전원 off
	_delay_ms(1000);
	while (1)
	{
		for(int i=0;i<8;i++)
		{
			PORTC = ~(0x01 << i);
			_delay_ms(1000);
			
		}
		PORTC = 0xff;
		_delay_ms(1000);
		for(int i=7;i>=0;i--)
		{
			PORTC = ~(0x01 << i);
			_delay_ms(1000);
			
		}
		_delay_ms(1000);
		
		
		
	}
}

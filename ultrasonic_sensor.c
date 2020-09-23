#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL
int main(void)
{
	unsigned int distance;
	
	DDRC = 0xff;
	DDRE = ((DDRE | (1<<TRIG)) & ~(1<<ECHO));
	
	while(1)
	{
		
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE & (1<<ECHO)));
		TCNT1 = 0x0000;
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);

		//음파의 속도는 340m/s 이므로 1cm를 이동하는데 약 29us.
		// 4/2 = 왕복거리
		if(distance < 30)
		{
			
				PORTC = 0x01;
				_delay_ms(100);
			
			
		}
		 else if(distance <= 70)
		 {
			
				PORTC = 0x02;
				_delay_ms(100);
		} 
		else if(distance <= 100 )
		{
			
			PORTC = 0x04;
			_delay_ms(100);
		}
		else if(distance <= 130)
		{
			
			PORTC = 0x08;
			_delay_ms(100);
		}
		else if(distance <= 200)
		{
			
			PORTC = 0x10;
			_delay_ms(100);
		}
		
		
		else if(distance > 210)
		{
			
			PORTC = 0x20;
			_delay_ms(100);
		}
		

			_delay_ms(100);
		
	}
}
		

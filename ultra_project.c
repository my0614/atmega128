#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

void buzzer()
{
	DDRG =0xff; //부저사용한 포트
	//1초동안 부저 울리기
	PORTG = 0xff;
	_delay_ms(1000);
	PORTG = 0x00;
	_delay_ms(1000);

}

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

		//음파의 속도는 340m/s 이므로 1cm를 이동하는데 약 29us.
		// 4/2 = 왕복거리
		if(distance <= 50)
		{	
			PORTC = 0xff;
			_delay_ms(100);
			buzzer();
		}
		else if(distance <= 80)
		{
			PORTC = 0x07;
			_delay_ms(100);
		}
		else if(distance <= 100 )
		{
			PORTC = 0x03;
			_delay_ms(100);
		}
		else if(distance <= 130)
		{
			PORTC = 0x01;
			_delay_ms(100);
		}
		_delay_ms(10); //
	
	}
}

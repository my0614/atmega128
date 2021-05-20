#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 0
#define ECHO 1
#define SOUND_VELOCITY 340UL

void buzzer()
{
	DDRB =0xff; //부저사용한 포트
	//1초동안 부저 울리기
	PORTB = 0xff;
	_delay_ms(1000);
	PORTB = 0x00;
	_delay_ms(1000);

}

int main(void)
{
	unsigned int distance;

	//DDRD = 0xff;
	//DDRD = ((DDRE | (1<<TRIG)) & ~(1<<ECHO)); // 초음파센서

	while(1)
	{
		DDRD = 0xff;
		DDRD = ((DDRE | (1<<TRIG)) & ~(1<<ECHO)); // 초음파센서
		
		TCCR1B = 0x03;
		PORTD &= ~(1<<TRIG);
		_delay_us(10);
		PORTD |= (1<<TRIG);
		_delay_us(10);
		PORTD &= ~(1<<TRIG);
		while(!(PIND & (1<<ECHO)));
		TCNT1 = 0x0000;
		while(PIND & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);

		//음파의 속도는 340m/s 이므로 1cm를 이동하는데 약 29us.
		// 4/2 = 왕복거리
		if(distance <= 50)
		{
			PORTD = 0x10;
			_delay_ms(100);
			buzzer();
		}
		else if(distance <= 80)
		{
			PORTD = 0x30;
			_delay_ms(100);
		}
		else if(distance <= 100 )
		{
			PORTD = 0x70;
			_delay_ms(100);
		}
		else if(distance <= 130)
		{
			PORTD = 0xf0;
			_delay_ms(100);
		}
		_delay_ms(10); //

	}
}

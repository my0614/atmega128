#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 0
#define ECHO 1
#define SOUND_VELOCITY 340UL

unsigned char arr[4]={0x10,0x20,0x40,0x80}; // led

void buzzer()
{
	DDRB =0xff; //부저사용한 포트
	//1초동안 부저 울리기
	PORTB = 0xff;
	_delay_ms(500);
	PORTB = 0x00;
	_delay_ms(500);

}


int main(void)
{
	unsigned int dis,i;
	int toggle = 0;
	DDRF=0x00; //버튼입력
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
		dis = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);
		
		// 일정한 거리 감지되면 모터 정지
		if(dis <= 80)
		{
			toggle = 2;
		}
		// 시작버튼
		if((PINF & 0x10) == 0)
		{
			toggle = 1;
			buzzer();
		}
		// 스탑버튼
		if((PINF & 0x20) == 0)
		{
			toggle = 2;
			buzzer();
		}
		if(toggle == 1)
		{
			// led 반복하기
			for(i=0;i<4;i++)
			{
				PORTD = arr[i];
				_delay_ms(500);
				
			}
			
		}
		if(toggle == 2)
		{
			PORTD = 0x00;
			
		}
		
		
	}
}

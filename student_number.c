#include <avr/io.h>

#include <util/delay.h>

#define F_CPU 16000000UL

unsigned char array1[4] = {0x4f,0x4f,0x3f,0x66}; // 학번 ->2643
unsigned char array2[4] = {0x01,0x02,0x04,0x08}; // fnd 자리

int main(void)

{
	
	DDRC = 0xFF; // 값
	DDRG = 0xff; // 4자리수
	PORTC = 0xff;
	PORTG= 0x0f;
	// 학번 2643이므로 홀수 (숫자  5출력)
	while(1)
	{
		for(int i=0;i<4;i++)
		{
			PORTG =  array2[i]; // 자리
			PORTC = array1[i];
			_delay_ms(2);
					
		}
	}
	
	return 0;

}

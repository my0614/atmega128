#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

volatile toggle = 0; // 거실 버튼 1
volatile toggle2 = 0; // 거실 버튼 2
volatile state = 100; // 0과 1이 아닌 다른 숫자

void ready()
{
	DDRE = 0xff;
	PORTE = 0xff;
	DDRC = 0xff;
	PORTC = 0xff;
	DDRF = 0xff;
	PORTF = 0xff;
	
	
}
int main(void)
{
	ready();
    /*버튼 전체는 portA에 LED는 각 port*/
    while (1) 
    {
		
		
		// 거실 LED버튼 절반씩 켜기
		if((PINE & 0x01) == 0) // 거실 버튼 0번
		{
			toggle = ~toggle;	
			state = toggle;
		}
		
		
		if((PINE & 0x02) == 0) // 거실 버튼 1번
		{
			toggle2 = ~toggle2;
			if(toggle2 == 0)
				state = 3;
			else
				state = 1;

			
		}
		
		if((PINE &0x04) == 0)
		{
			state = 4;
		}
		
		if((PINE &0x08) == 0)
		{
			state = 5;
		}
	
		
		// 거실 switch문
		switch(state)
		{
			case 0 :
			PORTC = 0xf0; // 절반 on
			break;
			case 1 : 
			PORTC = 0xff; // 버튼 off
			break;
			case 3 :
			PORTC = 0x0f; // 절반 on
			break;
			case 4 :
			PORTF = 0x00;
			break;
			case 5:
			PORTF = 0xff;
			break;
			
		
		}
		
		
	
		
		
		
		
    }
}



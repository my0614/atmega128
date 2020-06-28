
#define F_CPU 16000000UL
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int num[10] = {
	0b11000000,
	0b11111001,
	0b10100100,
	0b10110000,
	0b10011001,
	0b10010010,
	0b10000010,
	0b11111000,
	0b10000000,
	0b10010000
	
};




int main(void)
{
 
	DDRE= 0xff;
	DDRB = 0xff;
	int cnt=0, su=0;
	int toggle=11;

	while(1)
	{
		if((PIND & 0x01) == 0)
		{
			toggle = 0;
		}
		else if((PIND & 0x02) == 0)
		{
			toggle = 1;
		}
		
		if(toggle == 0)
		{
			su++;
			if(su%50==0) {
				cnt++;
				if(cnt>99)  cnt=0;
			}
		}
		
		if(toggle == 1)
		{
			su++;
			if(su%50==0) {
				cnt--;
				if(cnt<0)  cnt=99;
			}
		}	
		PORTB = 0x01; // 일의 자리
		PORTE = num[cnt/10];
		_delay_ms(5);
		
		PORTB = 0x02; //십의 자리
		PORTE= num[cnt%10];
		_delay_ms(5);
			
			
	}
}

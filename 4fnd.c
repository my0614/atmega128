#include <avr/io.h>

#include <util/delay.h>

#define F_CPU 16000000UL



int number[10] = {0b00111111,

	0b00000110,

	0b01011011,

	0b01001111,

	0b01100110,

	0b01101101,

	0b01111101,

	0b00100111,

	0b01111111,

0b01101111// 9




};



int main(void)

{

	DDRE = 0xFF; // 값

	DDRD = 0xff; // 4자리수
	PORTE = 0xff;
	PORTD= 0x0f;
	unsigned char thou= 0 , hund = 0, ten= 0, one=0; // 자리값 변수
	unsigned count = 0;
	
	while(1)
	{
		thou = count/1000;
		hund =count/100%10;
		ten = count/10%10;
		one = count%10;
		
		for(int i=0;i<10;i++)
		{
			PORTD = 0x01;
			PORTE = number[thou];
			_delay_ms(1);
			
			PORTD  = 0x02;
			PORTE = number[hund];
			_delay_ms(1);
			
			PORTD = 0x04;
			PORTE = number[ten];
			_delay_ms(1);	
			
			PORTD = 0x08;
			PORTE = number[one];
			_delay_ms(1);
			
		
		
		}
		if(count == 9999) // 65535
		{
			
			count = 0; // count 초기화
		}
	}
		

	

	return 0;

}

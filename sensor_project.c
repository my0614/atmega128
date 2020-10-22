/*
 * sensor_project.c
 *
 * Created: 2020-10-22 오전 9:13:08
 * Author : MY
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void seting()
{
	DDRC=0x00;      // PC0 : soundsensor
	PORTC=0xff;
	DDRA = 0x00;
	PORTA = 0x00; // 노트센서 입력
	DDRD = 0xff; // LED
	PORTD = 0xff;
	DDRG = 0x00;
	PORTG = 0xff; // 삼색LED
	
	
}

unsigned int sensor_count =0;
int toggle = 0;
int main(void)
{
	seting(); // port설정함수	
	
	while(1)
	{
		if(!(PINC & 0x01)) // PINC0번
		{
			toggle = 1; // sound_sensor는 toggle 1번
		}
		
		
		if(!(PINC & 0x02))
		{
			toggle = 2;	// 노크모듈은 toggle 2번
		}
		
		
		
		switch(toggle)
		{
			case 1 :
			sensor_count++; toggle = 0; PORTD=0x01; break;
			case 2 :
			sensor_count++; toggle = 0; PORTD = 0x02; break;
			
		}
		if(sensor_count == 1)
		{
			
			
		}
		
		
		
	}
}


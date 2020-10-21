#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


unsigned int toggle = 0;

void main()
{
	DDRF=0x00;          // PD0 = Sound Sensor
	PORTF=0xff;
	DDRD=0xff;            // PB = LED
	int count= 0;
	while(1)
	{
		
		if(!(PINF & 0x01))
		{
			count++;
			for(int i=0;i<count;i++)
			{
				
				PORTD=count;
				_delay_ms(100);
				
				if((PINA & 0x01) == 0)
				{
					toggle = 1;
					break;
					
				}
			}
			
			
		}
		

		
		if((PINA & 0x01) == 0)
		{
			toggle = 1;
			PORTD = 0x00;
			_delay_ms(100);
			count = 0;
			
		}
		if(toggle == 1)
		{
			PORTD = 0x00;
			_delay_ms(1000);
			toggle=0;
			count=0;
			
		}
	}

}


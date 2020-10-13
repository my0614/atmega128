
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>




unsigned char  number[16] = {
0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6,0xEE, 0x3E, 0x9C, 0x7A, 0x9E, 0x8E
};



int main(void)
{
	DDRE = 0xFF; // 값
	DDRD = 0xff; // 4자리수
	DDRC = 0xff; // led
	for(int i=0; i<4; i++)
	{
		PORTD = (0<<i);
		PORTE = number[0];
	}

	while(1)
	{

		for(int i=0;i<16;i++)
		{


			for(int j=0;j<16;j++)
			{


				for(int k=0;k<16;k++)
				{


					for(int p=0;p<16;p++)
					{

						PORTD = 0x10;
						PORTE = number[i];
						_delay_ms(5);
						PORTD = 0x20;
						PORTE = number[j];
						_delay_ms(5);
						PORTD = 0x40;
						PORTE = number[k];
						_delay_ms(5);
						PORTD = 0x40;
						PORTE = number[p];
						_delay_ms(5);


					}

					_delay_ms(10);

				}
				_delay_ms(10);
			}
			_delay_ms(10);
		}

	}

	return 0;

}

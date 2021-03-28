include <avr/io.h>

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

    DDRA = 0xFF; // 세그먼트데이터핀

    DDRG = 0b00001111; // 세그먼트자릿수

    int dp = 0b10000000;

    int flag = 0b00000000;

	while(1){

		for (int a=3 ; a<13 ; a++){

			for (int k=0 ; k<50 ; k++){

				for (int i=0 ; i<4 ; i++){

					PORTA = student_number[(a-i)%10]|(dp&flag);

					flag = ~flag;

					PORTG = ~(0b1<<i);

					_delay_ms(100);

				}
            }
			flag = ~flag;
		}
	}
	return 0;

}

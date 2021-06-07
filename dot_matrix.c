// ATmega128의 레지스터 등이 정의되어 있음
#include<avr/io.h>
 
// _delay_ms() 함수 등이 정의되어 있음
#include<util/delay.h>
 
char Y[] = {
        0B10000010,
        0B01000100,
        0B00101000,
        0B00010000,
        0B00010000,
        0B00010000,
        0B00010000,
        0B00010000
    };

char G[] = {
        0B00000000,
        0B00000000,
        0B11111110,
        0B10010000,
        0B10010000,
        0B10011110,
        0B11010010,
        0B01111110
    };

char G[] = {
        0B11111111,
        0B10000001,
        0B11111111,
        0B10100000,
        0B10010000,
        0B10001000,
        0B10000100,
        0B10000010
    };

int show(char name)
{
	DDRA = 0B11111111;
    DDRC = 0B11111111;
	unsigned char i;        // 8비트의 변수 선언
	 for(i = 0; i < 8; i++){
            // 8비트의 ROWS 신호 중 1비트만 논리 1로 출력
            PORTC = (1<<(i));
            // COLS 신호에 데이터 출력
            PORTA = name[i]; 
            _delay_ms(2);    // 2ms 동안 대기
        }
}

// C 언어의 주 실행 함수
int main(void){
	DDRD = 0xff; // led 출력 (G :0x01, Y:0x02, R:0x04)
	DDRF = 0x00; // 버튼 입력

    while(1){
       PORTD = 0x01; //G led
	   _delay_ms(10000);
	   PORTD = 0x02; //Y led
	   _delay_ms(2000);
	   PORTD = 0x04; //R led
	   _delay_ms(10000);

		if((PINF & 0x01) == 0) // 버튼을 클릭했으면
		{
			PORTD = 0x02; // Y led
			_delay_ms(2000);
			PORTD = 0x04; // R led
			show(&G);
			_delay_ms(10000);
			show(&Y);
			_delay_ms(2000);
		}
    }
 
    return 0;
}

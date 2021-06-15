#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include <avr/interrupt.h>

int toggle = 0;

unsigned char DOT_Y[8] = {
   0x3C, 0x99, 0xC3, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7
};

unsigned char DOT_G[8] = {
   0xC3, 0x81, 0x3D, 0x3F, 0x31, 0x39, 0x81, 0xC3
};

unsigned char DOT_R[8] = {
   0x83, 0x81, 0x9C, 0x9C, 0x81, 0x83, 0x99, 0x99
};

ISR(INT0_vect)
{
   toggle = 1;

   EIFR = (1<<INTF0);
}


void Matrix(char *name)
{
    DDRA = 0xff; //  도트매트릭스 행
    DDRB = 0xff; // 도트매트릭스 열
    for(i = 0; i < 8; i++)
    {
        // 8비트의 ROWS 신호 중 1비트만 논리 1로 출력
        PORTB = (1<<(i));
        // COLS 신호에 데이터 출력
        PORTA = name[i]; 
        _delay_ms(2);    // 2ms 동안 대기
    }

}

// C 언어의 주 실행 함수
int main(void){

   DDRD = 0xFF; // led 출력 (G :0x01, Y:0x02, R:0x04)
   DDRE = 0x00; // 버튼 입력
   EICRB = 0xFF;
   EICRA = (2<<ISC00);
   EIMSK = (1<<INT0); // INT4~7까지 tkdyd
   
   sei();
   _delay_ms(100);
   while(1){
      
      PORTD = 0x01; //G led
      _delay_ms(10000);
      PORTD = 0x02; //Y led
      _delay_ms(2000);
      PORTD = 0x04; //R led
      _delay_ms(10000);
      if(toggle == 1)
      {
          
        PORTF = 0x02; 
        _delay_ms(2000);
        Matrix("DOT_G");
        PORTF = 0x04;
        _delay_ms(10000);
        Matrix("DOT_Y");
        _delay_ms(2000);
        toggle = 0;

      }
      
   }
   
   return 0;
}

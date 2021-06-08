#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include <avr/interrupt.h>

int toggle = 0;
   
unsigned char Y_color[8] = {
   0B10000010,
   0B01000100,
   0B00101000,
   0B00010000,
   0B00010000,
   0B00010000,
   0B00010000,
   0B00010000
};

unsigned char G_color[8] = {
   0B00000000,
   0B00000000,
   0B11111110,
   0B10010000,
   0B10010000,
   0B10011110,
   0B11010010,
   0B01111110
};

unsigned char N_[8] = {
   0B00000000,
   0B00000000,
   0B00000000,
   0B00000000,
   0B00000000,
   0B00000000,
   0B00000000,
   0B00000000
};

unsigned char R_color[8] = {
   0B11111111,
   0B10000001,
   0B11111111,
   0B10100000,
   0B10010000,
   0B10001000,
   0B10000100,
   0B10000010
};

void show(char *name)
{
   DDRA = 0B11111111;
   DDRC = 0B11111111;
   unsigned char i; 
   
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
   DDRE = 0x00; // 버튼 입력
   
   _delay_ms(100);
   while(1){
      if((PINE & 0x01) == 0) toggle = 1;
      PORTD = 0x10; //G led
      _delay_ms(10000);
      if((PINE & 0x01) == 0) toggle = 1;
      PORTD = 0x20; //Y led
      _delay_ms(2000);
      if((PINE & 0x01) == 0) toggle = 1;
      PORTD = 0x40; //R led
      _delay_ms(10000);
      show('N_');
      if((PINE & 0x01) == 0) toggle = 1;
      if(toggle == 1)
      {
         PORTD = 0x20; // Y led
         _delay_ms(2000);
         PORTD = 0x40; // R led
         show("G_color");
         _delay_ms(10000);
         show("Y_color");
         _delay_ms(2000);
         toggle = 0;
      }
      
      
   }
   
   return 0;
}



#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main() {
   unsigned char data[ ]= {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                              0x6d, 0x7d, 0x27, 0x7f, 0x6f};
   unsigned char data2[ ]= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d};
   unsigned int time = 0;
   unsigned int sec0 = 0;
   unsigned int sec1 = 0;
   unsigned int min0 = 0;
   unsigned int min1 = 0;

   DDRC = 0xFF;
   DDRG = 0x0F;

   while(1) {
      time++;
      sec0 = (time/100)%10;
      sec1 = (time/1000)%10;
            
      if(sec0 > 9) {
         sec1++;
      }
      if(sec1 > 5) {
         time = 0;
         min0++;
      }
      if(min0 > 9) {
         time = 0;
         min0 = 0;
         sec1 = 0;
         sec0 = 0;
         min1++;
      }
      if(min1 > 5) {
         min1 = 0;
      }

      PORTC = data[sec0];
      PORTG = 0x01;
      _delay_ms(2);

      PORTC = data2[sec1];
      PORTG = 0x02;
      _delay_ms(3);
      
      PORTC = data[min0] | 0x80;
      PORTG = 0x04;
      _delay_ms(2);

      PORTC = data2[min1];
      PORTG = 0x08;
      _delay_ms(3);


   }
}

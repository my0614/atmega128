/*******************************************************
This program was created by the
CodeWizardAVR V3.10 Evaluation
Automatic Program Generator
?Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2020-10-28
Author  : 
Company : 
Comments: 


Chip type               : ATmega128A
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128a.h>
#include <delay.h>
#include <io.h>

unsigned char  number[16] = {
	0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x84,0x98,0x88,0x83, 0xc6,0xa1,0x86,0x8e

};

unsigned char LED_number[8] ={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
// Declare your global variables here

unsigned int count = 0;
unsigned char thou=0,hund=0,ten =0,one=0;
unsigned int k,i;
unsigned int toggle = 0;

void main(void)
{


// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Port E initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDE0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (0<<PORTE2) | (0<<PORTE1) | (0<<PORTE0);

// Port F initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRF=(1<<DDF7) | (1<<DDF6) | (1<<DDF5) | (1<<DDF4) | (1<<DDF3) | (1<<DDF2) | (1<<DDF1) | (1<<DDF0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);

// Port G initialization
// Function: Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRG=(1<<DDG4) | (1<<DDG3) | (1<<DDG2) | (1<<DDG1) | (1<<DDG0);
// State: Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTG=(0<<PORTG4) | (0<<PORTG3) | (0<<PORTG2) | (0<<PORTG1) | (0<<PORTG0);



while (1)
      {
      // Place your code here
       if((PINC & 0x01) == 0)
		{
			toggle = 1;
		}
		if((PINC & 0x02) == 0)
		{
			toggle = 2;
		}
		//버튼 1번눌렀을때
		if(toggle == 1)
		{
				PORTD = 0x00;
				delay_ms(500);
				for(i=0;i<8;i++)
				{
					PORTD = LED_number[i];
					delay_ms(500);
				}
				PORTD = 0x00;
				delay_ms(500);
				for(i=7;i>=0;i--)
				{
					PORTD = LED_number[i];
					delay_ms(500);
				}
		
			
		}
		  // 버튼 2눌렀을때
		if(toggle == 2)
		{
			thou = count/1600;
			hund = count/160%16;
			ten = count%16%16;
			one = count%16;
			
			for(k=0;k<16;k++)
			{
				
				PORTG = 0x01;
				PORTF= number[thou];
				delay_ms(1);
				PORTG = 0x02;
				PORTF= number[hund];
				delay_ms(1);
				PORTG = 0x04;
				PORTF= number[ten];
				delay_ms(1);
				PORTG = 0x08;
				PORTF= number[one];
				delay_ms(1);
			}
			  count++;
			  if(count==65535)
			  {
				  count=0;
			  }
			
			toggle = 0; //toggle초기화  
		}
      }
}

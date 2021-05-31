#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <interrupt.h>
#define TRIG 0
#define ECHO 1
#define SOUND_VELOCITY 340UL

unsigned char num[4]= { 0x06,0x5b,0x4f,0x66}; // fnd숫자
int toggle = 0;
void Command_write(uint8_t command)

{

	PORTG &= ~0x02;	// RS LOW

	PORTC = command;// command write

	_delay_us(1);

	PORTG |= 0x04;	// E HIGH

	_delay_us(1);

	PORTG &= ~0x04;	// E LOW

	_delay_us(41);

}

void Data_write(uint8_t data)

{
	PORTG |= 0x02;	// RS HIGH
	PORTC = data;	// data write
	_delay_us(1);
	PORTG |= 0x04;	// E HIGH
	_delay_us(1);
	PORTG &= ~0x04;	// E LOW
	_delay_us(41);
}

void LCD_init(void)

{
	// function set - data 8bit, 2 line, 5x7 dot
	Command_write(0x38);
	Command_write(0x38);
	// Display ON/OFF control - display ON, Cursor OFF, Cursor blink OFF
	Command_write(0x0C);
	// Clear display
	Command_write(0x01);
	_delay_ms(2);
	// Entry Mode Set - Cursor address increase, Display Shift OFF
	Command_write(0x06);
}

void LCD_print(char *str)

{
	uint8_t i=0;
	while(str[i] !='\0')
	{
		Data_write(str[i++]);
	}

}

void show()
{
	// set the cursor to column 0, line 1
	Command_write(0x80);
	// Print a message to the LCD.
	LCD_print("Danger!!");
	_delay_ms(1000);
}

void buzzer()
{
	DDRB =0xff; //부저사용한 포트
	//1초동안 부저 울리기
	PORTB = 0xff;
	_delay_ms(1000);
	PORTB = 0x00;
	_delay_ms(1000);

}

// 시작버튼 외부인터럽트
ISR(INT4_vect)
{
	int toggle = 1;
}
// 스탑버튼 외부인터럽트
ISR(INT5_vect)
{
	int toggle = 2;
}


int main(void)
{
	unsigned int distance;
    int result = 0;
	DDRC = 0xFF;	// data Output
	DDRG = 0x07;	// control signal Output
	PORTG = 0x00;	// RW -> LOW, RS -> LOW, E -> LOW
	PORTE = 0x00; // 버튼
    EICRB = 0x0a; // 4,5번 falling edge
    EIMSK = 0x30; // INT4-7까지 허용
    sei();
	LCD_init();
	while(1)
	{
		if(toggle == 1)
		{
			DDRD = 0xff;
			DDRD = ((DDRE | (1<<TRIG)) & ~(1<<ECHO)); // 초음파센서
			DDRA =0xff;
			TCCR1B = 0x03;
			PORTD &= ~(1<<TRIG);
			_delay_us(10);
			PORTD |= (1<<TRIG);
			_delay_us(10);
			PORTD &= ~(1<<TRIG);
			while(!(PIND & (1<<ECHO)));
			TCNT1 = 0x0000;
			while(PIND & (1<<ECHO));
			TCCR1B = 0x00;
			distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);

			//음파의 속도는 340m/s 이므로 1cm를 이동하는데 약 29us.
			// 4/2 = 왕복거리
			if(distance <= 50)
			{
				PORTD = 0xf0;
				PORTA = num[3];
				_delay_ms(100);
				buzzer();
				show();
			}
			else if(distance <= 80)
			{
				PORTD = 0x70;
				PORTA = num[2];
				_delay_ms(100);
			}
			else if(distance <= 100 )
			{
				PORTD = 0x30;
				PORTA = num[1];
				_delay_ms(100);
			}
			else if(distance <= 130)
			{
				PORTD = 0x10;
				PORTA = num[0];
				_delay_ms(100);
			}
            if (distance <=270)
            {
                result = distance / 30;
                PORTA = num[result]; // 초음파센서 거리
                _delay_ms(100);
            }
			_delay_ms(10);
		}
		if(toggle ==2)
		{
			DDRD = 0x00; //led off
			DDRB = 0x00; // buzzer off
			_delay_ms(300);
		}

	}
}

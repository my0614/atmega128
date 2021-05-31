#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 0
#define ECHO 1
#define SOUND_VELOCITY 340UL

unsigned char arr[4]={0x10,0x20,0x40,0x80}; // led
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

void start()
{
	// set the cursor to column 0, line 1
	Command_write(0x80);
	// Print a message to the LCD.
	LCD_print("start!!");
	_delay_ms(1000);
}

void end()
{
	// set the cursor to column 0, line 1
	Command_write(0x80);
	// Print a message to the LCD.
	LCD_print("end!!");
	_delay_ms(1000);
}

void buzzer()
{
	DDRB =0xff; //부저사용한 포트
	//1초동안 부저 울리기
	PORTB = 0xff;
	_delay_ms(500);
	PORTB = 0x00;
	_delay_ms(500);

}


// 시작버튼 외부인터럽트
ISR(INT4_vect)
{
	int toggle = 1;
    buzzer();
    _delay_ms(100);
}
// 스탑버튼 외부인터럽트
ISR(INT5_vect)
{
	int toggle = 2;
    buzzer();
    _delay_ms(100);
}

int main(void)
{
	unsigned int dis,i;
	int toggle = 0;
    PORTE = 0x00; // 버튼
    EICRB = 0x0a; // 4,5번 falling edge
    EIMSK = 0x30; // INT4-7까지 허용
	//DDRD = 0xff;
	//DDRD = ((DDRE | (1<<TRIG)) & ~(1<<ECHO)); // 초음파센서

	while(1)
	{
        if(toggle == 1)
        {
            start(); // lcd 출력
            DDRD = 0xff;
            DDRD = ((DDRE | (1<<TRIG)) & ~(1<<ECHO)); // 초음파센서
            
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
            dis = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);
            
            // 일정한 거리 감지되면 모터 정지
            if(dis <= 80)
            {
                toggle = 2;
            }
            
                // led 반복하기
            for(i=0;i<4;i++)
            {
                PORTD = arr[i];
                _delay_ms(500);
                    
		    }	
		}
		if(toggle == 2)
		{
            end(); // lcd 출력
			PORTD = 0x00; // led,초음파센서 off
            PORTG = 0x00; // 부저 off

		}
		
		
	}
}

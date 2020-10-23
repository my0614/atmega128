
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define sbi(x, y) (x |= (1 << y))  // x의 y 비트를 설정(1)
#define cbi(x, y) (x &= ~(1 << y)) // x의 y 비트를 클리어(0)

// CON 포트는 포트 C와 연결됨을 정의
#define LCD_CON      PORTC
// DATA 포트는 포트 A와 연결됨을 정의
#define LCD_DATA     PORTA
// DATA 포트의 출력 방향 설정 매크로를 정의
#define LCD_DATA_DIR DDRA
// DATA 포트의 입력 방향 설정 매크로를 정의
#define LCD_DATA_IN  PINA
// RS 신호의 비트 번호 정의
#define LCD_RS   0
// RW 신호의 비트 번호 정의
#define LCD_RW   1
// E 신호의 비트 번호 정의
#define LCD_E    2

// 텍스트 LCD로 부터 상태(명령)를 읽는 함수
unsigned char LCD_rCommand(void){
	unsigned char temp=1;
	
	LCD_DATA_DIR = 0X00;
	
	cbi(LCD_CON, LCD_RS); // 0번 비트 클리어, RS = 0, 명령
	sbi(LCD_CON, LCD_RW); // 1번 비트 설정, RW = 1, 읽기
	sbi(LCD_CON, LCD_E);  // 2번 비트 설정, E = 1
	_delay_us(1);
	
	temp = LCD_DATA_IN;      // 명령 읽기
	_delay_us(1);
	
	cbi(LCD_CON, LCD_E);  // 명령 읽기 동작 끝
	
	LCD_DATA_DIR = 0XFF;
	_delay_us(1);
	
	return temp;
}

// 텍스트 LCD의 비지 플래그 상태를 확인하는 함수
char LCD_BusyCheck(unsigned char temp)
{
	return temp & 0x80;
}

// 텍스트 LCD에 명령을 출력하는 함수 - 단, 비지플래그 체크하지 않음
void LCD_wCommand(char cmd)
{
	cbi(LCD_CON, LCD_RS); // 0번 비트 클리어, RS = 0, 명령
	cbi(LCD_CON, LCD_RW); // 1번 비트 클리어, RW = 0, 쓰기
	sbi(LCD_CON, LCD_E);  // 2번 비트 설정, E = 1
	LCD_DATA = cmd;          // 명령 출력
	_delay_us(1);
	cbi(LCD_CON, LCD_E);  // 명령 쓰기 동작 끝
	_delay_us(1);
}

// 텍스트 LCD에 명령을 출력하는 함수 - 단, 비지플래그 체크함
void LCD_wBCommand(char cmd)
{
	while(LCD_BusyCheck(LCD_rCommand()))
	_delay_us(1);
	cbi(LCD_CON, LCD_RS); // 0번 비트 클리어, RS = 0, 명령
	cbi(LCD_CON, LCD_RW); // 1번 비트 클리어, RW = 0, 쓰기
	sbi(LCD_CON, LCD_E);  // 2번 비트 설정, E = 1
	
	LCD_DATA = cmd;          // 명령 출력
	_delay_us(1);
	cbi(LCD_CON, LCD_E);  // 명령 쓰기 동작 끝
	_delay_us(1);
}

void LCD_Cursor(char col, char row)
{
	LCD_wBCommand(0x80 | (row + col * 0x40));
}

// 텍스트 LCD를 초기화하는 함수
void LCD_Init(void)
{
	_delay_ms(100);
	// 비지 플래그를 체크하지 않는 Function Set
	LCD_wCommand(0x38);
	_delay_ms(10);
	// 비지 플래그를 체크하지 않는 Function Set
	LCD_wCommand(0x38);
	_delay_us(200);
	// 비지 플래그를 체크하지 않는 Function Set
	LCD_wCommand(0x38);
	_delay_us(200);
	
	// 비지 플래그를 체크하는 Function Set
	LCD_wBCommand(0x38);
	// 비지 플래그를 체크하는 Display On/Off Control
	LCD_wBCommand(0x0c);
	// 비지 플래그를 체크하는 Clear Display
	LCD_wBCommand(0x01);
}

void LCD_wData(char dat)
{
	while(LCD_BusyCheck(LCD_rCommand()))
	{
		_delay_us(1);
	}
	sbi(LCD_CON, LCD_RS);
	cbi(LCD_CON, LCD_RW);
	sbi(LCD_CON, LCD_E);
	LCD_DATA = dat;
	_delay_us(1);
	cbi(LCD_CON, LCD_E);
	_delay_us(1);
}

void LCD_wString(char *str)
{
	while(*str)
	LCD_wData(*str++);
}



void buzzer()
{
	DDRG =0xff; //부저
	LCD_Init();
	LCD_Cursor(0,6);

	LCD_wString("Bomb!!");



	PORTG = 0xff;
	_delay_ms(1000);
	PORTG = 0x00;
	_delay_ms(1000);
	
}

int main(void)
{
    char buffhour[4];
    char buffmin[4];
    char buffsecond[4];
	char password[4] = {"123"};
	char passbuf[4] = {"000"};
	int hour= 0,min=0,second=10;
	
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xff; // 버튼
	
	LCD_Init();

		while(second >= 0)
		{
			
			
			LCD_Cursor(0,3);
			LCD_wString("Bomb TIME");
			
			LCD_Cursor(1,1);
			sprintf(buffhour, "%02d ", hour);
			LCD_wString(buffhour); // WESNET 문자열 출력
			LCD_wString(" : ");
			sprintf(buffmin, "%02d ", min);
			LCD_wString(buffmin); // WESNET 문자열 출력
			LCD_wString(" : ");
			sprintf(buffsecond, "%02d ", second);
			LCD_wString(buffsecond); // WESNET 문자열 출력
			LCD_wString(" : ");
			_delay_ms(1000);
			second--;
			/*
			if((PIND & 0x01) == 0)
			{
				strcat(passbuf,"1");
			}
			if((PIND & 0x02) == 0)
			{
				strcat(passbuf,"2");
			}
			if((PIND & 0x04) == 0)
			{
				strcat(passbuf,"3");
			}
			
			/*if(strcmp(password,passbuf) == 0) 
			{
				LCD_Init();
				LCD_Cursor(0,6);
				LCD_wString("success");
				_delay_ms(1000);
				
			}*/
			
		}
		
		buzzer(); // 부저함수
		
	
}


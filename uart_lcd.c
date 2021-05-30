
#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <io.h>
#include <interrupt.h>

int state = 0; // 상태값 변수
char arr[10]; // 첫번째 단어 배열선언
char arr2[10]; // 두번째 단어 배열선언
int i=0; // 인덱스 변수

#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
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

// 문자열 LCD에 출력하기
void LCD_wString(char *str)
{
	while(*str)
	LCD_wData(*str++); // 한개의 문자열 출력을 계속 반복
}

// uart 통신을 위한 신호 맞추기
void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) |			(1<<RXCIE0);
}

// uart 문자받기
void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

// uart 문자열 통신
void uart_string(char* str)
{
	while (*str)
	uart_write(*str++);
}

int main(void)
{

    DDRA = 0xFF; // LCD
	DDRC = 0xFF; // LCD 데이터핀
    DDRD = 0x00; // 버튼
	uart_init(BAUDRATE(9600)); // uart통신 속도 맞추기
	sei(); // ISR 실행
    LCD_Init(); // LCD 초기화

 	while(1)
	{
        LCD_Init(); // LCD 초기화
        LCD_Cursor(0,2); // LCD 커서 위치 
        LCD_wString(arr); // 첫번째 단어 출력
        _delay_ms(500); // 0.5초 딜레이

        LCD_Cursor(1,2); // LCD 커서 위치
        LCD_wString(arr2); // 두번째 단어 출력
		_delay_ms(500); // 0.5초 딜레이

        if((PIND & 0x01) == 0) // 버튼을 누르면
        {
            LCD_Init(); // LCD 초기화
            _delay_ms(1000); // 1초 딜레이
            exit(1); 끝내기 
        }
				
			
	}
}

// uart 통신하기
ISR(USART0_RX_vect)
{
	unsigned char buf = UDR0; // 버퍼 선언
	switch(buf)
	{
        // uart 처음시작 0x02, 마지막 0x03이다.
		case 0x02 : state = 1; return; // 첫번째 단어 시작
        case '\0' : state = 2; i =0; break; // 공백을 기준으로 1,2번째 단어 나누기
		case 0x03 : state = 0; i = 0;break; // 2번째 단어 끝
	}
    // state가 1일때는 첫번째 단어 arr에 계속 저장하기
	if(state == 1)
	{
		arr[i] = buf;
		i++;		
	}
    // state가 2일때는 두번째 단어 arr2에 계속 저장하기
    if(state == 2)
	{
		arr2[i] = buf;
		i++;		
	}

}

#include <delay.h> // delay사용을 위한 헤더파일
#include <interrupt.h> // 외부인터럽트 사용을 위한 헤더파일
#include <mega128.h> // 기본 헤더파일

// led나 세그먼트가 배열을 사용하여 0부터 사용하기 때문에 그전인 -1을 초기화로 설정
int cnt = -1;


int seg[9] = {0b00111111,

	0b00000110,

	0b01011011,

	0b01001111,

	0b01100110,

	0b01101101,

	0b01111101,

	0b00100111,

	0b01111111,


};

// led 1~8까지 표현
unsigned char led_cnt[8] =
{
    0b00000001, //1
    0b00000010, //2
    0b00000100, //3
    0b00001000, //4
    0b00010000, //5
    0b00100000, //6
    0b01000000, //7
    0b10000000 //8
};

// 버튼 1
interrupt [EXT_INT0] void ext_int0_isr(void)
{
    cnt++; // cnt변수 1씩 증가
    // led 깜빡이기
    PORTA = 0xff;
    delay_ms(100);
    PORTA = 0x00;
    delay_ms(100);
    if(cnt >7) cnt = 7; // led,세그먼트 최대값 설정
}
//버튼 2
interrupt [EXT_INT1] void ext_int1_i(void)
{
    cnt--; // cnt변수 1씩 감소
    // led 깜빡이기
    PORTA = 0xff;
    delay_ms(100);
    PORTA = 0x00;
    delay_ms(100);
    if(cnt <0) cnt = 0; // led,세그먼트 최솟값 설정
}
void main(void)
{
    DDRA = 0xff; // led 출력설정
    DDRB = 0xff; // 7세그먼트 출력설정 
    DDRD = 0xff; // 세그먼트 자리수 
    // 외부인터럽트 설정
    EICRA=0x0a; // 외부인터럽트 INT0~3까지 (Falling Edge)
    EICRB=0x00; // 외부인터럽트 INT4~7까지 (Rising Edge)
    EIMSK=0x03; // 외부인터럽트 마스크 레지스터 설정(어떤 핀을 레지스터로 결정할지 정함 INT0,INT1사용으로 설정)
    EIFR=0xFF; // 외부인터럽트 플래그 레지스터 설정
    SREG=0x80; // 인터럽트 허가 결정 (현재 모든 인터럽트 허용)
    while(1)
    {
        //cnt가 -1이 아닐때 즉,(증가 버튼을 눌렀을 때부터) 버튼이 누르기 전에는 아무것도 안됨
        if(cnt != -1)
        {                             
            PORTD = 0x01;
            PORTB = seg[0]; 
            delay_ms(1);
            PORTD = 0x02;
            PORTB = seg[0]; 
            delay_ms(1);
            PORTD = 0x04;
            PORTB = seg[0];
            delay_ms(1);
            PORTD = 0x08;
            PORTB = seg[9-cnt]; // seg배열에 있는 cnt인덱스로 세그먼트 숫자 출력하기
            delay_ms(1);
            PORTA = led_cnt[cnt]; // led_cnt배열에 있는 cnt인덱스로 led켜기
            delay_ms(500); // 0.5초 delay
        }
    }
}


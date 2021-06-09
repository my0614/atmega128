#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 1
#define ECHO 0
#define SOUND_VELOCITY 340UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1<<RXCIE0);
} // 8bit, no parity, 1 stop bit, TX enable, RX ISR enable

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	// wait for sending
	UDR0 = data; // send
}

void uart_string(char* str)
{
	while (*str)
		uart_write(*str++);
}

ISR(USART0_RX_vect)
{
	unsigned char buf = UDR0;
	uart_write(buf - 'a' + 'A');
}

int main(void)
{
	unsigned int distance;
	uart_init(BAUDRATE(9600));
    sei();
	DDRC = 0xff;
	DDRD = ((DDRD | (1<<TRIG)) & ~(1<<ECHO));
	int value[4] = {0,};
	while(1)
	{
		
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
		if(distance < 30)
		{
				PORTC = 0x01;
				_delay_ms(100);
		}
        else
        {
            PORTC = 0x02;
			_delay_ms(100);
        }
        sprintf(value, "dis = %d",distance);
        uart_string(value);
        _delay_ms(1000);
		
	}
}

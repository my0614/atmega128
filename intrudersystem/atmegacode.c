#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

unsigned int count = 0;

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


void buzzer()
{
	DDRG = 0xff;
	PORTG  = 0x00;
	_delay_ms(1000);
	PORTG = 0xff;
	_delay_ms(1500);
	PORTG  = 0x00;
	uart_string("Danger");
	_delay_ms(1000);

}
void ready()
{

	
	DDRA = 0x00;
	DDRB = 0xff;
	PORTB = 0x00; // led 초기화
	DDRC = 0xff;
	PORTC = 0xff;
	DDRE = ((DDRE | (1<<TRIG)) & ~(1<<ECHO));
	uart_init(BAUDRATE(9600));
	sei();
	uart_string("start");
		
}
int main(void)
{
	
	unsigned int distance;
	unsigned short value;
	while(1)
	{
		
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE & (1<<ECHO)));
		TCNT1 = 0x0000;
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);

		// 감지되면
		if(distance < 100)
		{
			count++;
			PORTB = 0x40;
			PORTC = 0x00;
			_delay_ms(500);
			
			
		}
		//볼스위치
		else if(!(PINA & 0x02))
		{	
			count++;
			PORTB = 0x80;
			_delay_ms(500);
		}
		// 소리감지센서 
		else if(!(PINA & 0x01))
		{
			count++;
			PORTB = 0x20;
			_delay_ms(500);
	
		}
		
		else 
		{
			PORTC = 0xff;
			_delay_ms(500);
			
		}
		
		if(count >= 3)
		{
			buzzer();
			count = 0;
		}
	
		_delay_ms(1500);
	}
}

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define CDS_10 341
#define CDS_20 450
#define CDS_50 550
#define CDS_80 650
#define CDS_100 731

void int_adc();
unsigned short read_adc();
void show_adc_led(unsigned short data);

int init_adc(void)
{
	ADMUX = 0x40;
	ADCSRA = 0x87;    // ADC 동작표시, ADC 8은 enable, ADC 7은 prescaler 128
}

unsigned short read_adc()
{
	unsigned char adc_low, adc_high;
	unsigned short value;

	ADCSRA |= 0x40;    // ADC 시작
	// ADC Complete
	while((ADCSRA & 0x10) != 0x10);
	adc_low = ADCL;
	adc_high = ADCH;
	value = (adc_high << 8) | adc_low;
	
	return value;
}

void show_adc_led(unsigned short value)
{
	if(value<=20)
	{
		 PORTA = 0x01;
	
	}
	else 
	{
		PORTD = 0x00;
	}
}

int main(void)
{
	
	unsigned short value;
	DDRD = 0xff;
	DDRF = 0x00;
	DDRA = 0xff;
	init_adc();
	// green  LED
	PORTA = 0x02;
	_delay_ms(3000);
	while (1)
	{
		PORTA = 0x04;
		_delay_ms(500);
		value = read_adc();
		show_adc_led(value);

	}
}

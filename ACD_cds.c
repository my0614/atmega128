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
	if(value<=CDS_10) PORTA = 0xFF;
	else if(value<=CDS_20) PORTA = 0x0F;
	else if(value<=CDS_50) PORTA = 0x07;
	else if(value<=CDS_80) PORTA = 0x03;
	else if(value<=CDS_100) PORTA = 0x01;
	else PORTA = 0x00;
}



int main(void)
{
	unsigned short value;
	DDRA = 0xff;
	DDRF = 0x00;
	init_adc();
	while (1)
	{
		value = read_adc();
		show_adc_led(value);
	}
}


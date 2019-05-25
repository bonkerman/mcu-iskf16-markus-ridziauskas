#define F_CPU 16000000UL
#include "avr/io.h"
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t duty = 0;
uint8_t flag = 0;

void PWM_init()
{
	/*set fast PWM mode with non-inverted output*/
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB |= (1<<PB3);  /*set OC0 pin as output*/
	DDRC |= (0xff);
	DDRD |= (0xff);
	TIMSK |= (1<<OCIE0);
	ADMUX = 0b01100000;
	ADCSRA = 0b10001111;
	sei();
}

ISR(ADC_vect){
	PORTC = ADCH; // Virðutiniai 8 bitai iðsaugomi kintamajame result }
	PORTD = ADCH;
}

ISR(TIMER0_COMP_vect) {
	if(duty == 255){
		flag = 1;
	}
	if(duty == 0){
		flag = 0;
	}
	if(flag==0){
		OCR0= ++duty;
	} else {
		OCR0= --duty;
	}
	
	_delay_ms(8);
}

int main ()
{
	PWM_init();
	while (1)
	{
		ADCSRA |= (1 << ADSC); 
	}
}
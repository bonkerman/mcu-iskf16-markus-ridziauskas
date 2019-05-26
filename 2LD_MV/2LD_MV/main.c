/*
 * 2LD_MV.c
 *
 * Created: 2019-02-22 12:22:37
 * Author : 20163098
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int overflow = 0;


ISR(TIMER0_OVF_vect)
{
	overflow++;
}

void timer2_init()
{
	TIMSK |= (1 << TOIE0);
	TCCR0 |= (1<<WGM00)|(1<<WGM01)|(1<<CS02);
	TCNT0 = 0;
	sei();
}

int main(void)
{
	int TOT = 112;
	int REM = 30;
	int i = 0;
    DDRA = 255;
	DDRC = 255;
	timer2_init();
    while (1) 
    {
		for (i = 0; i<=1; i++){
		if (overflow >= TOT){
			if (TCNT0 >= REM){
				PORTC ^= (1<<3);
				TCNT0 = 0;
				overflow = 0;
			}
		}
		}
		if (TOT = 112)
			TOT = 544;
		if (REM = 30)
			REM = 98;
		PORTA = TCNT0;
    }
}


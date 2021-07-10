//this code turn on LEDs in sequence every timer0 overflow

// how timer0 "normal mode" works:
1. timer0 counts upward y 1 every pulse till it reaches max value (TOP)
2. when it reaches TOP = 255 value, overflow happens
3. and TOV0 flag is set, to get ready to enable the ISR (if its mask TOIE0 is enabled and general interrupt flag is enabled)
4. when ISR is executed, TOv0 flag is cleared and the process is repeated again


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU 1000000ul
#endif

int main(void)
{
	DDRD = 0xFF;  //set PD as output Port
	TCCR0 = 0x00; //set timer mode to normal
	PORTD = 0x00;
	TIMSK |= (1 << TOIE0); //enable overflow interrupt mask
	
	sei();  //enable global interrupt flag
	TCCR0 |= (1 << CS02) | (1 << CS00)  ;  //set prescalar to 1024 (divide MCU clock speed by 1)
	while(1)
	{
		
	}

}

//ISR is written outside the main function, else Error : "static declaration of '_vector_9' follows non-static decleration
	ISR(TIMER0_OVF_vect) //ISR for timer0 Overflow
	{
	PORTD++;
	PORTD = (PORTD << 1); //increase PORTD by one each overflow, to light LEDs in order
	}


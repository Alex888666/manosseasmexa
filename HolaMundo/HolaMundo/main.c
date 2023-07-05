/*
 * HolaMundo.c
 *
 * Created: 04/07/2023 12:32:13 p. m.
 * Author : alexh
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB    = 0b11100000;
	PORTB   = 0b00000000;
	OCR0A = 0x04;
	TCCR1A = (0 << COM1A1) | (1 << COM1A0) | (0 << WGM01) | (0 << WGM00);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS02) | (1 << CS01) | (1 << CS00);
	
    /* Replace with your application code */
    while (1) 
    {
		
}


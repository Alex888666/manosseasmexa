/*
 * PWM.c
 *
 * Created: 05/07/2023 12:37:54 p. m.
 * Author : alexh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#define set_bit(sfr, bit)	(_SFR_BYTE(sfr) |= _BV(bit))
#define clear_bit(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

int main(void)
{
	//Asi se setean los bits como salida
	set_bit(DDRD, 5);
	set_bit(DDRD, 6);
    
	 // Modo Fast PWM
	 TCCR0B &= ~(1<<WGM02);
	 TCCR0A |= (1<<WGM01);
	 TCCR0A |= (1<<WGM00);
	 // Prescalador 64
	 TCCR0B &= ~(1<<CS02);
	 TCCR0B |= (1<<CS01);
	 TCCR0B |= (1<<CS00);
	 
	 //evento en el pin oc0a
	 set_bit(TCCR0A, COM0A1);
	 clear_bit(TCCR0A, COM0A0);
	 
	//evento en el pin oc0b
	set_bit(TCCR0A, COM0B1);
	set_bit(TCCR0A, COM0B0);
	
	OCR0A = 0;
	OCR0B = 63;
	uint8_t DC = 0;
	
	
    while (1) 
    {
		DC ++;
		OCR0A = DC;
		_delay_ms(100);
    }
}


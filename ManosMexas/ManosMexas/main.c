/*
 * ManosMexas.c
 *
 * Created: 23/07/2023 02:13:18 p. m.
 * Author : alexh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#define set_bit(sfr, bit)	(_SFR_BYTE(sfr) |= _BV(bit))
#define clear_bit(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))


// CONTROLES PULGAR
void CerrarPulg()
{
	PORTB &=~(1<<2);
	PORTL |=(1<<0);
}

void AbrirPulg()
{
	PORTB |=(1<<2);
	PORTL &=~(1<<0);
}

void PararPulg()
{
	PORTB &=~(1<<2);
	PORTL &=~(1<<0);
}

// CONTROLES Indice

void CerrarInd()
{
	PORTL &=~(1<<2);
	PORTL |=(1<<4);
}

void AbrirInd()
{
	PORTL |=(1<<2);
	PORTL &=~(1<<4);
}

void PararInd()
{
	PORTL &=~(1<<2);
	PORTL &=~(1<<4);
}

// CONTROLES MEDIO

void CerrarMed()
{
	PORTL &=~(1<<5);
	PORTL |=(1<<7);
}

void AbrirMed()
{
	PORTL |=(1<<5);
	PORTL &=~(1<<7);
}

void PararMed()
{
	PORTL |=(1<<5);
	PORTL &=~(1<<7);
}

// CONTROLES Angular

void CerrarAng()
{
	PORTC &=~(1<<4);
	PORTC |=(1<<6);
}

void AbirAng()
{
	PORTC |=(1<<4);
	PORTC &=~(1<<6);
}

void PararAng()
{
	PORTC |=(1<<4);
	PORTC |=(1<<6);
}

//Controles Meñique

void CerrarMeq()
{
	PORTC &=~(1<<2);
	PORTC |=(1<<0);
}

void AbrirMeq()
{
	PORTC |=(1<<2);
	PORTC &=~(1<<0);
}

void PararMeq()
{
	PORTC &=~(1<<2);
	PORTC &=~(1<<0);
}

void pwm75() //Seteo de la palabra de control para generar el PWM 100ms con 75%
{
	OCR1A=780;
	OCR1B=584;
	TCCR1A=0b00100011;
	TCCR1B=0b00011101;
}

void pwm25() //Seteo de la palabra de control para generar el PWM 100ms con 25%
{
	DDRD = DDRD | 0b00010000;
	OCR1A=780;
	OCR1B=194;
	TCCR1A=0b00100011;
	TCCR1B=0b00011101;
}

int main(void)
{
	//Seteando bits para el PWM de los enable
	set_bit(DDRD, 2); //ENA - PH1
	set_bit(DDRD, 3); //ENB - PH1
	//set_bit(DDRB, 4);
	//set_bit(DDRB, 5);
	//set_bit(DDRB, 6);
	
	//Seteando Bits de salida para el GPIO
	
	//Puente H1
	DDRL |= (1<<4); // PD45: IN1 - PH1
	PORTL &= ~(1<<4); // Poniendo en low
	DDRL |= (1<<2); // PD47: IN2 - PH1
	PORTL &= ~(1<<2); // Poniendo en low
	DDRL |= (1<<0); // PD49: IN3 - PH1
	PORTL &= ~(1<<0); // Poniendo en low
	DDRB |= (1<<2); // PD51: IN4 - PH1
	PORTB &= ~(1<<2); // Poniendo en low
	
	//Puente H2
	DDRL |= (1<<7); // PD42: IN3 - PH2
	PORTL &= ~(1<<7); // Poniendo en low
	DDRL |= (1<<5); // PD44: IN4 - PH2
	PORTL &= ~(1<<5); // Poniendo en low
	
	//Puente H3
	DDRC |= (1<<0); // PD37: IN4 - PH3
	PORTC &= ~(1<<0); // Poniendo en low
	DDRC |= (1<<2); // PD35: IN3 - PH3
	PORTC &= ~(1<<2); // Poniendo en low
	DDRC |= (1<<4); // PD33: IN2 - PH3
	PORTC &= ~(1<<4); // Poniendo en low
	DDRC |= (1<<6); // PD31: IN1 - PH3
	PORTC &= ~(1<<6); // Poniendo en low
	
	//Seteando Bits de entrada de los pulsos
	DDRB &=~ (1<<1); // PD52 FASE A - M1
	DDRB &=~ (1<<3); // PD50 FASE B - M1
	DDRL &=~ (1<<1); // PD48 FASE A - M2
	DDRL &=~ (1<<3); // PD46 FASE B - M2
	

	//Seteando como salida puertos de PWM
	DDRE |= (1<<5); // PD3: INB - PH1
	DDRG |= (1<<5); // PD4: INA - PH1
	DDRE |= (1<<3); // PD5: INB - PH2
	DDRH |= (1<<3); // PD6: INA - PH1
	DDRH |= (1<<4); // PD7: INB - PH1
	
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
	
	OCR0A = 127;
	OCR0B = 127;
	
	//uint8_t DC = 0;
	
	
	while (1)
	{
		//PararAng();
		//PararInd();
		//PararMed();
		//PararMeq();
		//PararPulg();
	}
}




/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed. Use 
 * functions from GPIO library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define LED_RED		PC1
#define BTN			PD2
#define BLINK_DELAY 500
#define 	_BV(bit)   (1 << (bit))
#define 	bit_is_set(sfr, bit)   (_SFR_BYTE(sfr) & _BV(bit))

#define 	bit_is_clear(sfr, bit)   (!(_SFR_BYTE(sfr) & _BV(bit)))

#define 	loop_until_bit_is_set(sfr, bit)   do { } while (bit_is_clear(sfr, bit))

#define 	loop_until_bit_is_clear(sfr, bit)   do { } while (bit_is_set(sfr, bit))

#ifndef F_CPU
# define F_CPU 16000000     // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"           // GPIO library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs when a push button is pressed. Functions 
 *           from user-defined GPIO library is used.
 * Returns:  none
 **********************************************************************/
int main(void)
{

    // Configure the second LED at port C
	GPIO_config_output(&DDRC, LED_RED);
	GPIO_write_low(&PORTC, LED_RED);

    // Infinite loop
    while (1)
    {
		/*
		* 1 position 90 deg à gauche, 2 pos au centre, c'est linéaire
		*/
		_delay_ms(20);
		GPIO_toggle(&PORTC, LED_RED);
		_delay_ms(2);
		GPIO_toggle(&PORTC, LED_RED);
		
	   
        // WRITE YOUR CODE HERE
		
    }

    // Will never reach this
    return 0;
}
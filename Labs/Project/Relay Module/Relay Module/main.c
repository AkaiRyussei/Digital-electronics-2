/*
 * GccApplication1.c
 *
 * Created: 29/09/2021 16:43:15
 * Author : truon
 */ 

/* Defines -----------------------------------------------------------*/
/* The preprocessor will process directives that are inserted into the C
 * source code. These directives allow additional actions to be taken on
 * the C source code before it is compiled into object code. Directives
 * are not part of the C language itself.
 *
 * Preprocessor directives begin with a pound (#) symbol and may have 
 * several arguments. Do NOT put a semicolon character at the end of 
 * directives. This is a common mistake.
 */
#define RELAY1   PB5 // AVR pin where green LED is connected
#define RELAY2   PB4
#define SHORT_DELAY 250 // Delay in milliseconds
#ifndef F_CPU           // Preprocessor directive allows for conditional
                        // compilation. The #ifndef means "if not defined".
# define F_CPU 16000000 // CPU frequency in Hz required for delay
#endif                  // The #ifndef directive must be closed by #endif

/* Includes ----------------------------------------------------------*/
/* Include another C language file into the current file at the location
 * of the #include statement prior to compiling the source code.
 */
#include <util/delay.h> // Functions for busy-wait delay loops
#include <avr/io.h>     // AVR device-specific IO definitions

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<RELAY1);
	DDRB = DDRB | (1<<RELAY2);

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<RELAY1);
	PORTB = PORTB & ~(1<<RELAY2);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Invert LED in Data Register
        // PORTB = PORTB xor 0010 0000
        PORTB = PORTB ^ (1<<RELAY1);
		PORTB = PORTB ^ (1<<RELAY2);
		
    }

    // Will never reach this
    return 0;
}


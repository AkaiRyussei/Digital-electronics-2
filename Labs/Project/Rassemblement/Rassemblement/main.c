

/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdbool.h>
#include "timer.h"          // Timer library for AVR-GCC
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include "twi.h"            // TWI library for AVR-GCC
#include <time.h>
#include "gpio.h"  
#include <util/delay.h> 

// servo motor part
#define SERVO_M PC1

//RELAYS part
#define RELAY1   PB5 
#define RELAY2   PB4

//LED
#define LED PB3

/* Variables ---------------------------------------------------------*/
typedef enum {              // FSM declaration
    STATE_IDLE = 1,
    STATE_SEND,
    STATE_ACK
} state_t;
 
 //processing variables
int nextLine = 0;
_Bool change = false; 

//input variables
volatile uint16_t humidity = 0;
volatile uint16_t temperature = 0;
volatile uint16_t light = 0; 

int main(void)
{
	// Servo motor part
	
	GPIO_config_output(&DDRC, SERVO_M);
	GPIO_write_low(&PORTC, SERVO_M);
	
	// end servo motor part
	
	// Start RELAYS part
	DDRB = DDRB | (1<<RELAY1);
	DDRB = DDRB | (1<<RELAY2);
	
	PORTB = PORTB & ~(1<<RELAY1);
	PORTB = PORTB & ~(1<<RELAY2);
	//end RELAYS part
	
	//LED setup 
	GPIO_config_output(&DDRB, LED);
	GPIO_write_low(&PORTB, LED);
	
	// end LED setup
	
	/* code of the light sensor */
    
	ADMUX |= (1<<REFS0);   // =1
	ADMUX &= ~(1<<REFS1);  // =0
	// Set input channel to ADC0
	ADMUX &=~ (1<<MUX3 | 1<< MUX2 | 1<< MUX1 | 1<<MUX0);
	// Enable ADC module
	ADCSRA |= (1<<ADEN);

	// Enable conversion complete interrupt
	ADCSRA |= (1<<ADIE);
	// Set clock prescaler to 128
	ADCSRA |= (1<< ADPS2 | 1<<ADPS1 | 1<<ADPS0);
	
	// Initialize I2C (TWI)
    twi_init();

    // Initialize UART to asynchronous, 8N1, 9600
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter1 to update FSM
    // Set prescaler to 33 ms and enable interrupt
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();
	
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART
    uart_puts("\r\nScan I2C-bus for devices:\r\n");

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */

    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Update Finite State Machine and test I2C slave addresses 
 *           between 8 and 119.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
	//Start ADC conversion ( for the light sensor )
	ADCSRA |= (1<<ADSC);
	
	/* here it's for hum and temp */
    static state_t state = STATE_IDLE;  // Current state of the FSM
    static uint8_t addr = 0x5c;            // I2C slave address
    uint8_t result = 1;                 // ACK result from the bus 
    char uart_string[2] = "00"; // String for converting numbers by itoa()
    // FSM
    switch (state)
    {
		
    case STATE_IDLE:
		state = STATE_SEND;
        break;
    
    // Transmit I2C slave address and get result
    case STATE_SEND:
        // I2C address frame:
        // +------------------------+------------+
        // |      from Master       | from Slave |
        // +------------------------+------------+
        // | 7  6  5  4  3  2  1  0 |     ACK    |
        // |a6 a5 a4 a3 a2 a1 a0 R/W|   result   |
        // +------------------------+------------+
        result = twi_start((addr<<1) + TWI_WRITE);
		
		
			
		// TEMP + HUMID ==============
		
		
		
		if (nextLine == 0)
			twi_write(0x02); //0x00 for humid and 0x02 for temperature
		else if(nextLine == 1)
			twi_write(0x00);
		
		if ( nextLine  <= 1 ){
			twi_stop();
			result = twi_start((addr<<1) + TWI_READ);
			//integer part
			result = twi_read_ack();
			
			if (nextLine == 0){
				temperature = result;
			}
			if (nextLine == 1){
				humidity = result;
			}
			itoa(result, uart_string, 10);
			uart_puts(uart_string);
			//fractional part
			result = twi_read_nack();
			twi_stop();
			itoa(result, uart_string, 10);
			uart_puts(".");
			uart_puts(uart_string);
			uart_puts(" ");
			
			if (nextLine == 0)
				uart_puts("degrees");
				
			if (nextLine == 1)
				uart_puts("humidity");
				
				
			uart_puts(" ");
		}
		
		nextLine ++; 
		
		
		if ( nextLine == 3 ){
			nextLine = 0; 
			uart_puts("\r\n");
		}
		
		state = STATE_IDLE;
        break;

    // A module connected to the bus was found
    case STATE_ACK:
        // Send info about active I2C slave to UART and move to IDLE
		
		itoa(addr, uart_string, 16);
		uart_puts(uart_string);
		uart_puts(" ");
		state = STATE_IDLE;
        break;

    // If something unexpected happens then move to IDLE
    default:
        state = STATE_IDLE;
        break;
    }
}
	
ISR(ADC_vect)
{
	if ( nextLine == 2){
		
		//Send ADC value to UART Tx
		uint16_t value = 0;
		char lcd_string[4] = "";
		
		
		value = ADC;                  // Copy ADC result to 16-bit variable
		light = ADC;
		itoa(value, lcd_string, 10);  // Convert decimal value to string

		//Send ADC value to UART Tx
		if ( change == false ){
			uart_puts(lcd_string);
			uart_puts(" light");
		}
		change = !change;
	}
	
}

ISR(TIMER2_OVF_vect){
	
	
	char lcd_string[4] = "";
	uart_puts(itoa((humidity%100),lcd_string,10));

}

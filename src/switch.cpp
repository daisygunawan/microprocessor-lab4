// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include "switch.h"    // Include the header file for switch-related functions
#include <avr/io.h>     // Include AVR I/O definitions for register manipulation

// Initialize external switch on PD0 with interrupt
void initSwitchPD0(){
    DDRD &= ~(1 << DDD0);    // Set PD0 as input by clearing the DDD0 bit in DDRD (Data Direction Register)
    PORTD |= (1 << PORTD0);  // Enable internal pull-up resistor on PD0 by setting the PORTD0 bit in PORTD

    EICRA &= ~(1 << ISC01);  // Clear ISC01 bit in EICRA (External Interrupt Control Register A) to configure interrupt
    EICRA |= (1 << ISC00);   // Set ISC00 bit in EICRA to trigger interrupt on any logical change on INT0 (PD0)

    EIMSK |= (1 << INT0);    // Enable external interrupt INT0 by setting the INT0 bit in EIMSK (External Interrupt Mask Register)
}

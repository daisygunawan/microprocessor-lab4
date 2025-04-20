// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>   // For register definitions like TCCR0A, OCR0A, etc.
#include <avr/interrupt.h>  // Optional: if you plan to use interrupts
#include <util/delay.h>     // Optional: for _delay_ms(), but not used here
#include <stdint.h>         // For uint types
#define F_CPU 16000000UL    // Define CPU frequency if not already defined

// Function to initialize Timer0 in CTC mode
void initTimer0();

// Function to initialize Timer1 in CTC mode
void initTimer1();

// Delay function that pauses for a number of seconds
void delayS(unsigned int delay);

// Delay function that pauses for a number of milliseconds
void delayMs(unsigned int delay);

#endif


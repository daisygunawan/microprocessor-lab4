// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include "timer.h"  // Import the timer setup from another file

// Set up Timer0 so it works in "CTC mode" (Clear Timer on Compare Match)
void initTimer0(){
  TCCR0A &= ~(1 << WGM00);  // Make sure bit WGM00 is 0 (off)
  TCCR0A |= (1 << WGM01);   // Turn on bit WGM01 to activate CTC mode
  TCCR0B &= ~(1 << WGM02);  // Make sure bit WGM02 is 0 too
}

// Set up Timer1 for the same CTC mode
void initTimer1(){
  TCCR1A &= ~(1 << WGM10);  // Turn off bit WGM10
  TCCR1A &= ~(1 << WGM11);  // Turn off bit WGM11
  TCCR1B |= (1 << WGM12);   // Turn on bit WGM12 to enable CTC mode
  TCCR1B &= ~(1 << WGM13);  // Make sure bit WGM13 is off
}

// This function makes the Arduino wait (delay) for a few seconds
void delayS(unsigned int delay){
  // Set how long 1 second is for the timer, based on CPU speed and prescaler
  OCR1A = (F_CPU * 1 / 256) - 1;

  // Start Timer1 in CTC mode with a prescaler of 256
  TCCR1B |= (1 << WGM12) | (1 << CS12);

  unsigned int counter = 0;

  // If delay is more than 0, start counting seconds
  if (delay > 0) {
    TCNT1 = 0;  // Reset the timer count to 0
    while (!(TIFR1 & (1 << OCF1A))){}  // Wait until timer hits the match value
    TIFR1 |= (1 << OCF1A);  // Clear the match flag (reset it)
    counter++;

    // Keep repeating this until we reach the number of seconds requested
    while (counter < delay) {
      TCNT1 = 0;  // Reset timer again
      while (!(TIFR1 & (1 << OCF1A))){}  // Wait again
      TIFR1 |= (1 << OCF1A);  // Clear flag again
      counter++;  // Add 1 to the second counter
    }
  }

  // Stop the timer by turning off its settings
  TCCR1B &= ~((1 << WGM12) | (1 << CS12) | (1 << CS10));
}

// This function makes the Arduino wait (delay) for a few milliseconds
void delayMs(unsigned int delay){
  // Set how long 1 millisecond is for Timer0
  OCR0A = (int)(F_CPU / 64 * 0.001) - 1;

  // Start Timer0 with a prescaler of 64
  TCCR0B |= (1 << CS01) | (1 << CS00);

  unsigned int counter = 0;

  // If delay is more than 0, start counting milliseconds
  if (delay > 0) {
    TCNT0 = 0;  // Reset Timer0
    while (!(TIFR0 & (1 << OCF0A))){}  // Wait until it matches
    TIFR0 |= (1 << OCF0A);  // Clear match flag
    counter++;

    // Keep counting until we reach the delay in ms
    while (counter < delay) {
      TCNT0 = 0;  // Reset Timer0
      while (!(TIFR0 & (1 << OCF0A))){}  // Wait for match
      TIFR0 |= (1 << OCF0A);  // Clear the match flag
      counter++;  // Add 1 to millisecond counter
    }
  }

  // Turn off Timer0 so it stops running
  TCCR0B &= ~((1 << CS01) | (1 << CS00));
}

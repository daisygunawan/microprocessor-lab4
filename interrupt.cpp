#include "interrupt.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Initialize external interrupt
void initInterrupts() {
    EICRA = (1 << ISC00);  // Trigger on any logical change
    EIMSK = (1 << INT0);   // Enable external interrupt on INT0 (PORTD0)
}

// External interrupt service routine for motor control
ISR(INT0_vect) {
    motorControl();  // Handle motor control logic
}

void motorControl() {
    // Toggle motor state: turn it off when pressed
}

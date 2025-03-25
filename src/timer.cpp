#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Initialize Timers for debounce and countdown
void initTimers() {
    // Timer0 for debounce
    TCCR0B = (1 << CS02) | (1 << CS00);  // Prescaler
    TIMSK0 = (1 << TOIE0);  // Enable overflow interrupt for Timer0

    // Timer1 for countdown
    TCCR1B = (1 << WGM12) | (1 << CS12);  // CTC mode, prescaler
    TIMSK1 = (1 << OCIE1A);  // Enable compare interrupt
}

// Countdown logic
void countdown() {
    // Implement countdown logic for 7-segment display
}

// Timer0 interrupt for debouncing switch
ISR(TIMER0_OVF_vect) {
    // Debounce logic for the switch
}

// Timer1 interrupt for countdown
ISR(TIMER1_COMPA_vect) {
    countdown();  // Call countdown
}

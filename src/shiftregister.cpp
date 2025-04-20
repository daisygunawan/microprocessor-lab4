// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include <avr/io.h>  // Include AVR I/O definitions for register manipulation
#include "shiftregister.h"  // Include the shift register header file
#include "timer.h"  // Include the timer header file

// Initialize the shift register by configuring data direction and setting SRCLR high
void initShiftRegister(){
    DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);  // Set PA0, PA1, PA2, PA3 as output
    PORTA |= (1 << PORTA3);  // Set PA3 (SRCLR) high to disable clear functionality (active low)
}

// Clear the shift register by toggling the SRCLR pin
void clearShiftRegister(){
    PORTA &= ~(1 << PORTA3);  // Set PA3 (SRCLR) low to clear the shift register
    PORTA |= (1 << PORTA3);   // Set PA3 (SRCLR) high again to resume normal operation
    PORTA |= (1 << PORTA2);   // Latch the data to output pins
    PORTA &= ~(1 << PORTA2);  // Toggle PA2 to update the shift register
}

// Write a 7-bit binary value to the shift register
void writeShiftRegister(int bin){
    // Check if the first bit of 'bin' is 1 or 0 and set the shift register input accordingly
    if (bin & (1 << 0)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    // Repeat the same for the second bit
    if (bin & (1 << 1)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    // Repeat the same for the third bit
    if (bin & (1 << 2)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    // Repeat the same for the fourth bit
    if (bin & (1 << 3)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    // Repeat the same for the fifth bit
    if (bin & (1 << 4)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    // Repeat the same for the sixth bit
    if (bin & (1 << 5)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    // Repeat the same for the seventh bit
    if (bin & (1 << 6)) {
        PORTA |= (1 << PORTA0);  // Set PA0 high for bit 1
    }
    else{
        PORTA &= ~(1 << PORTA0);  // Set PA0 low for bit 0
    }
    PORTA |= (1 << PORTA1);  // Pulse the clock to shift in the next bit
    PORTA &= ~(1 << PORTA1); // Reset the clock pulse

    PORTA |= (1 << PORTA2);  // Latch the data to output pins
    PORTA &= ~(1 << PORTA2); // Toggle PA2 to update the shift register
}

// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include <avr/io.h> // Includes AVR I/O definitions so we can access registers like DDRC and PORTC
#include "sevensegment.h" // Includes our custom header for 7-segment display functions
#include "shiftregister.h" // Includes our custom header for shift register control

// This array holds the binary pattern for displaying digits 0 to 9 on a 7-segment display
uint8_t digits[10] = {
    0b00111111, // Digit 0
    0b00000110, // Digit 1
    0b01011011, // Digit 2
    0b01001111, // Digit 3
    0b01100110, // Digit 4
    0b01101101, // Digit 5
    0b01111101, // Digit 6
    0b00000111, // Digit 7
    0b01111111, // Digit 8
    0b01101111  // Digit 9
};

// This function sets all PORTC pins (PC0–PC7) as output to control the 7-segment segments
void initSevenSegment() {
    DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5) | (1 << DDC6) | (1 << DDC7);
    // Each bit in DDRC is set to 1 to make the corresponding PCx pin an output
}

// This function turns off all segments on the 7-segment display and clears the shift register
void clearDisplay() {
    PORTC &= ~((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3) |
               (1 << PORTC4) | (1 << PORTC5) | (1 << PORTC6) | (1 << PORTC7));
    // We clear all bits on PORTC to turn off all segments

    clearShiftRegister(); // Call a function to also clear any output stored in the shift register
}

// This function displays a digit (0–9) on both the main and shift register 7-segment displays
void toggleDisplay(int num) {
    for (int i = 0; i < 10; i++) { // Loop through 0 to 9
        if (num == i) { // If the input number matches the current loop value
            clearDisplay(); // Clear the display before showing a new digit

            PORTC = digits[num]; // Send the pattern for the selected number to PORTC
            writeShiftRegister(digits[num]); // Also send the same pattern to the shift register display
        }
    }
}

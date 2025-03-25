#include "sevensegment.h"
#include <avr/io.h>

// Initialize the 7-segment display (using PORTC)
void initSevenSegment() {
    DDRC = 0xFF;  // Set all PORTC pins as output
}

// Display a digit on the 7-segment display
void displayDigit(uint8_t digit) {
    static const uint8_t segCodes[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F  // 7-segment codes for digits 0-9
    };
    PORTC = segCodes[digit];  // Display the digit
}

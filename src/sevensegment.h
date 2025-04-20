// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include <avr/io.h> // For register definitions

// Initializes PORTC pins as outputs for the 7-segment display
void initSevenSegment();

// Turns off all segments on the display and clears the shift register
void clearDisplay();

// Displays a digit (0–9) on the 7-segment display
void toggleDisplay(int num);

#endif


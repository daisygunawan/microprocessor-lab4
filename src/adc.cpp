// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include "adc.h"
#include <avr/io.h>

// This function initializes ADC0 to read values from the analog pin A0
void initADC0()
{
    // Set reference voltage to AVcc (5V) by setting REFS0
    ADMUX |= (1 << REFS0);
    
    // Ensure REFS1 is cleared to ensure AVcc as reference voltage
    ADMUX &= ~(1 << REFS1);

    // Right-adjust the ADC result (default setting)
    ADMUX &= ~(1 << ADLAR);
    
    // Clear MUX5 to select a single-ended input for the ADC (no differential)
    ADCSRB &= ~(1 << MUX5);

    // Clear MUX0, MUX1, MUX2, MUX3, and MUX4 to select ADC0 as the input channel
    ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2));
    ADMUX &= ~((1 << MUX3) | (1 << MUX4));

    // Set the ADC to Free Running Mode, which allows continuous sampling
    ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));

    // Enable the ADC and auto trigger (auto-start on conversion)
    ADCSRA |= (1 << ADEN) | (1 << ADATE);

    // Set the ADC prescaler to 64, which gives an ADC clock of ~125kHz
    // This assumes a system clock of 8 MHz
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1);

    // Disable the digital input buffer on ADC0 to prevent any interference with the analog input
    DIDR0 |= (1 << ADC0D);

    // Start the first ADC conversion
    ADCSRA |= (1 << ADSC);
}

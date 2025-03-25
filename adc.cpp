#include "adc.h"
#include <avr/io.h>

// Initialize ADC
void initADC() {
    ADMUX = (1 << MUX0);  // Select A0 pin
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);  // Enable ADC, prescaler
}

// Read ADC value from A0 pin
uint16_t readADC() {
    ADCSRA |= (1 << ADSC);  // Start ADC conversion
    while (ADCSRA & (1 << ADSC));  // Wait for conversion to finish
    return ADC;  // Return the ADC value
}

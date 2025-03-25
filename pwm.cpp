#include "pwm.h"
#include <avr/io.h>

// Initialize PWM using Timer 3
void initPWM() {
    TCCR3A = (1 << COM3A1) | (1 << WGM30);  // Fast PWM mode, non-inverted
    TCCR3B = (1 << WGM32) | (1 << CS31);    // Prescaler and mode
    DDRB |= (1 << PB3);  // Set OC3A as output
}

// Change PWM duty cycle based on ADC value
void changeDutyCycle(uint16_t adcValue) {
    OCR3A = adcValue >> 2;  // 10-bit ADC to 8-bit duty cycle (divide by 4)
}

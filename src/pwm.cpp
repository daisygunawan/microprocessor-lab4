// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include "pwm.h"   // Include the header for PWM functions
#include <Arduino.h> // Include the Arduino core library

// Initializes Timer3 for Fast PWM mode to control motor speed
void initPWM() {
    // Set Timer3 for Fast PWM mode, non-inverting on OC3A (pin PE3)
    TCCR3A |= (1 << COM3A1) | (1 << WGM31) | (1 << WGM30); 
    // Continue Fast PWM mode and set no prescaler for Timer3
    TCCR3B |= (1 << WGM32) | (1 << CS30); 

    OCR3A = 0;  // Set the initial duty cycle to 0 (motor off)

    // Set PE3 (OC3A) as output to control the PWM signal
    DDRE = DDRE | (1 << PE3);
    // Set PH3 and PH4 as outputs for controlling motor direction
    DDRH = DDRH | (1 << PH3) | (1 << PH4);
}

// Controls motor direction via two output pins on PORT H (PH3 and PH4)
void setMotorDirection(unsigned int direction) {
    if (direction == 1) {           // If the direction is 1, set motor forward
        PORTH |= (1 << PH3);        // Set PH3 high (forward direction)
        PORTH &= ~(1 << PH4);       // Set PH4 low
    } else {                        // If the direction is 0, set motor in reverse
        PORTH |= (1 << PH4);        // Set PH4 high (reverse direction)
        PORTH &= ~(1 << PH3);       // Set PH3 low
    }
}

// Adjusts the PWM duty cycle based on ADC result (motor speed and direction)
void changeDutyCycle(unsigned int result) {
    switch (result) {
        // Special case for the neutral position (midpoint of ADC range)
        case (unsigned int)(1023 * 0.5):
            OCR3A = 0;  // Stop the motor by setting duty cycle to 0
            break;
        
        // Case for full reverse (ADC result is 0)
        case 0:
            setMotorDirection(0);  // Set motor direction to reverse
            OCR3A = 1023;  // Full speed in reverse
            break;

        // Case for full forward (ADC result is 1023)
        case 1023:
            setMotorDirection(1);  // Set motor direction to forward
            OCR3A = 1023;  // Full speed in forward direction
            break;

        default:
            // Handle the range where result is less than 512 (reverse)
            if (result < 512) {
                setMotorDirection(0);  // Set motor direction to reverse
                OCR3A = (511 - result) * 2;  // Increase speed as result moves from midpoint
            } 
            // Handle the range where result is greater than 512 (forward)
            else if (result > 512) {
                setMotorDirection(1);  // Set motor direction to forward
                OCR3A = (result - 512) * 2;  // Increase speed as result moves from midpoint
            }
            break;  // End of default case
    }
}


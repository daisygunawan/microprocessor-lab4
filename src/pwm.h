// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#ifndef PWM_H
#define PWM_H

// Function to initialize PWM on Timer3 to control motor speed
void initPWM();

// Function to set the motor's direction (0 for reverse, 1 for forward)
void setMotorDirection(unsigned int direction);

// Function to adjust the PWM duty cycle based on ADC result
void changeDutyCycle(unsigned int result);

#endif // PWM_H

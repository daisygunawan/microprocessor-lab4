#ifndef PWM_H
#define PWM_H

#include <stdint.h>

// Function prototypes
void initPWM();
void changeDutyCycle(uint16_t adcValue);

#endif

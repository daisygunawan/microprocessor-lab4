#include "adc.h"
#include "pwm.h"
#include "timer.h"
#include "interrupt.h"
#include "sevensegment.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int main() {
    // Initialize peripherals
    initADC();
    initPWM();
    initTimers();
    initInterrupts();
    initSevenSegment();

    while (1) {
        // Read ADC value and update PWM duty cycle
        uint16_t adcValue = readADC();
        changeDutyCycle(adcValue);

        // Main state machine logic for motor control
    }
}

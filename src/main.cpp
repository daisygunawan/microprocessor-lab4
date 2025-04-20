// Author       : Daisy, Priska, Jessica, Jennifer
// Group        : 5
// Date         : 4/20/2025
// Project Name : Group Lab 4
//
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include "sevensegment.h"
#include "shiftregister.h"
#include "switch.h"
#include "pwm.h"
#include "adc.h"
#include "timer.h"

#define DEBOUNCE_DELAY 50  // Define the debounce delay time

typedef enum {
  wait_press,         // State for waiting for a button press
  debounce_press,     // State for debounce after button press
  wait_release,       // State for waiting for button release
  debounce_release,   // State for debounce after button release
} current_state;

volatile current_state state = wait_press;  // Set initial state to wait for button press
bool delay_state = 0;                       // Button press status
volatile bool isInterrupt = true;           // Flag for enabling/disabling interrupt
volatile int displayDigit = 9;              // Start countdown from 9

int main(){
  initTimer0();              // Initialize timer0 for debouncing
  initTimer1();              // Initialize timer1 for countdown
  initSwitchPD0();           // Configure external interrupt on PD0 (switch)
  initSevenSegment();        // Initialize 7-segment display
  initShiftRegister();       // Initialize shift register (if used)
  initPWM();                 // Initialize PWM for motor control
  initADC0();                // Initialize ADC on A0 for analog input
  sei();                     // Enable global interrupts

  unsigned int result;       // Variable to store ADC result

  while (1) {
    if (state == wait_press) {             // If state is 'wait_press'
      if (delay_state == 1) {              // If button is pressed
        result = (1023 * 0.5);             // Set default 50% duty cycle
        displayDigit = 9;                  // Start countdown from 9
        changeDutyCycle(result);           // Apply the PWM duty cycle
        toggleDisplay(displayDigit);       // Display the digit on 7-segment
        delayS(1);                         // Wait for 1 second

        if (displayDigit > 0) {
          while (displayDigit > 0) {      // Count down from 9 to 0
            displayDigit--;               
            toggleDisplay(displayDigit);  // Update the display
            delayS(1);                    // Wait for 1 second
          }
        } else {
          state = debounce_press;          // After countdown, go to debounce_press
          displayDigit = 9;                // Reset the display digit for the next run
          isInterrupt = true;              // Re-enable the interrupt
        }
      }

      result = ADCL;                              // Read the lower byte of the ADC result
      result += ((unsigned int)ADCH) << 8;       // Combine it with the higher byte
      changeDutyCycle(result);                   // Update motor speed based on ADC value
      clearDisplay();                            // Clear the display
    } 

    else if (state == debounce_press) {          // If state is 'debounce_press'
      delayMs(30);                               // Wait for 30 ms for debounce
      state = wait_release;                      // Move to 'wait_release' state
    }

    else if (state == wait_release) {            // If state is 'wait_release'
      if (delay_state == 0) {                    // If the button is released
        state = debounce_release;                // Go to 'debounce_release' state
      }
    }

    else if (state == debounce_release) {        // If state is 'debounce_release'
      delayMs(30);                               // Wait for 30 ms for debounce
      state = wait_press;                        // Return to 'wait_press' state
      result = ADCL;                             // Read the lower byte of the ADC result
      result += ((unsigned int)ADCH) << 8;       // Combine it with the higher byte
      changeDutyCycle(result);                   // Update motor speed based on ADC value
      clearDisplay();                            // Clear the display
    }
  }

  return 0;
}

// External interrupt routine for INT0 (PD0)
ISR(INT0_vect) {
  if (delay_state == 0) {
    delay_state = 1;  // Toggle button state to pressed
  } else {
    delay_state = 0;  // Toggle button state to released
  }
}

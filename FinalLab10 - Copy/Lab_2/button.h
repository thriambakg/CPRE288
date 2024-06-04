/*
 * button.h
 *
 *  Created on: Nov 5, 2020
 *      Author: trg1
 */



#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <stdbool.h>
#include "driverlib/interrupt.h"

extern volatile int button_event; // Boolean to keep track of whether a hardware event has happened (button pressed)
extern volatile int button_num; // keeps track of button pressed

// initialize the push buttons
void button_init();

// Initialize GPIO interrupts for buttons
void init_button_interrupts();

// handler for gpio event when button is pressed
void gpioe_handler();

// Returns 8-bit integer with bits 0:5 indicating if button is pressed (set)
// or not (cleared)
uint8_t button_checkButtons();

// Non-blocking call
// Returns highest value button being pressed, 0 if no button pressed
uint8_t button_getButton();

#endif /* BUTTON_H_ */




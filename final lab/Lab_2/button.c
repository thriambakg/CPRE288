/*
 * button.c
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton, Zhao Zhang, Chad Nelson, & Zachary Glanz.
 *
 *  @edit: Lindsey Sleeth and Sam Stifter on 02/04/2019
 *  @edit: Phillip Jone 05/30/2019: Mearged Spring 2019 version with Fall 2018
 */



//The buttons are on PORTE 3:0
// GPIO_PORTE_DATA_R -- Name of the memory mapped register for GPIO Port E,
// which is connected to the push buttons
#include "button.h"


/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init() {
    static uint8_t initialized = 0;

    //Check if already initialized
    if(initialized){
        return;
    }


    // Reading: To initialize and configure GPIO PORTE, visit pg. 656 in the
    // Tiva datasheet.

    // Follow steps in 10.3 for initialization and configuration. Some steps
    // have been outlined below.

    // Ignore all other steps in initialization and configuration that are not
    // listed below. You will learn more about additional steps in a later lab.

    // 1) Turn on PORTE system clock, do not modify other clock enables
    SYSCTL_RCGCGPIO_R |= 0b00010000;//correct

    // 2) Set the buttons as inputs, do not modify other PORTE wires
    GPIO_PORTE_DIR_R &= 0b11110000;//correct

    // 3) Enable digital functionality for button inputs,
    //    do not modify other PORTE enables
    GPIO_PORTE_DEN_R |= 0b00001111;//GET CHECKED


    initialized = 1;
}




/**
 * Returns the position of the leftmost button being pushed.
 * @return the position of the leftmost button being pushed. 4 is the leftmost button, 1 is the rightmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton() { //ALL EDITED ON 9/7/2020, MAY NEED TO START OVER

   // #warning "Unimplemented function: uint8_t button_getButton(void)"   // delete warning after implementing



    // TODO: Write code below -- Return the left must button position pressed

    // INSERT CODE HERE!

    int x; //ALL EDITED ON 9/7/2020, MAY NEED TO START OVER
        for(x=3;x>=0;x--){
            if( ((GPIO_PORTE_DATA_R >> x) & 1) == 0 ){
                return (x+1);
            }
        }

    return 0; // EDIT ME
}





/*
 * servo.c
 *
 *  Created on: Oct 21, 2020
 *      Author: jmonty
 */

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include "driverlib/interrupt.h"
#include <inc/tm4c123gh6pm.h>

void servo_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x02; //port B clock enable
    GPIO_PORTB_AFSEL_R |= 0x20; //alt function enable
    GPIO_PORTB_PCTL_R |= 0x00700000; //alt function select
    GPIO_PORTB_DEN_R |= 0x20; //pin B5 digital enable
    GPIO_PORTB_DIR_R |= 0x20; //setting pinB5 to output
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1; //enabling Timer 1b clock
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN; //disabling timer during configuration
    TIMER1_CFG_R |= 0x04; //selecting timer configuration
    TIMER1_TBMR_R |= 0xA; //setting PWM and Timer mode --> PWM has periodic counting
    unsigned int pwm_period = 20 * 1000 * 16; //clock cycle start value --> this is the milliseconds to clock cycles
    TIMER1_TBILR_R = pwm_period & 0xFFFF; //set start value's lower 16 bits
    TIMER1_TBPR_R = pwm_period >> 16; //set start value's next 8 bits
    TIMER1_TBMATCHR_R = (195 * 100 * 16); //setting proper match value with match register --> 195 * 100 * 16 //may add &0xFFFF at end
    TIMER1_TBPMR_R = (195 * 100 * 16) >> 16; //same as above comment--> you need both registers --> (195 * 100 * 16) >> 16
    TIMER1_CTL_R |= TIMER_CTL_TBEN; //re-enabling timer after configuration
}

int servo_move(float degrees)
{
    unsigned int newvalue;
    newvalue = (TIMER1_TBPMR_R << 16) + TIMER1_TBMATCHR_R - (160 * degrees);
    TIMER1_TBMATCHR_R = (newvalue);
    TIMER1_TBPMR_R = (newvalue) >> 16;
    return 0; //do we need this line?
}


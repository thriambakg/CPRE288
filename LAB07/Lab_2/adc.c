/*
 * adc.c
 *
 *  Created on: Oct 6, 2020
 *      Author: jmonty
 */

#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"
#include "Timer.h"
#include <math.h>
#include "cyBot_uart.h"

void adc_init(){//code added on 10/6/20, need to verify accuracy -- if correct, then done?
    //GPIO initialization
    SYSCTL_RCGCGPIO_R |= 0b000010; //enable ADC0 port D clock
    SYSCTL_RCGCADC_R |= 0b0001; //set ADC clock
    GPIO_PORTB_AFSEL_R |= 0x10; //set Port B pin 4 alternate function
    GPIO_PORTB_DIR_R &= 0b11101111; //set port D pin 4 to input
    GPIO_PORTD_DEN_R &= 0b11101111; //set digital enable to off for Port B pin 4
    GPIO_PORTB_AMSEL_R |= 0b00010000; //enable analog mode for pin B4
    GPIO_PORTB_ADCCTL_R = 0x00; //not using any pins to trigger ADC conversion

    //ADC initialization
    ADC0_ACTSS_R &= ~(0x00000002); //during config, disable ADC0 sample sequencer SS1 by clearing bit 0
    ADC0_EMUX_R &= ~(0x000000F0); //set SS1 trigger via ADCPSSI register
    ADC0_SSMUX1_R |= 0x000A; //set first sample to use AIN10 ADC pin
    ADC0_SSCTL1_R = 0x00000000; //clear register to 0 first, going to use channel 1 first, channel 9 second
    ADC0_SSCTL1_R |= 0x00000060; //then set bits 1 and 2 for second sample
    ADC0_SAC_R |= 0x4; //set sample averaging for 16x hardware oversample
    ADC0_ACTSS_R |= 0x00000002;//reenable ADC0 sample sequencer SS1

}

int adc_read(void){

    ADC0_PSSI_R = ADC_PSSI_SS0;//initiate SS1
    while((ADC0_RIS_R & ADC_RIS_INR0)== 0){//pause while conversion in process until complete
    }

    int value = ADC0_SSFIFO0_R; //retrieve value stored in SS FIFO containing conversion result
    return value;
}




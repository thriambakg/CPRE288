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
#include "adc.h"
#include <inc/tm4c123gh6pm.h>

float coeff_A = 1.217e8;
float coeff_B = -2.143;
float y_intercept = 5;

/**
 * @brief Sets up the infrared sensor.
 *
 */
void ir_init(void)
{

    // Turn on the clock for GPIO Port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    // Turn on the clock for ADC0
    SYSCTL_RCGCADC_R |= BIT0;

    // Enable alternate function for GPIO PB4
    GPIO_PORTB_AFSEL_R |= PB4;

    // Configure the pin PB4 for input and analog mode
    GPIO_PORTB_DIR_R &= ~PB4;
    GPIO_PORTB_DEN_R &= ~PB4;
    GPIO_PORTB_AMSEL_R |= PB4;

    // Don't use PB4 as the trigger source, use the program
    GPIO_PORTB_ADCCTL_R &= ~PB4;

    // Disable SS0, sample sequencer 0, for configuration
    ADC0_ACTSS_R &= ~BIT0;

    // Set SS0 to trigger from ADCPSSI
    ADC0_EMUX_R &= 0xFFF0;

    // Sample channel 10
    ADC0_SSMUX0_R |= 0xA;

    // Clear sample sequence control register
    ADC0_SSCTL0_R = 0x0;

    // Set sample sequencer to end and flag after first sample
    ADC0_SSCTL0_R |= 0x6;

    // Re-enable ADC0 SS0
    ADC0_ACTSS_R |= 0x1;
}

/**
 * @brief Sets the amount of hardware averaging: 2^rate. Max is 6
 *
 */
void ir_setAvg(int avg_rate)
{
    if (avg_rate < 7)
    {
        ADC0_SAC_R = avg_rate;
    }
}

/**
 * @brief Returns the raw value of the ADC connected to PB4 (IR sensor).
 *
 * @return int raw value of PB4
 */
int ir_read(void)
{

    // Initiate SS0 conversion sequence
    ADC0_PSSI_R = 0x1;

    // Wait for SS0 ADC conversions to complete
    while (~ADC0_RIS_R & BIT0)
    {
    }

    // Clear the raw interrupt status flag for SS0
    ADC0_ISC_R = BIT0;

    // Return channel 10 from FIFO buffer
    return ADC0_SSFIFO0_R;
}

/**
 * @brief Returns the distance read by the IR sensor in cm.
 *
 * @return int IR sensor distance in cm
 */
double ir_readCM(double max_dist)
{
    // Map the timer value to distance
    double distance = (coeff_A) * pow(ir_read(), coeff_B) + y_intercept;

    // Return 0 if distance is outside usable range of IR sensor
    return (distance > max_dist ? max_dist : distance);
}

/**
 * @brief Returns the distance read by the IR sensor in cm, averaged avg_times
 * number of times. Returns 0 if read distance is outside range of max_dist
 *
 * @param max_dist maximum valid distance for the returned data
 * @param avg_times number of samples to average
 * @return double IR sensor distance in cm
 */
double ir_read_avgCM(double max_dist, int avg_times)
{
    double total = 0;

    int i;
    for (i = 0; i < avg_times; i++)
    {
        total += ir_readCM(max_dist);
    }

    return total / ((float) avg_times);
}















// Infrared Sensor

//void adc_init(){//code added on 10/6/20, need to verify accuracy -- if correct, then done?
//    //GPIO initialization
//    SYSCTL_RCGCGPIO_R |= 0b000010; //enable ADC0 port D clock
//    SYSCTL_RCGCADC_R |= 0b0001; //set ADC clock
//    GPIO_PORTB_AFSEL_R |= 0x10; //set Port B pin 4 alternate function
//    GPIO_PORTB_DIR_R &= 0b11101111; //set port D pin 4 to input
//    GPIO_PORTD_DEN_R &= 0b11101111; //set digital enable to off for Port B pin 4
//    GPIO_PORTB_AMSEL_R |= 0b00010000; //enable analog mode for pin B4
//    GPIO_PORTB_ADCCTL_R = 0x00; //not using any pins to trigger ADC conversion
//
//    //ADC initialization
//    ADC0_ACTSS_R &= ~(0x00000002); //during config, disable ADC0 sample sequencer SS1 by clearing bit 0
//    ADC0_EMUX_R &= ~(0x000000F0); //set SS1 trigger via ADCPSSI register
//    ADC0_SSMUX1_R |= 0x000A; //set first sample to use AIN10 ADC pin
//    ADC0_SSCTL1_R = 0x00000000; //clear register to 0 first, going to use channel 1 first, channel 9 second
//    ADC0_SSCTL1_R |= 0x00000060; //then set bits 1 and 2 for second sample
//    ADC0_SAC_R |= 0x4; //set sample averaging for 16x hardware oversample
//    ADC0_ACTSS_R |= 0x00000002;//reenable ADC0 sample sequencer SS1
//
//}
//
//int adc_read(void){
//
//    ADC0_PSSI_R = ADC_PSSI_SS0;//initiate SS1
//    while((ADC0_RIS_R & ADC_RIS_INR0)== 0){//pause while conversion in process until complete
//    }
//
//    int value = ADC0_SSFIFO0_R; //retrieve value stored in SS FIFO containing conversion result
//    return value;
//}


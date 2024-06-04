/*
*
*   uart_extra_help.c
* Description: This is file is meant for those that would like a little
*              extra help with formatting their code, and followig the Datasheet.
*/

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "uart_extra_help.h"
#define REPLACE_ME 0x00
volatile  char uart_data;  // Your UART interrupt code can place read data here
volatile  char flag;       // Your UART interrupt can update this flag

void uart_init(int baud)
{//code below edited 9/23
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;      // enable clock GPIOB (page 340)//
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R = 0x3;      // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R  = 0x00000011;       // pmc0 and pmc1       (page 688)  also refer to page 650
    GPIO_PORTB_DEN_R   = (0x02 | 0x01);        // enables pb0 and pb1
    GPIO_PORTB_DIR_R   = (~0x01 | 0x02);        // sets pb0 as output, pb1 as input

    //compute baud values [UART clock= 16 MHz]
    double fbrd;
    int    ibrd;

    ibrd = 8; //16,000,000 / (16 * 9600) = 104.16666 104
    fbrd = 44;  // .1666*64+.5 = 11.16666 11  -- NOTE THESE VALUES HAVE TO CHANGE BECAUSE BAUD RATE -- 44/8

    UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART1 (page 918)
    UART1_IBRD_R = 8; //16,000,000 / (16 * 9600) = 104.16666 104        // write integer portion of BRD to IBRD
    UART1_FBRD_R = 44;  // .1666*64+.5 = 11.16666 11   // write fractional portion of BRD to FBRD
    UART1_LCRH_R = UART_LCRH_WLEN_8; //0x60        // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R   = 0;//UART_CC_CS_SYSCLK;          // use system clock as clock source (page 939)
    UART1_CTL_R |= UART_CTL_UARTEN;        // enable UART1

}

void uart_sendChar(char data) //code below added 9/23, not sure if it will work
{
    while(UART1_FR_R & 0x20){
        }
        UART1_DR_R = data;
}

int uart_receive(void) //code below added 9/23, not sure if it will work
{
    char data = 0;
    while(UART1_FR_R & UART_FR_RXFE){// Waiting for text from portal
    }
    data = (char) (UART1_DR_R & 0xFF);// set the data equal to the text received
    return data;
}

void uart_sendStr(const char *data) //code below added 9/23, not sure if it will work
{
    int i = 0;
    while(data[i] != 0){//Send the character chars individually (i.e., one by one)
        uart_sendChar(data[i]);
        i++;
    }
}

// _PART3


void uart_interrupt_init(void) //code below added 9/23, not sure if it will work
{
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0b00010000; //enable interrupt on receive - page 924

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R |= 0x00000040; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(INT_UART1, uart_interrupt_handler); //give the micro-controller the address of our interrupt handler - page 104 22 is the vector number
}

void uart_interrupt_handler(void) //code below added 9/23, not sure if it will work
{
    flag = 1; //set flag to 1, taken from uart_extra_help.h file, related to extern volatile  char flag;

    // STEP1: Check the Masked Interrupt Status
    if(UART1_MIS_R & UART_MIS_RXMIS){// did we receive a byte?

    //STEP2:  Copy the data
        uart_data = (char) (UART1_DR_R & 0xFF); //taken from uart_extra_help.h file, related to extern volatile  char uart_data;

    //STEP3:  Clear the interrupt
        UART1_ICR_R |= UART_ICR_RXIC; //clearing the bit by writing a 1 to the 4 bit
    }

}



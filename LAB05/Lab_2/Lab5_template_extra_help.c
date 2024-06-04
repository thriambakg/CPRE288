/**
 * lab5_template_extra_help.c
 *
 * Description: This is file is meant for those that would like a little
 *              extra help with formatting their code.
 *
 */

#define _RESET 1
#define _PART1 0
#define _PART2 0
#define _PART3 0

#include "timer.h"
#include "lcd.h"
#include "uart.h"

#if _RESET
#include "Simulation_User Files_resetSimulation.h"
#endif

// Adding global volatile varibles for communcating between 
// your Interupt Service Routine, and your non-interupt code.

volatile  char uart_data;  // Your UART interupt code can place read data here
volatile  char flag;       // Your UART interupt can update this flag
                           // to indicate that it has placed new data
                           // in uart_data                     


void main()
{
#if _RESET
    resetSimulationBoard();
#else

    timer_init();
    lcd_init();

#if _PART1      // Receive and display text
    // TODO
	

#endif

#if _PART2      // Echo Received Character
	// TODO

#endif

#if _PART3 // Receive and send characters using interrupts.
 // TODO
 
#endif

#endif
}


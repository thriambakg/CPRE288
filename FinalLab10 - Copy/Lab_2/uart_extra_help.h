/*
*   uart.h
*   Used to set up the UART [UART1 at 115200]
*
 * Description: This is file is meant for those that would like a little
 *              extra help with formatting their code.
*/

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

// These two varbles have been declared
// in the file containing main



void uart_init(int baud);

void uart_sendChar(char data);

int uart_receive(void);

void uart_sendStr(const char *data);

void uart_interrupt_init(void);

void uart_interrupt_handler(void);

#endif /* UART_H_ */

/*
 * ping.h
 *
 *  Created on: Oct 13, 2020
 *      Author: jmonty
 */

#ifndef PING_H_
#define PING_H_

volatile enum {LOW, HIGH, DONE} state;
void ping_init();
void ping_read(void);
unsigned send_pulse();
void TIMER1A_HANDLER(void);
#endif /* PING_H_ */

/*
 *
 *  Created on: 10/29/2020
 *      Author: Group s3-b
 */

#ifndef PING_H_
#define PING_H_

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "driverlib/interrupt.h"


void ping_init(void);

void ping_pulse(void);

void ping_captureHandler(void);

double ping_read(unsigned int max_dist);

#endif /* PING_H_ */

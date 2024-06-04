/*
 * movement.h
 *
 *  Created on: Sep 8, 2020
 *      Author: trg1
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "open_interface.h"

void move_forward(oi_t *sensor, int centimeters);
void move_backward(oi_t *sensor, int centimeters);
void turn_left(oi_t *sensor, int degrees);
void turn_right(oi_t *sensor, int degrees);


#endif /* MOVEMENT_H_ */

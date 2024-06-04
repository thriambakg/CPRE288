/*
 * movement.h
 *
 *  Created on: Sep 8, 2020
 *      Author: trg1
 */

#include "open_interface.h"
#include "timer.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


void move_forward(oi_t *sensor, int millimeters);
void turn_right(oi_t *sensor, int degrees);
void turn_left(oi_t *sensor, int degrees);
void move_forward_collision(oi_t *sensor, int millimeters);
int move_forward_cliff(oi_t *sensor, int millimeters);
void move_backward(oi_t *sensor, int millimeters);



#endif /* MOVEMENT_H_ */

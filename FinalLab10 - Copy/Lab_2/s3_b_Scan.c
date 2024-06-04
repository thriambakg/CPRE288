/*
 * s3-b_Scan.c
 *
 *  Created on: Oct 31, 2020
 *      Author: trg1
 */


#include <s3_b_Scan.h>
#include "adc.h"
#include "ping (1).h"
#include "servo.h"
#include "timer.h"


void s3_b_init(void)
{
    timer_init();
    ping_init();
    adc_init();
    servo_init();
}

//moves by an angle

double s3_b_Scan(double angle)
{
    servo_move(angle);

    double irdist = adc_read();
    return irdist;

}


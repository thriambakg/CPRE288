///*
// *
// *  Created on: 10/29/2020
// *      Author: Group s3-b
// */
//
//#include "ir.h"
//#include "lcd.h"
//#include "adc.h"
//#include "ping (1).h"
//#include "servo.h"
//#include "timer.h"
//#include "uart.h"
//#include <inc/tm4c123gh6pm.h>
//#include <math.h>
//#include <stdlib.h>
//#include "resetSimulation.h"
//
//#define NUM_SAMPLES 10
//
//double getDist(double i){
//    double dist;
//    // calibrate our distance to our line of best fit from our test data
//    dist = 154877 * pow(i, -1.208);
//    return dist;
//}
//
//int main(void) {
//  lcd_init();
//  timer_init();
//  ping_init();
//  adc_init();
//  //uart_init(115200);
//  resetSimulationBoard();
//
//  while (1)
//  {
//    char str[100];
//    double irDistance =getDist(adc_read());
//
//    double pingDistance = ping_read(100);
//
//    //uart prints
//    //sprintf(str, " Distance: %.2f, %.2f \n\r", irDistance, pingDistance);
//    //sprintf(str, " Distance: %d \n\r", irDistance);
//    //uart_sendStr(str);
//
//    //lcd prints
//    lcd_printf("Distance: %.2f, %.2f", irDistance, pingDistance);
//
//    timer_waitMillis(500);
//    lcd_clear();
//  }
//}

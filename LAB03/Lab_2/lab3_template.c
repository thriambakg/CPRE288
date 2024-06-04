/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "lcd.h"
#include "button.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "open_interface.h"
#include "Timer.h"
#include "resetSimulation.h"
#include <string.h>
/**
 * main.c
 * Prints the button that has been pressed
 */
int main(void)
{

    // Hint: You may need to use pointers to return the button that has been pressed
    cyBot_uart_init();
    timer_init();
    lcd_init();
    button_init();
    init_button_interrupts();

    //checkpoint 4
//    while (1 == 1)
//    {
//        int buttonValue = button_getButton();
//        if (buttonValue == 1)
//        {
//            cyBot_sendByte('1');
//        }
//        else if (buttonValue == 2)
//        {
//            cyBot_sendByte('2');
//        }
//        else if (buttonValue == 3)
//        {
//            cyBot_sendByte('3');
//        }
//        else if (buttonValue == 4)
//        {
//            cyBot_sendByte('4');
//        }
//        else
//        {
//            cyBot_sendByte('0');
//        }
//    }

    oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);


    while (true)
    {
        char value = cyBot_getByte();
        if (strcmp(value,'w')==0)
        {
            move_forward(sensor_data,1);
        }
        else if (strcmp(value,'d')==0)
        {
            turn_left(sensor_data,1);
        }
        else if (strcmp(value,'a')==0)
        {
            turn_right(sensor_data,1);
        }
        else if (strcmp(value,'s')==0)
        {
            move_backward(sensor_data,-1);
        }



    }
    oi_free(sensor_data);
}

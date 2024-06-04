/**
 * lab7_main.c
 */

//note, may also need to add .c and .h files for averaging functionality (part 2) and file creation functionality (part 3)
#include "lcd.h"
#include "cyBot_uart.h"
#include "button.h"
#include "adc.h"
#include "timer.h"

lcd_init();
timer_init();
cyBot_uart_init();

//extern volatile char buffer[21]; // create our line buffer
//extern volatile char cur; // initialize current character to null
//extern volatile int len; // number of chars printed this line

/**
 * main.c
 */
//convert
//int getDist(int i)
//{
//    int dist;
//    // calibrate our distance to our line of best fit from our test data
//    dist = 240321 * pow(i, -1.284) + 1;
//    return dist;
//}

int main(void)
{
    //inits
    lcd_init();
    adc_init();
    uart_init();
    timer_waitMillis(500);
    //send data headers
    uart_sendStr("reading,distance\n\r");
    while (true)
    {
        //Get result from adc_read
        int fifo_result = adc_read();
        //Convert analog value to distance (cm)
        //int distance = getDist(fifo_result);
        char str1[80];
        sprintf(str1, "%d\n\r", fifo_result);
        lcd_printf(str1); //display info on lcd screen
        //uart_sendStr(str1); // sent string to putty using uart
        timer_waitMillis(500); // wait 500 milliseconds
    }
}
//must add functionality for all three parts


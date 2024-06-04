//**
// * lab4_template.c
// *
// * Template file for CprE 288 lab 4
// *
// * @author Zhao Zhang, Chad Nelson, Zachary Glanz
// * @date 08/14/2016
// *
// * @author Phillip Jones, updated 6/4/2019
// */
//
//#include "lcd.h"
//#include "button.h"
//#include "movement.h"
//#include "open_interface.h"
//#include "Timer.h"
//#include "resetSimulation.h"
//#include <string.h>
//#include <stdio.h>
//
//#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
//// PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1
//
//#include "cyBot_Scan.h"  // For scan sensors
//
//#warning "Possible unimplemented functions"
//#define REPLACEME 0
//
//// Defined in button.c : Used to communicate information between the
//// the interupt handeler and main.
//extern volatile int button_event;
//extern volatile int button_num;
//
////int main(void)
//{
//
//    //button_init();
//    lcd_init();
//    //init_button_interrupts(button_event, button_num);
//
//
//
//
//    cyBot_uart_init_clean(); // Clean UART initialization, before running your UART GPIO init code
//
//    SYSCTL_RCGCGPIO_R |= 0x00000002;
//    timer_waitMillis(1); // Small delay before accessing device after turning on clock
//    GPIO_PORTB_AFSEL_R |= 0x03;
//    GPIO_PORTB_PCTL_R &= 0xFFFFFFEE;     // Force 0's in the desired locations
//    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
//    GPIO_PORTB_DEN_R |= 0b00000011;
//    GPIO_PORTB_DIR_R &= 0b11111110;      // Force 0's in the desired locations
//    GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the desired locations
//
//    cyBot_uart_init_last_half();  // Complete the UART device initialization part of configuration
//
//    // Initialze scan sensors
//    cyBOT_init_Scan();
//
//    // YOUR CODE HERE
//    char rec;// YOUR CODE HERE
//    cyBOT_Scan_t data;
//    int a, x;
//    char header[] = "Angle \t PING distance \t IR raw value \r \n";// headers with \t for tabs
//    char data_line[50];
//    int header_length = 34;
//    while(1)
//    {
//        rec = cyBot_getByte_blocking();
//        if (rec == 'm')
//        {
//            for(x=0;x<header_length;x++)
//            {
//                cyBot_sendByte(header[x]);
//            }
//            for (a=0;a<=180;a+=5)
//            {
//                cyBOT_Scan(a, &data);// YOUR CODE HERE
//
//                sprintf(data_line, "%d\t%.2f\t\t%d\r\n", a,data.sound_dist, data.IR_raw_val);
//                char* data_line_pos = data_line;
//                while(*data_line_pos !='\0'){cyBot_sendByte(*data_line_pos++);}
//            }
//            lcd_printf("DONE");
//        }
//    }
//
//
//}

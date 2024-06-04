/*
 * autoScan.c
 *
 *  Created on: Nov 5, 2020
 *      Author: trg1
 */

/*
 *
 *  Created on: 10/29/2020
 *      Author: Group s3-b
 */
#include "ir.h"
#include "lcd.h"
#include "adc.h"
#include "ping (1).h"
#include "servo.h"
#include "timer.h"
#include "uart_extra_help.h"
#include <inc/tm4c123gh6pm.h>
#include <math.h>
#include "s3_b_Scan.h"
#include <stdlib.h>
#include "resetSimulation.h"
#include "open_interface.h"
#include "movement.h"

void scaninit(void)
{
    uart_init(115200);
    s3_b_init();
}
void scan(int move_to) //not sure how to do this part
{
    //resetSimulationBoard();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    //incrementers
    int j, radial = 0, index = 0, w;
    double angle;
    double irDist;
    //header for table
    char header[] =
            "object #\tangle\tIR distance\tPing distance\tradial width\tlinear width\r\n";
    //data line length
    char data_line[50];
    //length of the header above
    //array of values
    int check = 0;
    double startangle, endangle;
    //temp variables be assigned to obstacles arrays
    int tempangle, tempdistance,pingDistance;
    //create struct with start degrees, end degrees, and distance
    struct obstacles
    {
        double startangle; //start of angle
        double radial; //radial degrees
        double irdistance; //IR distance from cybot
        double pingD;
        double linear; //linear radius
    };
    struct obstacles values[20];

    while (1)
    {
        //this is just for the header
        for (j = 0; j < strlen(header); j++)
        {
            uart_sendChar(header[j]);
        }

        //main for loop to increment measured values
        for (angle = 0.0; angle <= 180.0; angle++)
        {
            //change this
            irDist = s3_b_Scan(angle); // YOUR CODE HERE
            ;
            timer_waitMillis(100);
            if (irDist < 200)
            {
                if (check == 0)
                {
                    startangle = angle;
                }
                check = 1;
                tempdistance = irDist;
                pingDistance = ping_read(200);
                endangle = angle;

            }
            else if (check == 1)
            {
                if (endangle - startangle != 0)
                {
                    values[index].radial = endangle - startangle;
                    values[index].irdistance = tempdistance;
                    values[index].pingD = pingDistance;
                    values[index].startangle = (startangle + endangle) / 2;
                    values[index].linear = sqrt(
                            (2 * (pow(values[index].irdistance, 2)))
                                    - ((2
                                            * (values[index].irdistance
                                                    * values[index].irdistance)
                                            * cos(values[index].radial * 3.1415
                                                    / 180))));
                    index++;
                    startangle = 0;
                    endangle = 0;
                    tempdistance = 0;
                    pingDistance = 0;
                    check = 0;
                }
            }

        }
        for (w = 0; w < index; w++)
        {
            sprintf(data_line, "%d\t\t%.1f\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\r\n",
                    w + 1, values[w].startangle, values[w].irdistance,values[w].pingD,
                    values[w].radial, values[w].linear);
            char *data_line_pos = data_line;
            while (*data_line_pos != '\0')
            {
                //cyBot_sendByte(*data_line_pos++);
                uart_sendChar(*data_line_pos++);
            }
        }

        //sorter to find smallest object

        //objext found at 30 degrees @ 50 cm from bot

        //part 3
//        temp values
//        bracket values
//        need to
//        be[smallest]

        if (move_to == 1)
        {
            int smallest = 0;
            int e;
            int temp;
            for (e = 0; e < index; e++)
            {
                if (values[e].linear < values[smallest].linear)
                {
                    smallest = e;
                }

            }
            if (values[smallest].startangle > 90)
            {
                turn_right(sensor_data, values[smallest].startangle - 90);
            }
            else if (values[smallest].startangle < 90)
            {
                turn_left(sensor_data, 90 - values[smallest].startangle);
            }

            move_forward_collision(sensor_data, values[smallest].irdistance - 5);
            oi_free(sensor_data);
        }

        break;
        //for //create second for loop to go through objects found

    }
}


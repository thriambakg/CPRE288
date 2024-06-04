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

void main() //not sure how to do this part
{
    //resetSimulationBoard();
        uart_init(115200);
        s3_b_init();
        oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);

    //incrementers
    int  j, radial = 0, index = 0, w;
    double angle;
    double objectDist;
    //header for table
    char header[] =
            "object #\t angle\t distance\t radial width\t linear width\r\n";
    //data line length
    char data_line[50];
    //length of the header above
    //array of values
    int check = 0;
    double startangle, endangle;
    //temp variables be assigned to obstacles arrays
    int tempangle, tempdistance;
    //create struct with start degrees, end degrees, and distance
    struct obstacles
    {
        double startangle; //start of angle
        double radial; //radial degrees
        double distance; //distance from cybot
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
            objectDist = s3_b_Scan(angle); // YOUR CODE HERE
            timer_waitMillis(100);
            if (objectDist < 100)
            {
                if (check == 0)
                {
                    startangle = angle;
                }
                check = 1;
                tempdistance = objectDist;
                endangle = angle;

            }
            else if (check == 1)
            {
                if(endangle - startangle != 0)
                {
                values[index].radial = endangle - startangle;
                values[index].distance = tempdistance;
                values[index].startangle = (startangle + endangle) / 2;
                values[index].linear = sqrt((2 * (pow(values[index].distance, 2))) - ((2 * (values[index].distance * values[index].distance) * cos(values[index].radial*3.1415/180))));
                index++;
                startangle = 0;
                endangle = 0;
                tempdistance = 0;
                check = 0;
                }
            }

        }
        for (w = 0; w < index; w++)
        {
            sprintf(data_line, "\t %d \t %.2f \t %.2f \t %.2f \t %.2f \r\n", w + 1,
                    values[w].startangle, values[w].distance, values[w].radial,
                    values[w].linear);
            char *data_line_pos = data_line;
            while (*data_line_pos != '\0')
            {
                //cyBot_sendByte(*data_line_pos++);
                uart_sendChar(*data_line_pos++);
            }
        }

        //sorter to find smallest object

        //objext found at 30 degrees @ 50 cm from bot
            int smallest = 0 ;
            int e;
            int temp;
            for (e = 0; e < index; e++)
            {
                if (values[e].linear < values[smallest].linear)
                {
                    smallest = e;
                }

            }
        //part 3
//        temp values
//        bracket values
//        need to
//        be[smallest]
        if (values[smallest].startangle > 90)
        {
            turn_right(sensor_data,values[smallest].startangle-90);
        }
        else if (values[smallest].startangle < 90)
        {
            turn_left(sensor_data, 90-values[smallest].startangle);
        }

        int dist = 0; // distance traveled
        int dist_to_travel = values[smallest].distance-5; // distance to travel
        float modifier = 0.67; // Modifier to account for the speed of the robot and the stopping distance
        while (dist < (dist_to_travel * modifier))
        { // while we still have distance to travel
            if (sensor_data->bumpRight)
            { // if the left bumper is hit
                move_backward(sensor_data, 15); //move back 15 cm
                dist -= 13;
                turn_left(sensor_data, 80); //turn right
                move_forward(sensor_data, 30); //move forward 15 cm

                turn_right(sensor_data, 80); //turn left
                move_forward(sensor_data, 60);
                dist += 55;
                turn_right(sensor_data, 80);
                move_forward(sensor_data, 30);

                turn_left(sensor_data, 80);

            }
            else if (sensor_data->bumpLeft)
            { // if the right bumper is hit
                move_backward(sensor_data, 15); //move back 15 cm
                dist -= 13;
                turn_right(sensor_data, 80); //turn left
                move_forward(sensor_data, 30); //move forward 25
                turn_left(sensor_data, 80); //turn left
                move_forward(sensor_data, 60);

                dist += 55;
                turn_left(sensor_data, 80); //turn right
                move_forward(sensor_data, 30);

                turn_right(sensor_data, 80);
            }
            else
            { //while the bumpers are not hit
                move_forward(sensor_data, 1); //move forward 1 cm at a time until we reach dist
                dist++; //increment distance traveled
            }
        }
        oi_free(sensor_data);

        break;
        //for //create second for loop to go through objects found

    }
}

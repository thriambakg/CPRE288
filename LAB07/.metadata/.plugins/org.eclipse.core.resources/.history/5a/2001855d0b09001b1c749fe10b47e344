#include "Timer.h"
#include "lcd.h"
#include "button.h"
#include "resetSimulation.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "movement.h"
#include "open_interface.h"
#include <math.h>

void main() //not sure how to do this part
{
    //resetSimulationBoard();
    cyBot_uart_init();
    cyBOT_init_Scan();
    cyBOT_Scan_t data;
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    //incrementers
    int angle, j, radial = 0, index = 0, w;
    //header for table
    char header[] =
            "object #\t angle\t distance\t radial width\t linear width\r\n";
    //data line length
    char data_line[50];
    //length of the header above
    //array of values
    int check = 0;
    float startangle, endangle;
    //temp variables be assigned to obstacles arrays
    int tempangle, tempdistance;
    //create struct with start degrees, end degrees, and distance
    struct obstacles
    {
        float startangle; //start of angl
        int radial; //radial degrees
        int distance; //distance from cybot
        int linear; //linear radius
    };
    struct obstacles values[20];

    while (1)
    {
        //this is just for the header
        for (j = 0; j < strlen(header); j++)
        {
            cyBot_sendByte(header[j]);
        }

        //main for loop to increment measured values
        for (angle = 0; angle <= 180; angle+=2)
        {
            cyBOT_Scan(angle, &data); // YOUR CODE HERE
            if (data.sound_dist < 100)
            {
                if (check == 0)
                {
                    startangle = angle;
                }
                check = 1;
                tempdistance = data.sound_dist;
                endangle = angle;

            }
            else if (check == 1)
            {
                values[index].radial = endangle - startangle;
                values[index].distance = tempdistance;
                values[index].startangle = (startangle + endangle) / 2;
                values[index].linear = sqrt(
                        2 * (pow(tempdistance, 2))
                                + 2 * tempdistance * tempdistance
                                        * cos(radial));
                index++;
                radial = 0;
                check = 0;
            }

        }
        for (w = 0; w < index; w++)
        {
            sprintf(data_line, "%d \t %.2f \t %d \t %d \t %d \r\n", w + 1,
                    values[w].startangle, values[w].distance, values[w].radial,
                    values[w].linear);
            char *data_line_pos = data_line;
            while (*data_line_pos != '\0')
            {
                cyBot_sendByte(*data_line_pos++);
            }
        }

        //sorter to find smallest object

        //objext found at 30 degrees @ 50 cm from bot
//            int smallest;
//            int temp = values[0].linear;
//            for (int e = 1; e < index; e++)
//            {
//                if (values[e].linear < temp)
//                {
//                    temp = values[e].linear;
//                    smallest = e;
//                }
//
//            }
        //part 3
//        temp values
//        bracket values
//        need to
//        be[smallest]
        if (values[0].startangle < 90)
        {
            turn_left(sensor_data,values[0].startangle);
        }
        if (values[0].startangle > 90)
        {
            turn_right(sensor_data, values[0].startangle - 90);
        }

        int dist = 0; // distance traveled
        int dist_to_travel = values[0].distance; // distance to travel
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

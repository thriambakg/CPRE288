/**
 * main.c
 */
#include "open_interface.h"
#include "resetSimulation.h"
#include "movement.h"
int main(void)
{

    // resetSimulationBoard();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    int dist = 0; // distance traveled
    int dist_to_travel = 200; // distance to travel
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
            turn_right(sensor_data,80);
            move_forward(sensor_data,30);

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

            dist+=55;
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
}

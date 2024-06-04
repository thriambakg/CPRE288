#include "movement.h"
#include "uart_extra_help.h"
#include "open_interface.h"
#include "timer.h"

void move_forward(oi_t *sensor, int centimeters){
    oi_setWheels(300,300); //move forward full speed, 500mm/s
    int sum = 0;
    while(sum < centimeters * 10){ //while we are still moving
        oi_update(sensor);
        sum += sensor -> distance; //add change in distance
    }
    oi_setWheels(0,0); //stop moving
    return;
}

void turn_right(oi_t *sensor, int degrees){
    oi_setWheels(150,-150);//turn left
    int sum = 0;
    while(sum < degrees){//while we have not turned degrees
        oi_update(sensor);
        sum += sensor -> angle;//update sum with amount we have turned
    }
    oi_setWheels(0,0);
    return;//stop moving
}

void turn_left(oi_t *sensor, int degrees){
    degrees = -1 * degrees;
    oi_setWheels(-150,150);//turn right
    int sum = 0;
    while(sum > degrees){//while we have not turned degrees
        oi_update(sensor);
        sum += sensor -> angle;//update sum with amount we have turned
    }
    oi_setWheels(0,0);//stop moving
    return;
}

void move_forward_collision(oi_t *sensor, int dist_to_travel) {

    int dist = 0; // distance traveled
             // distance to travel
            float modifier = 0.67; // Modifier to account for the speed of the robot and the stopping distance
            while (dist < (dist_to_travel * modifier))
            { // while we still have distance to travel
                if (sensor->bumpRight)
                { // if the left bumper is hit
                    move_backward(sensor, 15); //move back 15 cm
                    dist -= 13;
                    turn_left(sensor, 80); //turn right
                    move_forward(sensor, 30); //move forward 15 cm

                    turn_right(sensor, 80); //turn left
                    move_forward(sensor, 60);
                    dist += 55;
                    turn_right(sensor, 80);
                    move_forward(sensor, 30);

                    turn_left(sensor, 80);

                }
                else if (sensor->bumpLeft)
                { // if the right bumper is hit
                    move_backward(sensor, 15); //move back 15 cm
                    dist -= 13;
                    turn_right(sensor, 80); //turn left
                    move_forward(sensor, 30); //move forward 25
                    turn_left(sensor, 80); //turn left
                    move_forward(sensor, 60);

                    dist += 55;
                    turn_left(sensor, 80); //turn right
                    move_forward(sensor, 30);

                    turn_right(sensor, 80);
                }
                else
                { //while the bumpers are not hit
                    move_forward(sensor, 1); //move forward 1 cm at a time until we reach dist
                    dist++; //increment distance traveled
                }
            }


}

int move_forward_cliff(oi_t *sensor, int millimeters) {

    int sum = 0;
    int cliffOrBump = 0;

     //move forward full speed

    while((sum < millimeters) && (cliffOrBump != 1))
    {
        oi_setWheels(300, 300);
        oi_update(sensor);

        if(sensor -> cliffRight==1) {
            oi_setWheels(0,0);
            move_backward(sensor, -15);
            oi_init(sensor);
            oi_setWheels(0,0);
            cliffOrBump = 1;
]
            return 3;
        }
        else if(sensor -> cliffLeft==1)    {
            oi_setWheels(0,0);
            move_backward(sensor, -15);
            oi_init(sensor);
            oi_setWheels(0,0);
            cliffOrBump = 1;

            return 0;
        }
        else if(sensor -> cliffFrontRight==1) {
            oi_setWheels(0,0);
            move_backward(sensor, -15);
            oi_init(sensor);
            oi_setWheels(0,0);
            cliffOrBump = 1;

            return 2;
        }
        else if((sensor -> cliffFrontLeft==1))    {
            oi_setWheels(0,0);
            move_backward(sensor, -15);
            oi_init(sensor);
            oi_setWheels(0,0);
            cliffOrBump = 1;

            return 1;
        }
        else if(sensor -> bumpRight == 1) {
            oi_setWheels(0,0);
            move_backward(sensor, -15);
            cliffOrBump = 1;
            oi_init(sensor);
            return 5;
        }
        else if(sensor -> bumpLeft == 1)    {
            oi_setWheels(0,0);
            move_backward(sensor, -15);
            cliffOrBump = 1;
            oi_init(sensor);
            return 6;
        }
        timer_waitMillis(200);
        sum += sensor -> distance;
    }

    oi_setWheels(0,0); //stop
    //oi_free(sensor);
    return 4;
}

void move_backward(oi_t *sensor, int centimeters){
    oi_setWheels(-300,-300); //move backward
    int sum = 0;
    while(sum > centimeters*10){ //while we are still moving
        oi_update(sensor);
        sum += sensor -> distance; //add change in distance
    }
    oi_setWheels(0,0); //stop moving
    return;
}

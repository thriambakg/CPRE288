/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Describtion: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>



int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the the LCD screen.  This also clears the screen. 

	oi_t *sensor_data = oi_alloc();
	oi_init(sensor_data); // should turn the iRobot Create's
	"Dirt Detect" LED to blue

	lcd_rotatingBanner("Microcontrollers are lots of fun!");


	return 0;
}

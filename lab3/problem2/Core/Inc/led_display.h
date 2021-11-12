/*
 * led_display.h
 *
 *  Created on: Sep 25, 2021
 *      Author: HH
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_
void display7SEG(int counter);
void time_clock(void);
void stopwatch(void);
void blinking_led(void);
void select_clock(void);

void display_clock(void);
void increases_time(void);
void auto_increases_time(void);

#endif /* INC_LED_DISPLAY_H_ */

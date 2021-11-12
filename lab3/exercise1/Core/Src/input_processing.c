/*
 * input_processing.c
 *
 *  Created on: Sep 22, 2021
 *      Author: HH
 */
#include "main.h"
#include "input_reading.h"
#include "led_display.h"

#define NUMBER_LED	 7
enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND,
	BUTTON_PRESSED_MORE_THAN_3_SECOND};
enum ButtonState buttonState = BUTTON_RELEASED;

enum ButtonState1{BUTTON_RELEASED_1, BUTTON_PRESSED_1, BUTTON_PRESSED_MORE_THAN_1_SECOND_1
	, BUTTON_PRESSED_MORE_THAN_3_SECOND_1};
enum ButtonState1 buttonState1 = BUTTON_RELEASED_1;

int c = 0;
int d = 0;

void fsm_for_input_processing(void){
	switch(buttonState){
	case BUTTON_RELEASED:
		if(get_button_value(0) == GPIO_PIN_SET){
			buttonState = BUTTON_PRESSED;
			c = 1;
		}
		break;
	case BUTTON_PRESSED:
		if(get_button_value(0) == GPIO_PIN_RESET){
			buttonState = BUTTON_PRESSED;
			if(c == 1){
				increases_led();
				c=0;
			}
		}
		else{
			if(get_flag_for_button_press_1s(0) == 1){
				buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;
			}
			c = 1;
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_1_SECOND:
		if(get_button_value(0) == GPIO_PIN_RESET){
			buttonState = BUTTON_RELEASED;
		}
		else if(get_flag_for_button_press_3s(0) == 1){
			buttonState = BUTTON_PRESSED_MORE_THAN_3_SECOND;
		}
		else{
			auto_increases_led();
		}
		break;
	case BUTTON_PRESSED_MORE_THAN_3_SECOND:
		if(get_button_value(0) == GPIO_PIN_RESET){
			buttonState = BUTTON_RELEASED;
		}else{
			auto_increases_led_3();
		}

	}

	if(get_button_value(0) == GPIO_PIN_RESET){
		switch(buttonState1){
			case BUTTON_RELEASED_1:
				if(get_button_value(1) == GPIO_PIN_SET){
					buttonState1 = BUTTON_PRESSED_1;
					d = 1;
				}
				break;
			case BUTTON_PRESSED_1:
				if(get_button_value(1) == GPIO_PIN_RESET){
					buttonState1 = BUTTON_PRESSED_1;
					if(d == 1){
						decreases_led();
						d=0;
					}
				}
				else{
					if(get_flag_for_button_press_1s(1) == 1){
						buttonState1 = BUTTON_PRESSED_MORE_THAN_1_SECOND_1;
					}
					d = 1;
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND_1:
				if(get_button_value(1) == GPIO_PIN_RESET){
					buttonState1 = BUTTON_RELEASED_1;
				}
				else if(get_flag_for_button_press_3s(1) == 1){
					buttonState1 = BUTTON_PRESSED_MORE_THAN_3_SECOND_1;
				}
				else{
					auto_decreases_led();
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_3_SECOND_1:
				if(get_button_value(1) == GPIO_PIN_RESET){
					buttonState1 = BUTTON_RELEASED_1;
				}
				else{
					auto_decreases_led_3();
				}
			}
	}
}


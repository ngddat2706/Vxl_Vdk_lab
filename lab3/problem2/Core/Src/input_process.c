/*
 * input_process.c
 *
 *  Created on: Sep 25, 2021
 *      Author: HH
 */
#include "main.h"
#include "led_display.h"
#include "input_reading.h"

int check_button_1 = 0;
int mode = 0;
void button_mode(void){
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET) check_button_1 = 1;
	 else{
		 if(check_button_1 == 1){
			 mode++;
			 if(mode == 6){
				 mode = 0;
			 }
			 check_button_1 =0;
		 }
	 }
}

int get_mode(void){
	return mode;
}

void set_mode(int mode_test){
	mode = mode_test;
}

int check_button_2 = 0;
void fsm_for_input_processing(void){
	if(get_flag_for_button_press_1s(0) == 1){
		auto_increases_time();
	}else{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_SET) check_button_2 = 1;
		else{
			if(check_button_2 == 1){
				increases_time();
				check_button_2 = 0;
			}
		}
	}
}




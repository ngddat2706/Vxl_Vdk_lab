/*
 * led_display.c
 *
 *  Created on: Sep 22, 2021
 *      Author: HH
 */
#include "main.h"
#define TIME_FOR_AUTO		25
#define TIME_FOR_AUTO_3		5

int time = 0;
int n = -1;

void clear_all(void){
	HAL_GPIO_WritePin(GPIOA, RED_LED_0_Pin|RED_LED_1_Pin|
			RED_LED_2_Pin|RED_LED_3_Pin|RED_LED_4_Pin|RED_LED_5_Pin|
			RED_LED_6_Pin|RED_LED_7_Pin, 0);
}

void display_led(int i){

	switch(i){
	case 0:
		HAL_GPIO_WritePin(GPIOA, RED_LED_0_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, RED_LED_1_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA, RED_LED_2_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, RED_LED_3_Pin, 1);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA, RED_LED_4_Pin, 1);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOA, RED_LED_5_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA, RED_LED_6_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOA, RED_LED_7_Pin, 1);
		break;
	default:
		clear_all();
		break;
	}
}

void increases_led(void ){
	clear_all();
	n++;
	if(n > 7) n = 0;
	display_led(n);
}

void decreases_led(void ){
	clear_all();
	n--;
	if(n < 0) n = 7;
	display_led(n);
}

void auto_increases_led(void ){
	time++;
	if(time >= TIME_FOR_AUTO){
		increases_led();
		time = 0;
	}
}
void auto_increases_led_3(void ){
	time++;
	if(time >= TIME_FOR_AUTO_3){
		increases_led();
		time = 0;
	}
}

void auto_decreases_led(void ){
	time++;
	if(time >= TIME_FOR_AUTO){
		decreases_led();
		time = 0;
	}
}

void auto_decreases_led_3(void ){
	time++;
	if(time >= TIME_FOR_AUTO_3){
		decreases_led();
		time = 0;
	}
}



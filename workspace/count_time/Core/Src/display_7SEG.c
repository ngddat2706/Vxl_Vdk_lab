/*
 * display.c
 *
 *  Created on: Oct 4, 2021
 *      Author: HH
 */

#include "main.h"
#define TIME_PER_SECOND		249	// time to increase a second
#define TIME_TRAN_LED	3

void display7SEG(int counter){
   	  switch(counter){
   	  case 0:
   		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, 1);
   		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14, 0);
   		  break;
   	  case 1:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_14, 0);
   	  	break;
   	  case 2:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9|GPIO_PIN_12, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  case 3:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11|GPIO_PIN_12, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  case 4:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  case 5:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8|GPIO_PIN_11, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  case 6:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  case 7:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_14, 0);
   	  	break;
   	  case 8:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  case 9:
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
   	  	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, 0);
   	  	break;
   	  default:
   		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, 1);
   		break;

   	  }
}

int number_7seg = 0;
int time = 0;
void time_clock(void){
	if(time >= TIME_PER_SECOND){
		number_7seg ++;
		if(number_7seg >= 255){
			number_7seg = 0;
		}
		time = 0;
	}
	time++;
}

int t = 0;
void display_clock(void){
	time_clock();
// Display 6 led 7 segment
	if(t>9 ){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		display7SEG(number_7seg/1000);
	}

	else if(t>6){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		display7SEG((number_7seg/100) %10);
	}

	else if(t > 3 ){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		display7SEG((number_7seg/10) %10);
	}

	else if(t > 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		display7SEG(number_7seg%10);
		}
	else{
		t = 12;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	}
	t--;
}


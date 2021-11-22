/*
 * led_display.c
 *
 *  Created on: Sep 25, 2021
 *      Author: HH
 */
#include "main.h"
#include "input_process.h"

#define TIME_AUTO_HOUR		100
#define TIME_PER_SECOND		249	// time to increase a second
#define TIME_STOPWATCH		24
int hour = 2;
int minutes = 58;
int second = 0;

int h_stopwatch = 0;
int m_stopwatch = 0;
int s_stopwatch = 0;


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

int run_stop = -1;
void increases_time(void){
	switch( get_mode() ){
		case 1:
			hour++;
			if(hour >= 24){
				hour = 0;
			}
			break;
		case 2:
			minutes++;
			if(minutes >= 60){
				minutes = 0;
			}
			break;
		case 3:
			second ++;
			if(second >= 60){
				second = 0;
			}
			break;
		case 4:
			run_stop = run_stop * (-1);
		break;
	}

}

int time_auto = 0;
void auto_increases_time(void){
	if(time_auto == TIME_AUTO_HOUR){
		increases_time();
		time_auto = 0;
	}
	time_auto++;
}

int time = 0;
int x = 1, y = 1, z = 1;
void time_clock(void){
	z =1;
	if(time >= TIME_PER_SECOND){
		second ++;
		if(second >= 60){
			second = 0;
			minutes++;
		}
		if(minutes >= 60){
			minutes = 0;
			hour++;
		}
		if(hour >= 24){
			hour=0;
		}
		time = 0;
	}
	time++;
}

int time_stopwatch = 0;
int check  =0;
void stopwatch(void){
if(run_stop == 1){
	if(time_stopwatch >= TIME_STOPWATCH){
		s_stopwatch ++;
		if(s_stopwatch >= 10){
			s_stopwatch = 0;
			m_stopwatch++;
		}
		if(m_stopwatch >= 60){
			m_stopwatch = 0;
			h_stopwatch++;
		}
		if(h_stopwatch >= 60){
			h_stopwatch=0;
		}
		time_stopwatch = 0;
	}
	time_stopwatch++;
	check = 1;
}
}

void blinking_led(void){
		switch (get_mode()){
			case 1:
				if(x == 0){
					x = 1;
				}else{
					x = 0;
				}
				y = 1;
				z = 1;
				break;
			case 2:
				x = 1;
				if(y == 0){
					y = 1;
				}else{
					y = 0;
				}
				z = 1;
				break;
			case 3:
				x = 1;
				y = 1;
				if(z == 0){
					z = 1;
				}else{
					z = 0;
				}
				break;
			default:
				z = 1;
				x = 1;
				y =1;
			break;
		}
}

int t = 18; // time to display 6 led 7 segment
int chuc, dvi;
int hour_run, minutes_run, second_run;
void select_clock(void){
	if(get_mode()== 0){
			time_clock();
			hour_run = hour;
			minutes_run = minutes;
			second_run = second;
			h_stopwatch = 0;
			m_stopwatch = 0;
			s_stopwatch = 0;
		}
		else if(get_mode() == 4){
			stopwatch();
			hour_run = h_stopwatch;
			minutes_run = m_stopwatch;
			second_run = s_stopwatch;
		}
		else if(get_mode() ==5){
			if(check == 1) set_mode(4);
			else set_mode(0);
			h_stopwatch = 0;
			m_stopwatch = 0;
			s_stopwatch = 0;
			check = 0;
			run_stop = -1;
		}
		else{
			hour_run = hour;
			minutes_run = minutes;
			second_run = second ;
		}
}


void display_clock(void){
	select_clock();
// Display 6 led 7 segment
	if(t > 15){
		chuc = hour_run/10;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
		display7SEG(chuc  * x + 10*(x-1));
	}

	else if(t > 12 ){
		dvi = hour_run%10;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
		display7SEG(dvi * x + 10*(x-1));
	}

	else if(t>9 ){
		chuc = minutes_run/10;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
		display7SEG(chuc * y + 10 * (y - 1));
	}

	else if(t>6){
		dvi = minutes_run%10;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
		display7SEG(dvi * y + 10 * (y - 1));
	}

	else if(t > 3 ){
		chuc = second_run/10;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		display7SEG(chuc * z + 10 * (z - 1));
	}

	else if(t > 0){
		dvi = second_run%10;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		display7SEG(dvi * z + 10 * (z - 1));
	}

	else{
		blinking_led();
		t = 18;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	}
	t--;
}



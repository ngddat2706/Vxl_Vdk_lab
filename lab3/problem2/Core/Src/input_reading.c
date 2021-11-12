/*
 * input_reading.c
 *
 *  Created on: Sep 22, 2021
 *      Author: HH
 */
#include "main.h"
#define NO_OF_BUTTONS		1
#define DURATION_FOR_AUTO_INCREASING	254

static GPIO_PinState	buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];


void button_reading(void){
	for(char i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];
		if(buttonBuffer[i] == GPIO_PIN_SET){
			if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
				counterForButtonPress1s[i]++;
			}
			else{
				flagForButtonPress1s[i] = 1;
				//to do
			}
		}
		else{
			counterForButtonPress1s[i] = 0;
			flagForButtonPress1s[i] = 0;
		}
	}
}

GPIO_PinState get_button_value(uint8_t index){
	if(index >= NO_OF_BUTTONS) return 0xff;
	return buttonBuffer[index];
}

unsigned char get_flag_for_button_press_1s(unsigned char index){
	if(index >= NO_OF_BUTTONS) return 0xff;
	return flagForButtonPress1s[index];
}



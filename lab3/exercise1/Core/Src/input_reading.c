/*
 * input_reading.c
 *
 *  Created on: Sep 22, 2021
 *      Author: HH
 */
#include "main.h"
#define NO_OF_BUTTONS		2
#define DURATION_FOR_AUTO_INCREASING	50
#define DURATION_FOR_AUTO				150

static GPIO_PinState	buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPress3s[NO_OF_BUTTONS];

GPIO_PinState get_status_pin(int n){
	switch(n){
	case 0:
		return HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
		break;
	case 1:
		return HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
		break;
	}
}

void button_reading(void){
	for(char i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = get_status_pin(i);
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];
		if(buttonBuffer[i] == GPIO_PIN_SET){
			if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
				counterForButtonPress1s[i]++;
			}
			else if(counterForButtonPress1s[i] < DURATION_FOR_AUTO){
				counterForButtonPress1s[i]++;
				flagForButtonPress1s[i] = 1;
			}
			else{
				flagForButtonPress3s[i] = 1;
				//to do
			}
		}
		else{
			counterForButtonPress1s[i] = 0;
			flagForButtonPress1s[i] = 0;
			flagForButtonPress3s[i] = 0;
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
unsigned char get_flag_for_button_press_3s(unsigned char index){
	if(index >= NO_OF_BUTTONS) return 0xff;
	return flagForButtonPress3s[index];
}



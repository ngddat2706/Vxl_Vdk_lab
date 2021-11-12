/*
 * input_reading.h
 *
 *  Created on: Sep 22, 2021
 *      Author: HH
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
//void get_status_pin(char n)
unsigned char get_button_value(unsigned char index);
void button_reading(void);
unsigned char get_flag_for_button_press_1s(unsigned char index);
unsigned char get_flag_for_button_press_3s(unsigned char index);


#endif /* INC_INPUT_READING_H_ */

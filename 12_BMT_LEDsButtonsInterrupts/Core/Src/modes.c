/*
 * modes.c
 *
 *  Created on: Feb 20, 2023
 *      Author: dark-on
 */
#include <string.h>


#include "main.h"
#include "stm32f4xx_it.h"


void emergency_mode(void){
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
}


void turn_off_leds(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
}


void run_mode(char mode[]){
	/*
	 * G - green; O - orange; R - red; B - blue; D. - delay
	 * 1 - turn on; 0 - turn off
	 *
	 * Example: "B1D.B0D." - turn on blue, delay, turn off blue, delay
	 */
	for (uint8_t i = 0; i < (uint8_t)strlen(mode); i += 2){
		if (is_mode_changed){
			is_mode_changed = 0;
			turn_off_leds();
			return;
		}

		switch (mode[i]){
		case 'D':
			HAL_Delay(speed);
			break;
		case 'B':
			if (mode[i+1] == '1'){
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
			}else{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
			}
			break;
		case 'R':
			if (mode[i+1] == '1'){
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
			}else{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
			}
			break;
		case 'O':
			if (mode[i+1] == '1'){
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
			}else{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
			}
			break;
		case 'G':
			if (mode[i+1] == '1'){
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
			}else{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
			}
			break;
		default:
			// if unknown symbol
			emergency_mode();
		}
	}
}

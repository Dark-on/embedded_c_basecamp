/*
 * modes.c
 *
 *  Created on: Feb 20, 2023
 *      Author: dark-on
 */
#include <string.h>


#include "main.h"
#include "stm32f4xx_it.h"


void run_mode_0(void){
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
}


void run_mode_1(void){
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);

	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
}

void run_mode_2(void){
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);

	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
}

void run_mode_3(void){
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
	HAL_Delay(speed);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
}

void run_default_mode(void){
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
}

void turn_off_leds(void){
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
}

//
//void run_mode(char mode[]){
//	//"B1D.B0D."
//	for (uint8_t i = 0; i < (uint8_t)strlen(mode); i += 2){
//		if (is_mode_changed){
//			is_mode_changed = 0;
//			turn_off_leds();
//			return;
//		}
//		if (mode[i] == 'B'){
//			if (mode[i+1] == '1'){
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 1);
//			}else{
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, 0);
//			}
//			continue;
//		}
//		if (mode[i] == 'R'){
//			if (mode[i+1] == '1'){
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 1);
//			}else{
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, 0);
//			}
//			continue;
//		}
//		if (mode[i] == 'O'){
//			if (mode[i+1] == '1'){
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
//			}else{
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 0);
//			}
//			continue;
//		}
//		if (mode[i] == 'G'){
//			if (mode[i+1] == '1'){
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 1);
//			}else{
//				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, 0);
//			}
//			continue;
//		}
//		if (mode[i] == 'D'){
//			HAL_Delay(speed);
//			continue;
//		}
//	}
//}

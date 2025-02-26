/*
 * voltage_level.c
 *
 *  Created on: Jan 5, 2025
 *      Author: Dmitry
 */
#include "main.h"
//#include "button.c"

uint32_t time = 0;
uint8_t flag_start_GetTick = 1;
uint8_t flag_low_level = 0;
uint8_t flag_high_level = 0;

//time = HAL_GetTick();

/*void set_voltage_level (uint32_t time_low_level, uint32_t time_high_level){

	if( (HAL_GetTick() - time) > time_low_level ){

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_Delay(time_high_level);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	    time = HAL_GetTick();
	}
}*/

void set_voltage_level (uint32_t time_low_level, uint32_t time_high_level){

	if(flag_start_GetTick){
		flag_start_GetTick = 0;
		flag_low_level = 1;
		time = HAL_GetTick();
	}

	if( (HAL_GetTick() - time) > time_low_level && flag_low_level ){

		flag_low_level = 0;
		flag_high_level = 1;
	    time = HAL_GetTick();
	    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // set high level pin
	}

	if( (HAL_GetTick() - time) > time_high_level && flag_high_level ){

	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // set low level pin
	  flag_high_level = 0;
	  flag_start_GetTick = 1;
	  time = HAL_GetTick();
	}
}

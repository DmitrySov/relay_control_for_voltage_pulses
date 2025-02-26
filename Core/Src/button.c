/*
 * button.c
 *
 *  Created on: Jan 5, 2025
 *      Author: Dmitry
 */
#include "main.h"

uint8_t flag_key1_press = 1;
uint8_t flag_key1_wait = 1;
uint32_t time_key1_press = 0;

static volatile uint8_t number = 0;

/*
 * Чтение кнопки, с учетом дребезга
 */
void read_button(void){

	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET && flag_key1_press) // подставить свой пин
	{
			flag_key1_press = 0;
			flag_key1_wait = 0;
			time_key1_press = HAL_GetTick();
	}

	if(!flag_key1_wait && (HAL_GetTick() - time_key1_press) > 100)
	{
			if( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0 == GPIO_PIN_SET) )
			{
					//HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
					// действие на нажатие

					if(number <= 3){
						number++;
					}
					else{number=0;}

					flag_key1_wait = 1;
			}
			else
			{
					flag_key1_wait = 1;
					flag_key1_press = 1;
			}
	}

	if(!flag_key1_press && (HAL_GetTick() - time_key1_press) > 300)
	{
			flag_key1_press = 1;
	}

}
/*
 * Функция переключения действия при нажатия кнопки.
 * number - счетик действия, 0 и четное значение для определения
 * на какое действие переключить при следующем нажатии кнопки, нечетное значение переход на нужное действие
 */
void click_action (uint32_t low_level1, uint32_t high_level1, uint32_t low_level2, uint32_t high_level2)
{
	read_button(); // чтение кнопки
	switch(number){
	    case 0:	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12, GPIO_PIN_RESET);	// если кнопка не нажата
	    	break;
		case 1: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);	// если кнопка нажата в первый раз
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
				number = 2;
				break;
		case 2: set_voltage_level (low_level1, high_level1);
				break;
		case 3: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET); // если кнопка нажата во второй раз
				//set_voltage_level (8000, 2000);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		        number = 4; // переход на case 4
				break;
		case 4: set_voltage_level (low_level2, high_level2);
				break;
  }
}

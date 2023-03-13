/*
 * i2c_lib.h
 *
 *  Created on: Mar 10, 2023
 *      Author: dark-on
 */

#ifndef INC_I2C_LIB_H_
#define INC_I2C_LIB_H_

typedef enum{
	LED0,
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED7,
	LED8,
	LED9,
	LED10,
	LED11,
	LED12,
	LED13,
	LED14,
	LED15
} LEDn;


typedef enum{
	OFF,
	ON
}LED_State;

void I2C_enable_outputs(void);
void I2C_disable_outputs(void);
void I2C_toggle_outputs(void);

void I2C_enable_sleep_mode(I2C_HandleTypeDef *hi2c);
void I2C_disable_sleep_mode(I2C_HandleTypeDef *hi2c);

void I2C_set_duty(I2C_HandleTypeDef *hi2c, LEDn led_number, uint8_t duty);
void I2C_set_duty_for_all(I2C_HandleTypeDef *hi2c, uint8_t duty);

void I2C_set_pwm_frequency(I2C_HandleTypeDef *hi2c, uint16_t frequency);

void I2C_write_led_on(I2C_HandleTypeDef *hi2c, LEDn led_number, LED_State LED_State);
void I2C_write_led_off(I2C_HandleTypeDef *hi2c, LEDn led_number, LED_State LED_State);
void I2C_write_led_on_for_all(I2C_HandleTypeDef *hi2c, LED_State LED_State);
void I2C_write_led_off_for_all(I2C_HandleTypeDef *hi2c, LED_State LED_State);

#endif /* INC_I2C_LIB_H_ */

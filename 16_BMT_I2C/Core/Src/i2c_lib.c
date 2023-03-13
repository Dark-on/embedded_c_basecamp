#include <stdint.h>
#include "stm32f4xx_hal.h"

#include "i2c_lib.h"

#define LED0_ON_L     0x06
#define LED0_ON_H     0x07

#define LED0_OFF_H    0x09

#define ALL_LED_ON_L  0xFA
#define ALL_LED_ON_H  0xFB

#define ALL_LED_OFF_H 0xFD
#define PRE_SCALE     0xFE


uint8_t devId = 0x80;
uint8_t txBuffer[8];


/**
  * @brief  Enables all the LED outputs at the same time.
  *
  * @note   When this function is called all the LED outputs are enabled and follow the output state
  *         defined in the LEDn_ON and LEDn_OFF registers
  *         with the polarity defined by INVRT bit (MODE2 register).
  *
  * @retval None
  */
void I2C_enable_outputs(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}


/**
  * @brief  Disables all the LED outputs at the same time.
  *
  * @note   When this function is called all the LED outputs are programmed to the value
  *         that is defined by OUTNE[1:0] in the MODE2 register.
  *
  * @retval None
  */
void I2C_disable_outputs(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
}


/**
  * @brief  Toggle all the LED outputs at the same time.
  *
  * @retval None
  */
void I2C_toggle_outputs(void){
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
}


/**
  * @brief  Enables sleep mode.
  *
  * @note   When the oscillator is off (Sleep mode) the LEDn outputs cannot be turned on,
  *         off or dimmed/blinked.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  *
  * @retval None
  */
void I2C_enable_sleep_mode(I2C_HandleTypeDef *hi2c){
	txBuffer[0] = 0x00;
	txBuffer[1] = 0x11; // to sleep
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);
}


/**
  * @brief  Disables sleep mode.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  *
  * @retval None
  */
void I2C_disable_sleep_mode(I2C_HandleTypeDef *hi2c){
	txBuffer[0] = 0x00;
	txBuffer[1] = 0x01; // to normal mode
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);
}


/**
  * @brief  Sets PWM duty cycle for the selected LED.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  led_number specifies the number of LED to be set duty
  *                This parameter can be one of LEDn where n can be (0..15).
  * @param  duty Duty cycle in percent
  *
  * @retval None
  */
void I2C_set_duty(I2C_HandleTypeDef *hi2c, LEDn led_number, uint8_t duty){
	txBuffer[0] = LED0_ON_L + led_number * 4;
	txBuffer[1] = 0x00;                       //LEDn_ON_L
	txBuffer[2] = 0x00;                       //LEDn_ON_H
	txBuffer[3] = (4096 * duty / 100) & 0xFF; //LEDn_OFF_L
	txBuffer[4] = (4096 * duty / 100) >> 8;   //LEDn_OFF_H
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 5, 1000);
}


/**
  * @brief  Sets PWM duty cycle for all LEDs.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  duty Duty cycle in percent
  *
  * @retval None
  */
void I2C_set_duty_for_all(I2C_HandleTypeDef *hi2c, uint8_t duty){
	txBuffer[0] = ALL_LED_ON_L;
	txBuffer[1] = 0x00;                       //ALL_LED_ON_L
	txBuffer[2] = 0x00;                       //ALL_LED_ON_H
	txBuffer[3] = (4096 * duty / 100) & 0xFF; //ALL_LED_OFF_L
	txBuffer[4] = (4096 * duty / 100) >> 8;   //ALL_LED_OFF_H
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 5, 1000);
}


/**
  * @brief  Sets PWM frequency.
  *
  * @note All outputs are set to the same PWM frequency.
  *       The frequency in the PCA9685 is adjustable from about 24 Hz to 1526 Hz
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  frequency
  *
  * @retval None
  */
void I2C_set_pwm_frequency(I2C_HandleTypeDef *hi2c, uint16_t frequency){
	I2C_enable_sleep_mode(hi2c);

	txBuffer[0] = PRE_SCALE;
	txBuffer[1] = 25000000 / 4096 / frequency - 1;
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);

	I2C_disable_sleep_mode(hi2c);
}


/**
  * @brief  Sets/resets the LEDn_ON_H output control bit 4.
  *
  * @note If LEDn_ON_H[4] and LEDn_OFF_H[4] are set at the same time,
  *       the LEDn_OFF_H[4] function takes precedence.
  * @note The turning ON of the LED is delayed by the amount in the LEDn_ON registers.
  *       LEDn_OFF[11:0] are ignored.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  led_number specifies the number of LED
  *                This parameter can be one of LEDn where n can be (0..15).
  * @param  LED_State specifies the value to be set.
  *            This parameter can be one of the LED_State enum values:
  *                @arg ON: the output is always ON.
  *                @arg OFF: the LEDn_ON and LEDn_OFF registers
  *                    are used according to their normal definition.
  * @retval None
  */
void I2C_write_led_on(I2C_HandleTypeDef *hi2c, LEDn led_number, LED_State LED_State){
	txBuffer[0] = LED0_ON_H + led_number * 4;
	txBuffer[1] = LED_State << 4;
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);
}


/**
  * @brief  Sets/resets the LEDn_OFF_H output control bit 4.
  *
  * @note If LEDn_ON_H[4] and LEDn_OFF_H[4] are set at the same time,
  *       the LEDn_OFF_H[4] function takes precedence.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  led_number specifies the number of LED
  *                This parameter can be one of LEDn where n can be (0..15).
  * @param  LED_State specifies the value to be set.
  *            This parameter can be one of the LED_State enum values:
  *                @arg ON: the output is always OFF. The values
  *                    in the LEDn_ON registers are ignored.
  *                @arg OFF: the LEDn_ON and LEDn_OFF registers
  *                    are used according to their normal definition.
  * @retval None
  */
void I2C_write_led_off(I2C_HandleTypeDef *hi2c, LEDn led_number, LED_State LED_State){
	txBuffer[0] = LED0_OFF_H + led_number * 4;
	txBuffer[1] = LED_State << 4;
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);
}

/**
  * @brief  Sets/resets the ALL_LED_ON_H output control bit 4.
  *
  * @note If ALL_LED_ON_H[4] and ALL_LED_OFF_H[4] are set at the same time,
  *       the ALL_LED_OFF_H[4] function takes precedence.
  * @note The turning ON of the LED is delayed by the amount in the ALL_LED_ON registers.
  *       ALL_LED_OFF[11:0] are ignored.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  LED_State specifies the value to be set.
  *            This parameter can be one of the LED_State enum values:
  *                @arg ON: the outputs are always ON.
  *                @arg OFF: the ALL_LED_ON and ALL_LED_OFF registers
  *                    are used according to their normal definition.
  * @retval None
  */
void I2C_write_led_on_for_all(I2C_HandleTypeDef *hi2c, LED_State LED_State){
	txBuffer[0] = ALL_LED_ON_H;
	txBuffer[1] = LED_State << 4;
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);
}


/**
  * @brief  Sets/resets the ALL_LED_OFF_H output control bit 4.
  *
  * @note If ALL_LED_ON_H[4] and ALL_LED_OFF_H[4] are set at the same time,
  *       the ALL_LED_OFF_H[4] function takes precedence.
  *
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *            the configuration information for the specified I2C.
  * @param  LED_State specifies the value to be set.
  *            This parameter can be one of the LED_State enum values:
  *                @arg ON: the output is always OFF. The values
  *                    in the ALL_LED_ON registers are ignored.
  *                @arg OFF: the ALL_LED_ON and ALL_LED_OFF registers
  *                    are used according to their normal definition.
  * @retval None
  */
void I2C_write_led_off_for_all(I2C_HandleTypeDef *hi2c, LED_State LED_State){
	txBuffer[0] = ALL_LED_OFF_H;
	txBuffer[1] = LED_State << 4;
	HAL_I2C_Master_Transmit(hi2c, devId, (uint8_t *)&txBuffer, 2, 1000);
}


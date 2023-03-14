/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c_lib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	NOT_EQUAL,
	EQUAL,
}compare_result_t;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint8_t rcvBuf[5];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
compare_result_t compare_strings(uint8_t *str1, uint8_t *str2, uint8_t len);
uint8_t char_to_digit(uint8_t character);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_Delay(10);

  I2C_enable_outputs();
  I2C_disable_sleep_mode(&hi2c1);
  I2C_set_duty_for_all(&hi2c1, 60);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  HAL_UART_Receive_IT(&huart3, rcvBuf, 5);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 50000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/**
  * @brief  Compare first "len" symbols of two strings.
  *
  * @note   len should be less then or equal to length of shortest string
  *
  * @param  str1 One of compared strings
  * @param  str2 One of compared strings
  * @param  len Amount of symbols to be compared
  *
  * @retval Is equal symbols or not
  */
compare_result_t compare_strings(uint8_t *str1, uint8_t *str2, uint8_t len){
	for (uint8_t i = 0; i < len; i++){
		if(str1[i] != str2[i]){
			return NOT_EQUAL;
		}
	}
	return EQUAL;
}


/**
  * @brief  Convert symbol code to corresponding digit.
  *
  * @note   if function got not symbol code of digit than return 0xFF
  *
  * @param  character Symbol code to be converted
  *
  * @retval Digit corresponding to the character
  */
uint8_t char_to_digit(uint8_t character){
	if('0' <= character || character <= '9'){
		return character - '0';
	}
	return 0xFF;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  switch (rcvBuf[0]){

  uint8_t digit1, digit2, digit3, digit4;

  case 'O':
	  /*
      enable/disable outputs
      command examples:
	  OutEn - enable outputs
	  OutDs - disable outputs
	  OutTg - toggle outputs
	  */
	  if (compare_strings(rcvBuf, (uint8_t *)"OutEn", 5)){
		  I2C_enable_outputs();
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Outputs enabled\n\r", 17, 10);
		  break;
	  }else if(compare_strings(rcvBuf, (uint8_t *)"OutDs", 5)){
		  I2C_disable_outputs();
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Outputs disabled\n\r", 18, 10);
		  break;
	  }else if(compare_strings(rcvBuf, (uint8_t *)"OutTg", 5)){
		  I2C_toggle_outputs();
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Outputs toggled\n\r", 17, 10);
		  break;
	  /* write led_on/of
	  command examples:
	  ON-06 - led_on for LED6
	  ONn06 - disable led_on for LED6
	  OFF12 - led_off for LED12
	  OFn12 - disable led_off for LED12
	  */
	  }else if(compare_strings(rcvBuf, (uint8_t *)"ONn", 3)){
		  digit2 = char_to_digit(rcvBuf[3]);
		  digit1 = char_to_digit(rcvBuf[4]);
		  if(digit1 < 10 && digit2 < 10){
			  uint8_t led = digit2 * 10 + digit1;
			  I2C_write_led_on(&hi2c1, led, OFF);
			  HAL_UART_Transmit(&huart3, (uint8_t *)"LED is not ON\n\r", 15, 10);
			  break;
		  }
	  }else if(compare_strings(rcvBuf, (uint8_t *)"ON-", 3)){
		  digit2 = char_to_digit(rcvBuf[3]);
		  digit1 = char_to_digit(rcvBuf[4]);
		  if(digit1 < 10 && digit2 < 10){
			  uint8_t led = digit2 * 10 + digit1;
			  I2C_write_led_on(&hi2c1, led, ON);
			  HAL_UART_Transmit(&huart3, (uint8_t *)"LED is ON\n\r", 11, 10);
			  break;
		  }
	  }else if(compare_strings(rcvBuf, (uint8_t *)"OFF", 3)){
		  digit2 = char_to_digit(rcvBuf[3]);
		  digit1 = char_to_digit(rcvBuf[4]);
		  if(digit1 < 10 && digit2 < 10){
			  uint8_t led = digit2 * 10 + digit1;
			  I2C_write_led_off(&hi2c1, led, ON);
			  HAL_UART_Transmit(&huart3, (uint8_t *)"LED is OFF\n\r", 12, 10);
			  break;
		  }
	  }else if(compare_strings(rcvBuf, (uint8_t *)"OFn", 3)){
		  digit2 = char_to_digit(rcvBuf[3]);
		  digit1 = char_to_digit(rcvBuf[4]);
		  if(digit1 < 10 && digit2 < 10){
			  uint8_t led = digit2 * 10 + digit1;
		  	  I2C_write_led_off(&hi2c1, led, OFF);
		  	  HAL_UART_Transmit(&huart3, (uint8_t *)"LED is not OFF\n\r", 16, 10);
		  	  break;
		  }
	  }
	  HAL_UART_Transmit(&huart3, rcvBuf, 5, 10);
	  HAL_UART_Transmit(&huart3, (uint8_t *)" - UnexpCmd\n\r", 13, 10);
	  break;
  case 'A':
	  /* write all led_on/of
	  command examples:
	  AllON - led_on for all
	  AlnON - disable led_on for all
	  AlOFF - led_off for all
	  AnOFF - disable led_off for all
	  */

	  if(compare_strings(rcvBuf, (uint8_t *)"AllON", 5)){
		  I2C_write_led_on_for_all(&hi2c1, ON);
		  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is ON\n\r", 12, 10);
		  break;
	  }else if(compare_strings(rcvBuf, (uint8_t *)"AlnON", 5)){
		  I2C_write_led_on_for_all(&hi2c1, OFF);
		  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is not ON\n\r", 16, 10);
		  break;
	  }else if(compare_strings(rcvBuf, (uint8_t *)"AlOFF", 5)){
		  I2C_write_led_off_for_all(&hi2c1, ON);
		  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is OFF\n\r", 13, 10);
		  break;
	  }else if(compare_strings(rcvBuf, (uint8_t *)"AnOFF", 5)){
		  I2C_write_led_off_for_all(&hi2c1, OFF);
		  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is not OFF\n\r", 17, 10);
		  break;
	  }else{
		  HAL_UART_Transmit(&huart3, rcvBuf, 5, 10);
		  HAL_UART_Transmit(&huart3, (uint8_t *)(" - UnexpCmd\n\r"), 13, 10);
		  break;
	  }
  case 'S':
	  /* enable/disable sleep mode
	  command examples:
	  SlmEn - enable sleep mode
	  SlmDs - disable sleep mode
	   */
	  if(compare_strings(rcvBuf, (uint8_t *)"SlmEn", 5)){
		  I2C_enable_sleep_mode(&hi2c1);
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Sleep mode enabled\n\r", 20, 10);
		  break;
	  } else if(compare_strings(rcvBuf, (uint8_t *)"SlmDs", 5)){
		  I2C_disable_sleep_mode(&hi2c1);
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Sleep mode disabled\n\r", 21, 10);
		  break;
	  }else{
		  HAL_UART_Transmit(&huart3, rcvBuf, 5, 10);
		  HAL_UART_Transmit(&huart3, (uint8_t *)(" - UnexpCmd\n\r"), 13, 10);
		  break;
	  }
  case 'D':
	  /*
	  set duty
	  command examples:
	  D0680 - set duty 80% for LED6
	  DAl95 - set duty 95% for all LEDs
	   */
	  if (compare_strings(rcvBuf, (uint8_t *)"DAl", 3)){
		  uint8_t digit2 = char_to_digit(rcvBuf[3]);
		  uint8_t digit1 = char_to_digit(rcvBuf[4]);
		  if(digit2 < 10 && digit1 < 10){
			  uint8_t duty = digit2 * 10 + digit1;
		  	  I2C_set_duty_for_all(&hi2c1, duty);
		  	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set for all\n\r", 21, 10);
		  	  break;
		  }
	  }else{
		  digit4 = char_to_digit(rcvBuf[1]);
		  digit3 = char_to_digit(rcvBuf[2]);
		  digit2 = char_to_digit(rcvBuf[3]);
		  digit1 = char_to_digit(rcvBuf[4]);
		  if(digit1 < 10 && digit2 < 10 && digit3 < 10 && digit4 < 10){
			  uint8_t led  = digit4 * 10 + digit3;
			  if (led <= 15){
				  uint8_t duty = digit2 * 10 + digit1;
				  I2C_set_duty(&hi2c1, led, duty);
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set\n\r", 13, 10);
				  break;
			  }else{
				  HAL_UART_Transmit(&huart3, (uint8_t *)"LED number is out of range\n\r", 28, 10);
				  break;
			  }
		  }
	  }

	  HAL_UART_Transmit(&huart3, rcvBuf, 5, 10);
	  HAL_UART_Transmit(&huart3, (uint8_t *)(" - UnexpCmd\n\r"), 13, 10);
	  break;
  case 'F':
	  /* set frequency
	  command examples:
	  F1000 - set frequency 1000Hz
	  F0050 - set frequency 50Hz
	  */
	  digit4 = char_to_digit(rcvBuf[1]);
	  digit3 = char_to_digit(rcvBuf[2]);
	  digit2 = char_to_digit(rcvBuf[3]);
	  digit1 = char_to_digit(rcvBuf[4]);
	  if(digit1 < 10 && digit2 < 10 && digit3 < 10 && digit4 < 10){
		  uint16_t frequency = digit4 * 1000 + digit3 * 100 + digit2 * 10 + digit1;
		  if (24 <= frequency && frequency <= 1526){
			  I2C_set_pwm_frequency(&hi2c1, frequency);
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is set\n\r", 18, 10);
			  break;
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is out of range\n\r", 27, 10);
			  break;
		  }
	  }
	  //no break
  default:
	  HAL_UART_Transmit(&huart3, rcvBuf, 5, 10);
	  HAL_UART_Transmit(&huart3, (uint8_t *)(" - UnexpCmd\n\r"), 13, 10);
	  break;
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

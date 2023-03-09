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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void temp_to_str(int16_t const temperature, uint8_t *str);
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
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  HAL_TIM_Base_Start_IT(&htim2);
  uint8_t rcvBuf[1];

  while (1)
  {
	  if (HAL_UART_Receive(&huart3, rcvBuf, 1, 10) == HAL_OK){
		  switch (rcvBuf[0]){
		  case 'b': //blue LED
			  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
			  if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15) == GPIO_PIN_SET){
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Blue ON\n\r", 9, 10);
			  }else{
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Blue OFF\n\r", 10, 10);
			  }
			  break;
		  case 'g': //green LED
			  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
			  if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == GPIO_PIN_SET){
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Green ON\n\r", 10, 10);
			  }else{
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Green OFF\n\r", 11, 10);
			  }
			  break;
		  case 'o': //orange LED
			  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
			  if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13) == GPIO_PIN_SET){
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Orange ON\n\r", 11, 10);
			  }else{
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Orange OFF\n\r", 12, 10);
			  }
			  break;
		  case 'r': //red LED
			  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
			  if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14) == GPIO_PIN_SET){
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Red ON\n\r", 8, 10);
			  }else{
				  HAL_UART_Transmit(&huart3, (uint8_t *)"Red OFF\n\r", 9, 10);
			  }
			  break;
		  default:
			  HAL_UART_Transmit(&huart3, (uint8_t *)"UnexpCmd\n\r", 10, 10);
			  break;
		  }

	  }
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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 64000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1250;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC8 PC9 PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/**
  * @brief  Convert temperature number into char[] and store in str.
  *
  * @note   size of str should be more than or equal to len of text message + 6
  *
  * @param  temperature - temperature in dC to convert
  * @param  str - pointer to str buffer
  *
  * @retval None
  */
void temp_to_str(int16_t const temperature, uint8_t *str){
	uint8_t const text[] = "Temperature: ";
	uint8_t const text_len = sizeof(text) - 1;

	for (uint8_t i = 0; i < text_len; i++){
		str[i] = text[i];
	}

	/* fill array with the temperature
	 * for example: 432.1
	 */
	uint8_t minus_pos = text_len;

	if (temperature / 1000){                         //4
		str[text_len + 1] = '0' + temperature / 1000;
	}else{
		str[text_len + 1] = ' ';
		minus_pos++;
	}

	if (temperature / 100 % 10){                     //3
		str[text_len + 2] = '0' + temperature / 100 % 10;
	}else{
		str[text_len + 2] = ' ';
		minus_pos++;
	}

	str[minus_pos] = (temperature < 0) ? '-' : ' ';

	str[text_len + 3] = '0' + temperature / 10 % 10; //2
	str[text_len + 4] = '.';                         //.
	str[text_len + 5] = '0' + temperature % 10;      //1
	str[text_len + 6] = '\n';
	str[text_len + 7] = '\r';
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin){
	case GPIO_PIN_6: //SWT4 - red LED
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14) == GPIO_PIN_SET){
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Red ON\n\r", 8, 10);
		}else{
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Red OFF\n\r", 9, 10);
		}
		break;
	case GPIO_PIN_8: //SWT5 - green LED
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == GPIO_PIN_SET){
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Green ON\n\r", 10, 10);
		}else{
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Green OFF\n\r", 11, 10);
		}
		break;
	case GPIO_PIN_9: //SWT3 - orange LED
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13) == GPIO_PIN_SET){
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Orange ON\n\r", 11, 10);
		}else{
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Orange OFF\n\r", 12, 10);
		}
		break;
	case GPIO_PIN_11: //SWT1 - blue LED
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
		if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15) == GPIO_PIN_SET){
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Blue ON\n\r", 9, 10);
		}else{
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Blue OFF\n\r", 10, 10);
		}
		break;
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	static uint32_t adcValue = 0;
	HAL_ADC_Start(&hadc1);
	while(HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK);
	adcValue = HAL_ADC_GetValue(&hadc1);

	/* find the temperature in dC (max accuracy -0.1С)
	 * 101C - temperature at 0V (min voltage)
	 * 3000mV - max voltage
	 * 4095 - max adcValue
	 * 20mV - per 1C, 2mV per 1dC
	 *
	 * using dC instead of C to make calculations without float
	 */
	static int16_t temperature = 0;
	temperature = 1010 - (adcValue * 3000 / 4095) / 2;

	/* uncomment to compare with more accurate value */
//  static float temperature_float = 0;
//	temperature_float = 101 - ((float)adcValue * 3000 / 4095) / 20;

	//convert temperature number to string and transmit via UART
	uint8_t temp_str[25] = {0};
	temp_to_str(temperature, temp_str);

	HAL_UART_Transmit(&huart3, temp_str, 25, 10);
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

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
uint8_t rcvBuf[2];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

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
	  HAL_UART_Receive_IT(&huart3, rcvBuf, 1);
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  switch (rcvBuf[0]){
  // enable/disable outputs
  case 'q':
	  I2C_enable_outputs();
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Outputs enabled\n\r", 17, 10);
	  break;
  case 'w':
	  I2C_disable_outputs();
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Outputs disabled\n\r", 18, 10);
	  break;
  case 'e':
	  I2C_toggle_outputs();
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Outputs toggled\n\r", 17, 10);
	  break;
  // enable/disable sleep mode
  case 't':
	  I2C_enable_sleep_mode(&hi2c1);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Sleep mode enabled\n\r", 20, 10);
	  break;
  case 'y':
	  I2C_disable_sleep_mode(&hi2c1);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Sleep mode disabled\n\r", 21, 10);
	  break;
  // set duty
  case 'a':
	  I2C_set_duty(&hi2c1, LED0, 10);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set\n\r", 13, 10);
	  break;
  case 's':
	  I2C_set_duty(&hi2c1, LED0, 25);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set\n\r", 13, 10);
	  break;
  case 'd':
	  I2C_set_duty(&hi2c1, LED0, 50);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set\n\r", 13, 10);
	  break;
  case 'f':
	  I2C_set_duty(&hi2c1, LED0, 75);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set\n\r", 13, 10);
	  break;
  //set duty for all
  case 'A':
	  I2C_set_duty_for_all(&hi2c1, 10);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set for all\n\r", 21, 10);
	  break;
  case 'S':
	  I2C_set_duty_for_all(&hi2c1, 25);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set for all\n\r", 21, 10);
	  break;
  case 'D':
	  I2C_set_duty_for_all(&hi2c1, 50);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set for all\n\r", 21, 10);
	  break;
  case 'F':
	  I2C_set_duty_for_all(&hi2c1, 75);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Duty is set for all\n\r", 21, 10);
	  break;
  // set frequency
  case 'h':
	  I2C_set_pwm_frequency(&hi2c1, 24);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is set\n\r", 18, 10);
	  break;
  case 'j':
	  I2C_set_pwm_frequency(&hi2c1, 500);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is set\n\r", 18, 10);
	  break;
  case 'k':
	  I2C_set_pwm_frequency(&hi2c1, 1000);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is set\n\r", 18, 10);
	  break;
  case 'l':
	  I2C_set_pwm_frequency(&hi2c1, 1526);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"Frequency is set\n\r", 18, 10);
	  break;
  // write led_on
  case 'x':
	  I2C_write_led_on(&hi2c1, LED0, ON);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LED0 is ON\n\r", 12, 10);
	  break;
  case 'X':
	  I2C_write_led_on_for_all(&hi2c1, ON);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is ON\n\r", 12, 10);
	  break;
  case 'c':
	  I2C_write_led_on(&hi2c1, LED0, OFF);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LED0 is not ON\n\r", 16, 10);
	  break;
  case 'C':
	  I2C_write_led_on_for_all(&hi2c1, OFF);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is not ON\n\r", 16, 10);
	  break;
  // write led_off
  case 'b':
	  I2C_write_led_off(&hi2c1, LED0, ON);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LED0 is OFF\n\r", 13, 10);
	  break;
  case 'B':
	  I2C_write_led_off_for_all(&hi2c1, ON);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is OFF\n\r", 13, 10);
	  break;
  case 'n':
	  I2C_write_led_off(&hi2c1, LED0, OFF);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LED0 is not OFF\n\r", 17, 10);
	  break;
  case 'N':
	  I2C_write_led_off_for_all(&hi2c1, OFF);
	  HAL_UART_Transmit(&huart3, (uint8_t *)"LEDs is not OFF\n\r", 17, 10);
	  break;

  default:
	  HAL_UART_Transmit(&huart3, (uint8_t *)"UnexpCmd\n\r", 10, 10);
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

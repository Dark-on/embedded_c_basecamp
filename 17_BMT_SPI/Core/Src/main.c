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
#include "spi_flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define LINE_NUMBER 22
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
const char * text[LINE_NUMBER] = {
		"From: Svitlana Drozd, drozd.svit@gmail.com\n",
		"Mentor: Bogdan Liulko, bogdan.liulko@globallogic.com\n",
		"Date: 19.03.2023\n",
		"TIME CAPSULE\n",

		"You can't buy this fineness\n",
		"Let me see the heat get to you\n",
		"Let me watch the dressing start to peel\n",
		"It's a kindness, highness\n",
		"Crumbs enough for everyone\n",
		"Old and young are welcome to the meal\n",
		"Honey, I'm makin' sure the table's made\n",
		"We can celebrate the good that we've done\n",
		"I won't lie if there's somethin' still to take\n",
		"There is ground to break, whatever's still to come\n",

		"Get some\n",
		"Pull up the ladder when the flood comes\n",
		"Throw enough rope until the legs have swung\n",
		"Seven new ways that you can eat your young\n",
		"Come and get some\n",
		"Skinnin' the children for a war drum\n",
		"Puttin' food on the table sellin' bombs and guns\n",
		"It's quicker and easier to eat your young\n"
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
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
  MX_SPI1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint8_t rcvBuf[1];

  while (1)
  {
	  if (HAL_UART_Receive(&huart3, rcvBuf, 1, 10) == HAL_OK){
	  switch (rcvBuf[0]){
	  case 'w': //Write
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Start writing\n\r", 15, 10);
		  if (SPI_Write(text, LINE_NUMBER) == SPI_OK){
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Writing is successful\n\r", 23, 10);
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Writing is not successful\n\r", 27, 10);
		  }
		  break;
	  case 'r': //Read
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Start reading\n\r", 15, 10);
		  if (SPI_Read(LINE_NUMBER) == SPI_OK){
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Reading is successful\n\r", 23, 10);
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Reading is not successful\n\r", 27, 10);
		  }
		  break;
	  case 's': //Erase 0th sector
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Start erasing sector\n\r", 22, 10);
		  if (SPI_Erase_sector(0) == SPI_OK){
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is successful\n\r", 23, 10);
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is not successful\n\r", 27, 10);
		  }
		  break;
	  case 'd': //Erase 1th 32KB block
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Start erasing 32KB block\n\r", 26, 10);
		  if (SPI_Erase_block(BLOCK_32KB, 1) == SPI_OK){
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is successful\n\r", 23, 10);
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is not successful\n\r", 27, 10);
		  }

		  break;
	  case 'f': //Erase 2th 64KB block
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Start erasing 64KB block\n\r", 26, 10);
		  if (SPI_Erase_block(BLOCK_64KB, 2) == SPI_OK){
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is successful\n\r", 23, 10);
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is not successful\n\r", 27, 10);
		  }
		  break;
	  case 'e': //Erase all
		  HAL_UART_Transmit(&huart3, (uint8_t *)"Start erasing chip\n\r", 20, 10);
		  if (SPI_Erase_All() == SPI_OK){
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is successful\n\r", 23, 10);
		  }else{
			  HAL_UART_Transmit(&huart3, (uint8_t *)"Erasing is not successful\n\r", 27, 10);
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */




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

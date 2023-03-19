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
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum
{
	RCV_SPI_ERR = 0,
	SPI_OK = 1
} SPI_RetCode_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define LINE_NUMBER 22
#define LINE_SIZE  100
#define BLOCK_SIZE 4096

#define CMD_READ       0x03 //Read Memory at 25MHz
#define CMD_READ_FAST  0x0B //Read Memory at 50MHz
#define CMD_ERASE_4K   0x20 //Erase 4 KByte of memory array
#define CMD_ERASE_32K  0x52 //Erase 32 KByte block of memory array
#define CMD_ERASE_64K  0xD8 //Erase 64 KByte block of memory array
#define CMD_ERASE_CHIP 0x60 //Erase Full Memory Array
#define CMD_PROG_BYTE  0x02 //To Program One Data Byte
#define CMD_PROG_WORD  0xAD //Auto Address Increment Programming
#define CMD_RDSR       0x05 //Read-Status-Register
#define CMD_EWSR       0x50 //Enable-Write-Status-Register
#define CMD_WRSR       0x01 //Write-Status-Register
#define CMD_WREN       0x06 //Write-Enable
#define CMD_WRDI       0x04 //Write-Disable
#define CMD_READ_ID    0x90 //Read-ID
#define CMD_JEDEC_ID   0x9F //JEDEC ID read
#define CMD_EBSY       0x70
#define CMD_DBSY       0x80

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
SPI_RetCode_t SPI_Read(void);
SPI_RetCode_t SPI_Erase(void);
SPI_RetCode_t SPI_Write_status(uint8_t const status);
SPI_RetCode_t SPI_Write(void);
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

  SPI_Erase();

  SPI_Read();

  SPI_Write();

  SPI_Read();

  SPI_Erase();

  SPI_Read();

  while (1)
  {
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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

SPI_RetCode_t SPI_Read(void){
	for (uint8_t block = 0; block < LINE_NUMBER; block++){

		uint8_t cmdBuf[4] = {0};
		uint8_t rcvBuf[LINE_SIZE] = {0};

		uint32_t address = block * BLOCK_SIZE;
		cmdBuf[0] = CMD_READ;
		cmdBuf[1] = (address >> 16) & 0xFF;
		cmdBuf[2] = (address >>  8) & 0xFF;
		cmdBuf[3] = (address >>  0) & 0xFF;

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

		HAL_StatusTypeDef spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 4, 1000);
		if (spi_status != HAL_OK) {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
			return RCV_SPI_ERR;
		}

		spi_status = HAL_SPI_Receive(&hspi1, rcvBuf, LINE_SIZE, 1000);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		if (spi_status != HAL_OK)
			return RCV_SPI_ERR;

		uint16_t first_empty_pos = 0;
		for(uint16_t symbol = 0; symbol < LINE_SIZE; symbol++){
			if(rcvBuf[symbol] == 0xFF || rcvBuf[symbol] == '\n'){
				rcvBuf[symbol] = '\n';
				rcvBuf[symbol + 1] = '\r';
				first_empty_pos = symbol;
				break;
			}
		}
		if (first_empty_pos > 0){
			HAL_UART_Transmit(&huart3, rcvBuf, first_empty_pos + 2, 1000);
		}else{
			rcvBuf[0] = '0' + block / 10;
			rcvBuf[1] = '0' + block % 10;
			rcvBuf[2] = ' ';
			HAL_UART_Transmit(&huart3, rcvBuf, 3, 1000);
			HAL_UART_Transmit(&huart3, (uint8_t *)"Block is empty\n\r", 16, 1000);
		}
	}
	return SPI_OK;
}


SPI_RetCode_t SPI_Erase(void){
	SPI_Write_status(0x80);

	uint8_t cmdBuf[1] = {0};
	cmdBuf[0] = CMD_WREN;

	HAL_StatusTypeDef spi_status;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 1, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	if (spi_status != HAL_OK)
		return RCV_SPI_ERR;

	cmdBuf[0] = CMD_ERASE_CHIP;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 1, 1);
//	spi_status = HAL_SPI_TransmitReceive(&hspi1, cmdBuf, spiBufRx, 1, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
	if (spi_status != HAL_OK)
		return RCV_SPI_ERR;
	HAL_Delay(50); //TSCE

	SPI_Write_status(0x1C);

	return SPI_OK;

}


SPI_RetCode_t SPI_Write_status(uint8_t const status){
	uint8_t cmdBuf[2] = {0};

	cmdBuf[0] = CMD_EWSR;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_StatusTypeDef spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 1, 1000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	if (spi_status != HAL_OK)
		return RCV_SPI_ERR;

	cmdBuf[0] = CMD_WRSR;
	cmdBuf[1] = status;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 2, 1000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	if (spi_status != HAL_OK)
		return RCV_SPI_ERR;
	return SPI_OK;
}


SPI_RetCode_t SPI_Write(void){
	SPI_Write_status(0x80);

	for (uint8_t line = 0; line < LINE_NUMBER; line++){
		for (uint8_t symbol = 0; symbol < strlen(text[line]); symbol++) {
			uint8_t cmdBuf[5] = {0};
			cmdBuf[0] = CMD_WREN;
			HAL_StatusTypeDef spi_status;

			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
			spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 1, 1);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

			if (spi_status != HAL_OK)
				return RCV_SPI_ERR;

			uint32_t address = line * BLOCK_SIZE + symbol;

			cmdBuf[0] = CMD_PROG_BYTE;
			cmdBuf[1] = (address >> 16) & 0xFF;
			cmdBuf[2] = (address >>  8) & 0xFF;
			cmdBuf[3] = (address >>  0) & 0xFF;
			cmdBuf[4] = text[line][symbol];

			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
			spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 5, 1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

			if (spi_status != HAL_OK)
				return RCV_SPI_ERR;
			HAL_Delay(1); //TBP 10 microseconds
		}
	}
	SPI_Write_status(0x1C);

	return SPI_OK;
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

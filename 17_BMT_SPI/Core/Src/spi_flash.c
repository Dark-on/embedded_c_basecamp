/*
 * spi_flash.c
 *
 *  Created on: Mar 20, 2023
 *      Author: dark-on
 */
#include <string.h>
#include <stdint.h>

#include "spi_flash.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;

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

#define SECTOR_SIZE 4096

/* Private function prototypes -----------------------------------------------*/
SPI_RetCode_t SPI_Write_status(uint8_t const status);
HAL_StatusTypeDef SPI_Write_Enable(void);



SPI_RetCode_t SPI_Read(uint8_t const line_number){
	for (uint8_t sector = 0; sector < line_number; sector++){
		uint8_t rcvBuf[LINE_SIZE] = {0};

		uint8_t cmdBuf[4] = {0};
		uint32_t address = sector * SECTOR_SIZE;

		cmdBuf[0] = CMD_READ;
		cmdBuf[1] = (address >> 16) & 0xFF;
		cmdBuf[2] = (address >>  8) & 0xFF;
		cmdBuf[3] = (address >>  0) & 0xFF;

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

		HAL_StatusTypeDef spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 4, 1000);
		if (spi_status != HAL_OK) {
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
			return SPI_ERR;
		}

		spi_status = HAL_SPI_Receive(&hspi1, rcvBuf, LINE_SIZE, 1000);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
		if (spi_status != HAL_OK)
			return SPI_ERR;

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
			rcvBuf[0] = '0' + sector / 10;
			rcvBuf[1] = '0' + sector % 10;
			rcvBuf[2] = ' ';
			HAL_UART_Transmit(&huart3, rcvBuf, 3, 1000);
			HAL_UART_Transmit(&huart3, (uint8_t *)"Sector is empty\n\r", 17, 1000);
		}
	}
	return SPI_OK;
}


SPI_RetCode_t SPI_Erase_All(void){
	SPI_Write_status(0x80); //EWSR WRSR

	HAL_StatusTypeDef spi_status;
	spi_status = SPI_Write_Enable();
	if (spi_status != HAL_OK)
		return SPI_ERR;

	uint8_t cmdBuf[1] = {0};
	cmdBuf[0] = CMD_ERASE_CHIP;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 1, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
	if (spi_status != HAL_OK)
		return SPI_ERR;
	HAL_Delay(50); //TSCE

	SPI_Write_status(0x1C);

	return SPI_OK;
}


SPI_RetCode_t SPI_Erase_sector(uint8_t const sector_number){
	SPI_Write_status(0x80); //EWSR WRSR

	HAL_StatusTypeDef spi_status;
	spi_status = SPI_Write_Enable();
	if (spi_status != HAL_OK)
		return SPI_ERR;

	uint8_t cmdBuf[4] = {0};
	uint16_t address = sector_number * SECTOR_SIZE;
	cmdBuf[0] = CMD_ERASE_4K;
	cmdBuf[1] = (address >> 16) & 0xFF;
	cmdBuf[2] = (address >>  8) & 0xFF;
	cmdBuf[3] = (address >>  0) & 0xFF;

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 4, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	if (spi_status != HAL_OK)
		return SPI_ERR;
	HAL_Delay(25); //TSE

	SPI_Write_status(0x1C);

	return SPI_OK;
}


SPI_RetCode_t SPI_Erase_block(block_size_t const block_size, uint8_t const block_number){
	SPI_Write_status(0x80); //EWSR WRSR

	HAL_StatusTypeDef spi_status;
	spi_status = SPI_Write_Enable();
	if (spi_status != HAL_OK)
		return SPI_ERR;

	uint8_t cmdBuf[4] = {0};
	uint32_t address = block_number * block_size;
	cmdBuf[0] = block_size == BLOCK_32KB ? CMD_ERASE_32K : CMD_ERASE_64K;
	cmdBuf[1] = (address >> 16) & 0xFF;
	cmdBuf[2] = (address >>  8) & 0xFF;
	cmdBuf[3] = (address >>  0) & 0xFF;

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 4, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	if (spi_status != HAL_OK)
		return SPI_ERR;
	HAL_Delay(25); //TSE

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
		return SPI_ERR;

	cmdBuf[0] = CMD_WRSR;
	cmdBuf[1] = status;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 2, 1000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	if (spi_status != HAL_OK)
		return SPI_ERR;
	return SPI_OK;
}


SPI_RetCode_t SPI_Write(const char * text[], uint8_t const line_number){
	SPI_Write_status(0x80); //EWSR WRSR

	for (uint8_t line = 0; line < line_number; line++){
		for (uint8_t symbol = 0; symbol < strlen(text[line]); symbol++) {

			if (SPI_Write_Enable() != HAL_OK)
				return SPI_ERR;

			uint8_t cmdBuf[5] = {0};
			uint32_t address = line * SECTOR_SIZE + symbol;

			cmdBuf[0] = CMD_PROG_BYTE;
			cmdBuf[1] = (address >> 16) & 0xFF;
			cmdBuf[2] = (address >>  8) & 0xFF;
			cmdBuf[3] = (address >>  0) & 0xFF;
			cmdBuf[4] = text[line][symbol];

			HAL_StatusTypeDef spi_status;

			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
			spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 5, 1000);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

			if (spi_status != HAL_OK)
				return SPI_ERR;
			HAL_Delay(1); //TBP 10 microseconds
		}
	}
	SPI_Write_status(0x1C); //EWSR WRSR

	return SPI_OK;
}

HAL_StatusTypeDef SPI_Write_Enable(void){
	HAL_StatusTypeDef spi_status;

	uint8_t cmdBuf[1] = {CMD_WREN};
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	spi_status = HAL_SPI_Transmit(&hspi1, cmdBuf, 1, 1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

	return spi_status;
}

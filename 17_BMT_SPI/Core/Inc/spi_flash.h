/*
 * spi_flash.h
 *
 *  Created on: Mar 20, 2023
 *      Author: dark-on
 */

#ifndef INC_SPI_FLASH_H_
#define INC_SPI_FLASH_H_

#define LINE_SIZE  100


typedef enum{
	SPI_ERR = 0,
	SPI_OK = 1
} SPI_RetCode_t;

typedef enum{
	BLOCK_32KB = 0x8000,
	BLOCK_64KB = 0x10000
}block_size_t;

SPI_RetCode_t SPI_Read(uint8_t const line_number);
SPI_RetCode_t SPI_Erase_All(void);
SPI_RetCode_t SPI_Erase_sector(uint8_t const sector_number);
SPI_RetCode_t SPI_Erase_block(block_size_t const block_size, uint8_t const block_number);
SPI_RetCode_t SPI_Write(const char * text[], uint8_t const line_number);


#endif /* INC_SPI_FLASH_H_ */

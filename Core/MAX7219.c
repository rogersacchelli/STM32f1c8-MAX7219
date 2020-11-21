/*
 * MAX7219.c
 *
 *  Created on: Nov 21, 2020
 *      Author: Roger Sacchelli
 */

#include "MAX7219.h"

void max7219_cs_enable(void){
	HAL_GPIO_WritePin(MAX7219_SPI_GPIO, GPIO_PIN_4, GPIO_PIN_RESET);
}

void max7219_cs_disable(void){
	HAL_GPIO_WritePin(MAX7219_SPI_GPIO, GPIO_PIN_4, GPIO_PIN_SET);;
}


void max7219_init(SPI_HandleTypeDef *hspi){
	// Init MAX7219
	max7219_cs_enable();
	uint16_t data = MAX7219_MODE_SCAN_LIMIT | 7;
	HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
	max7219_cs_disable();

	data = MAX7219_MODE_INTENSITY | 0xF;
	max7219_cs_enable();
	HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
	max7219_cs_disable();

	data = MAX7219_MODE_POWER | 0x1;
	max7219_cs_enable();
	HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
	max7219_cs_disable();

	data = MAX7219_MODE_DECODE | MAX7219_DECODE_D7;
	max7219_cs_enable();
	HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
	max7219_cs_disable();
}

void max7219_clearDisplay(SPI_HandleTypeDef *hspi)
{
    // Loop until 0, but don't run for zero
		uint8_t i = MAX7219_DIGITS_IN_USE;
		uint16_t data =  MAX7219_CHAR_BLANK | 0x0100;
    do {
        // Set each display in use to blank
    		max7219_cs_enable();
    		HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
    		max7219_cs_disable();
    		data+=0x0100;
        //MAX7219_writeData(i, MAX7219_CHAR_BLANK);
    } while (--i);
}

/*void MAX7219_displayNumber(SPI_HandleTypeDef *hspi, volatile long number)
{
    char negative = 0;
    uint16_t data;

    // Convert negative to positive.
    // Keep a record that it was negative so we can
    // sign it again on the display.
    if (number < 0) {
        negative = 1;
        number *= -1;
    }

    max7219_clearDisplay(hspi);

    // If number = 0, only show one zero then exit
    if (number == 0) {
        //MAX7219_writeData(MAX7219_DIGIT0, 0);
        data = MAX7219_DIGIT0 | 0;
      	HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
        return;
    }

    // Initialization to 0 required in this case,
    // does not work without it. Not sure why.
    //char i = 0;
    uint8_t i = 0;

		// shift number to the left
		//MAX7219_writeData(i, 15);
    data = (i << 8) | 15;
		HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
		++i;

    // Loop until number is 0.
    do {
			if(i != 4)
			{
				//MAX7219_writeData(++i, number % 10);
				data = (i << 8) | (number % 10);
				HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
			}
			else
			{
				data = (++i << 8) | (number % 10) + 128;
				//MAX7219_writeData(++i, (number % 10) + 128);
				HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
					// Actually divide by 10 now.
			}
					number /= 10;
    } while (number);

    // Bear in mind that if you only have three digits, and
    // try to display something like "-256" all that will display
    // will be "256" because it needs an extra fourth digit to
    // display the sign.
    if (negative) {
        //MAX7219_writeData(i, MAX7219_CHAR_NEGATIVE);
    		data = (i << 8)
				HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
  			HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
    }
}*/

void max7219_disp_num(SPI_HandleTypeDef *hspi, long number){
	uint16_t digit_position = 0x100;
	long write_number;

	while (number && ((digit_position >> 8) <= MAX7219_DIGITS_IN_USE)){
		write_number = digit_position | (number % 10);
		max7219_cs_enable();
		HAL_SPI_Transmit(hspi, (uint8_t *) &write_number, 1, 1000);
		max7219_cs_disable();
		number = number / 10;
		digit_position+=0x100;
	}
}

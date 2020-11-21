/*
 * MAX7219.h
 *
 *  Created on: Nov 21, 2020
 *      Author: Roger Sacchelli
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_

//#define MAX7219_LOAD1             PORTB |= (1<<PIN_SS)
//#define MAX7219_LOAD0             PORTB &= ~(1<<PIN_SS)

#include "main.h"

#define MAX7219_SPI_GPIO					GPIOA
#define MAX7219_SPI_CS_PIN				GPIO_PIN_4

#define MAX7219_DIGITS_IN_USE			0x08

#define MAX7219_MODE_DECODE       0x0900
#define MAX7219_MODE_INTENSITY    0x0A00
#define MAX7219_MODE_SCAN_LIMIT   0x0B00
#define MAX7219_MODE_POWER        0x0C00
#define MAX7219_MODE_TEST         0x0F00
#define MAX7219_MODE_NOOP         0x0000

#define MAX7219_DIGIT0            0x0100
#define MAX7219_DIGIT1            0x0200
#define MAX7219_DIGIT2            0x0300
#define MAX7219_DIGIT3            0x0400
#define MAX7219_DIGIT4            0x0500
#define MAX7219_DIGIT5            0x0600
#define MAX7219_DIGIT6            0x0700
#define MAX7219_DIGIT7            0x0800
#define MAX7219_DIGIT8            0x0900
#define MAX7219_DIGIT9            0x0A00

#define MAX7219_DECODE_NONE				0x0
#define MAX7219_DECODE_D0					0x01
#define MAX7219_DECODE_D3					0x0F
#define MAX7219_DECODE_D7					0xFF

#define MAX7219_CHAR_BLANK        0x000F
#define MAX7219_CHAR_NEGATIVE     0x000A

void max7219_cs_enable(void);
void max7219_cs_disable(void);
void max7219_init(SPI_HandleTypeDef *hspi);
void max7219_clearDisplay(SPI_HandleTypeDef *hspi);
void max7219_disp_num(SPI_HandleTypeDef *hspi, long number);



#endif /* INC_MAX7219_H_ */

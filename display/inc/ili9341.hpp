/*
 * ili9341.hpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifndef INC_ILI9341_HPP_
#define INC_ILI9341_HPP_

#include "stm32f7xx_hal.h"


#define DP_WIDTH 320
#define DP_HEIGHT 240
class c_ili9341{

	public:
		void init(void);
		void print_image( const uint8_t *ptr, unsigned width, unsigned height, unsigned x1, unsigned y1 );

	private:
		void init_chip(void);
		void MX_SPI3_Init(void);
		void send_command(uint8_t cmd);
		void send_data(uint8_t data);
		void send_data16(uint16_t *pdata);
		void set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
};



#endif /* INC_ILI9341_HPP_ */

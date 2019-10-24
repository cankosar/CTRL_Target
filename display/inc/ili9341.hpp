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
		void draw_vline(int16_t x1, int16_t y1, int16_t h, uint16_t t, uint16_t color);
		void draw_hline(int16_t x1, int16_t y1, int16_t w, uint16_t t, uint16_t color);
		void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
		void set_text_size(uint8_t s);
		void set_text_color(uint16_t c, uint16_t b);
		void print_static(char* c, uint16_t xm, uint16_t ym, uint8_t xsize);
		void print_num(float val, const char * format, uint8_t width,uint16_t xm, uint16_t ym);

	private:
		//Methods
		void init_chip(void);
		void MX_SPI3_Init(void);
		void send_command(uint8_t cmd);
		void send_data(uint8_t data);
		void send_data16(uint16_t *pdata);
		void send_data16rpt(uint16_t *pdata, uint32_t cnt);
		void set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
		void draw_char(int16_t x, int16_t y, unsigned char c, uint16_t fgcolor, uint16_t bgcolor, uint8_t size);
		void print(char* c, uint16_t xm, uint16_t ym);
		void write(char c);
		void print_float(float val, char * format, uint8_t len, uint16_t xm, uint16_t ym);
		void print_int(int16_t val, char * format, uint8_t len, uint16_t xm, uint16_t ym);
		void set_cursor(int16_t x, int16_t y);

		uint16_t calc_RGB565(uint8_t r,uint8_t g,uint8_t b);
		//Variables
		int16_t cursor_x, cursor_y;
		uint16_t textsize,textcolor,textbgcolor;


};



#endif /* INC_ILI9341_HPP_ */

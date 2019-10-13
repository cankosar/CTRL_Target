/*
 * display.h
 *
 *  Created on: 21.04.2019
 *      Author: Can
 */

//Includes
#include <stdbool.h>

#ifndef DISPLAY_H_
#define DISPLAY_H_
#endif /* DISPLAY_H_ */

#define DP_WIDTH 320
#define DP_HEIGHT 240


void send_command(uint8_t cmd);
void send_data(uint8_t cmd);
void send_data16 (uint16_t *pdata);
void send_data16rpt(uint16_t *pdata, uint32_t cnt);
void init_display(void);
void show_image ( const uint8_t *ptr, unsigned width, unsigned height, unsigned x1, unsigned y1 );
void set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void set_template(void);

//Text functions
void draw_char(int16_t x, int16_t y, unsigned char c, uint16_t fgcolor, uint16_t bgcolor, uint8_t size);
void print(char* c, uint16_t xm, uint16_t ym);
void print_static(char* c, uint16_t xm, uint16_t ym, uint8_t xsize);
void print_float(float val, char * format, uint8_t len, uint16_t xm, uint16_t ym);
void print_int(int16_t val, char * format, uint8_t len, uint16_t xm, uint16_t ym);
void print_num(float val, char * format, uint8_t len, uint8_t width, uint16_t xm, uint16_t ym);
void write(char c);
void set_cursor(int16_t x, int16_t y);
void set_text_size(uint8_t s);
void set_text_color(uint16_t c, uint16_t b);
uint16_t calc_RGB565(uint8_t r,uint8_t g,uint8_t b);

//Geometric functions
void draw_vline(int16_t x1, int16_t y1, int16_t h, uint16_t t, uint16_t color);
void draw_hline(int16_t x1, int16_t y1, int16_t w, uint16_t t, uint16_t color);
void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

uint16_t desc_offset_y;
uint16_t val_offset_y;

uint16_t rot_offset[3];
uint16_t but_offset[4];

uint16_t desc_color;
uint16_t val_color;
uint16_t active_color;
uint16_t inactive_color;

uint16_t ca_area_offset_x;
uint16_t ca_area_offset_y;
uint16_t w_l_thick;
uint16_t w_l_thin;

//LEDs
void LED_set_color(bool R, bool G, bool B);



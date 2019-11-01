/*
 * GUI.hpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifndef INC_GUI_HPP_
#define INC_GUI_HPP_

#include "stm32f7xx_hal.h"
#include "../../hw/inc/HW_config.hpp"
#include "../inc/LED_RGB.hpp"

class c_GUI{

	public:
		void init(void);
		void start(void);
		void draw_template_lines(void);
		void update_enc_desc(uint8_t id, bool status, const char* desc);
		void update_enc_value(uint8_t id, bool status, float* val, const char* format);
		void update_but_value(uint8_t id, bool status, bool flag);
		void update_but_desc(uint8_t id, bool status, const char* desc);
		void update_title(const char* desc);
		void clean_center_area(void);

		//Tuner methods
		void update_frequency(float freq);
		void update_note(const char* act_note);
		void visualize_cent(bool valid,float act_cent);

		c_LED_RGB LED;

	private:
		//Methods
		uint16_t calc_RGB565(uint8_t r,uint8_t g,uint8_t b);


		//Design parameter
		int16_t dx_enc[n_enc]={DX_ENC0,DX_ENC1,DX_ENC2};
		int16_t dx_but[n_but]={DX_BUT0,DX_BUT1,DX_BUT2,DX_BUT3};
};




#endif /* INC_GUI_HPP_ */

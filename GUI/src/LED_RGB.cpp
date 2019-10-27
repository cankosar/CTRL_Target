/*
 * LED_RGB.cpp
 *
 *  Created on: 27.10.2019
 *      Author: Can
 */




#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "../../hw/inc/HW_config.hpp"
#include "../inc/LED_RGB.hpp"

void c_LED_RGB::init(void){

	r=g=b=1;
	update_status();
}

void c_LED_RGB::reset(void){

	r=g=b=0;

	set_color();
}



void c_LED_RGB::set_color(void){

	HAL_GPIO_WritePin(LED_RGB_PORT,LED_R_PIN,(GPIO_PinState)r);		// Red
	HAL_GPIO_WritePin(LED_RGB_PORT,LED_G_PIN,(GPIO_PinState)g);		// Green
	HAL_GPIO_WritePin(LED_RGB_PORT,LED_B_PIN,(GPIO_PinState)b);		// Blue
}

void c_LED_RGB::update_status(void){

	if(error_status){
		//Light red if error
		r=1;
		g=0;
		b=0;
		set_color();
	}else if(mute_status){
		if(dsp_status){
			//Mute and DSP on
			r=0;
			g=1;
			b=1;
		}else{
			//Mute on
			r=0;
			g=0;
			b=1;
		}
		set_color();
	}else if(dsp_status){
		//Only DSP on
		r=0;
		g=1;
		b=0;
		set_color();
	}else{
		//Light white if no flag is up
		r=1;
		g=1;
		b=1;
		set_color();
	}

}

void c_LED_RGB::mute(bool flag){

	mute_status=flag;
	update_status();
}

void c_LED_RGB::error(bool flag){

	error_status=flag;
	update_status();
}

void c_LED_RGB::dsp(bool flag){

	dsp_status=!flag;
	update_status();
}


#ifdef __cplusplus
}
#endif

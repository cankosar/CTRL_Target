/*
 * GUI.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */




#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "../inc/GUI.hpp"
#include "../inc/evm.hpp"
#include "../../com/inc/com_ctrl.hpp"
#include "../../display/inc/ili9341.hpp"
//#include "../../display/inc/demo.hpp"

c_com_ctrl com;
c_ili9341 disp;

c_evm evm;

void c_GUI::init(void){

	//Initialize communication stack
	com.init();

	//Initialize display
	disp.init();

	//Show demo image
//	disp.print_image(demo_screen,DP_WIDTH,DP_HEIGHT,0,0);
}

void c_GUI::start(void){

	//Main loop
	while(1){
		evm.process();
	}
}

void evm_main(void){
	evm.capture();
}


#ifdef __cplusplus
}
#endif

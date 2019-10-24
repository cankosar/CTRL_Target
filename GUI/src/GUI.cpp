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
#include "../inc/GUI_design.hpp"

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

	//Draw template lines
	draw_template_lines();
}

void c_GUI::start(void){

	//Main loop
	while(1){
		evm.process();
	}
}

void c_GUI::draw_template_lines(void){

	//Paint background
	disp.draw_rect(0,0,DP_WIDTH,DP_HEIGHT,COL_BLACK);

	//Draw lines
	disp.draw_hline(0,DP_HEIGHT-H_BAR,DP_WIDTH,LT_THICK,COL_WHITE);
	disp.draw_hline(0,H_BAR,DP_WIDTH,LT_THICK,COL_WHITE);
	disp.draw_vline(DX_ENC01,0,H_BAR_LINE,LT_THIN,COL_WHITE);
	disp.draw_vline(DX_ENC12,0,H_BAR_LINE,LT_THIN,COL_WHITE);
	disp.draw_vline(DX_BUT01,DP_HEIGHT,-H_BAR_LINE,LT_THIN,COL_WHITE);
	disp.draw_vline(DX_BUT12,DP_HEIGHT,-H_BAR_LINE,LT_THIN,COL_WHITE);
	disp.draw_vline(DX_BUT23,DP_HEIGHT,-H_BAR_LINE,LT_THIN,COL_WHITE);
}


void c_GUI::update_enc_desc(uint8_t id, char* desc){

	//Set text size and color
	disp.set_text_size(W_F_DESC);
	disp.set_text_color(COL_DESC,COL_BG);

	//Print text
	disp.print_static(desc,dx_enc[id],DY_DESC,MAX_CHAR_DESC);
}

void c_GUI::update_but_desc(uint8_t id, char* desc){

	//Set text size and color
	disp.set_text_size(W_F_DESC);
	disp.set_text_color(COL_DESC,COL_BG);

	//Print text
	disp.print_static(desc,dx_but[id],DP_HEIGHT-DY_DESC,MAX_CHAR_DESC);
}

void  c_GUI::update_title(char* desc){

	//Set text size and color
	disp.set_text_size(W_F_TITLE);
	disp.set_text_color(COL_TITLE,COL_BG);

	//Print text
	disp.print_static(desc,DP_WIDTH/2,DP_HEIGHT/2,MAX_CHAR_TITLE);
}

void c_GUI::update_enc_value(uint8_t id, float* val, const char* format){

	//Set text size and color
	disp.set_text_size(W_F_VAL);
	disp.set_text_color(COL_VAL,COL_BG);

	//Print text
	disp.print_num(*val,format,MAX_CHAR_VAL,dx_enc[id],DY_VAL);
}

void c_GUI::update_but_value(uint8_t id, bool flag){

	//Set text size and color
	disp.set_text_size(W_F_VAL);

	if(flag){
		disp.set_text_color(COL_ACTIVE,COL_BG);
		//Print text
		disp.print_static((char*)"On",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_VAL);
	}else{
		disp.set_text_color(COL_INACTIVE,COL_BG);
		//Print text
		disp.print_static((char*)"Off",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_VAL);
	}
}

//Interrupt process
void evm_main(void){
	evm.capture();
}


#ifdef __cplusplus
}
#endif

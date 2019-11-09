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
#include "math.h"
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

	//Initialize event manager
	evm.init();

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


void c_GUI::update_enc_desc(uint8_t id, bool status, const char* desc){


	//Set text size and color
	disp.set_text_size(W_F_DESC);
	disp.set_text_color(COL_DESC,COL_BG);


	//Print text
	if(status){
		disp.print_static(desc,dx_enc[id],DY_DESC,MAX_CHAR_ENC);
	}else{
		disp.print_static("",dx_enc[id],DY_DESC,MAX_CHAR_ENC);
	}
}

void c_GUI::update_but_desc(uint8_t id, bool status, const char* desc){

	//Set text size and color
	disp.set_text_size(W_F_DESC);
	disp.set_text_color(COL_DESC,COL_BG);

	//Print text
	if(status){
		disp.print_static(desc,dx_but[id],DP_HEIGHT-DY_DESC,MAX_CHAR_BUT);
	}else{
		disp.print_static("",dx_but[id],DP_HEIGHT-DY_DESC,MAX_CHAR_BUT);
	}
}

void  c_GUI::update_title(const char* desc){

	//Set text size and color
	disp.set_text_size(W_F_TITLE);
	disp.set_text_color(COL_TITLE,COL_BG);

	//Print text
	disp.print_static(desc,DX_CENTER,DY_CENTER,MAX_CHAR_TITLE);
}

void  c_GUI::clean_center_area(void){

	//Paint background
	disp.draw_rect(DX_CENTER_AREA,DY_CENTER_AREA,W_CENTER_AREA,H_CENTER_AREA,COL_BG);

}

void c_GUI::update_enc_value(uint8_t id, bool status, float* val, const char* format){

	//Set text size and color
	disp.set_text_size(W_F_VAL);
	disp.set_text_color(COL_VAL,COL_BG);

	//Print text
	if(status){
		disp.print_num(*val,format,MAX_CHAR_ENC,dx_enc[id],DY_VAL);
	}else{
		disp.print_static("",dx_enc[id],DY_VAL,MAX_CHAR_ENC);
	}
}

void c_GUI::update_but_value(uint8_t id, bool type, bool status, bool flag){

	//Set text size and color
	disp.set_text_size(W_F_VAL);

	if(status){
		if(type==but_type_activate){
			//Type is standard toggle
			if(flag){
				disp.set_text_color(COL_ACTIVE,COL_BG);
				//Print text
				disp.print_static((char*)"On",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);
			}else{
				disp.set_text_color(COL_INACTIVE,COL_BG);
				//Print text
				disp.print_static((char*)"Off",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);
			}
		}else if(type==but_type_tap){
			//Type is TAP
			disp.set_text_color(COL_INACTIVE,COL_BG);
			disp.print_static((char*)"REC",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);
			HAL_Delay(200);
			disp.print_static((char*)"",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);

		}else if(type==but_type_save){
			//Type is save
			disp.set_text_color(COL_INACTIVE,COL_BG);
			disp.print_static((char*)"SAVED",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);
			HAL_Delay(200);
			disp.print_static((char*)"",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);
		}
	}else{
		disp.print_static((char*)"",dx_but[id],DP_HEIGHT-DY_VAL,MAX_CHAR_BUT);
	}
}


void c_GUI::update_frequency(float freq){
	//Print frequency

//	printf("%f\n",freq);

	disp.set_text_size(W_F_FREQ);
	disp.set_text_color(COL_FREQ,COL_BG);
	if(freq!=0){
		disp.print_num(freq,"%.1f Hz",W_F_FREQ,DX_FREQ,DY_FREQ);
	}else{
		disp.print_num(freq," ",W_F_FREQ,DX_FREQ,DY_FREQ);
	}
}

void c_GUI::update_note(const char* act_note){

	//Print Note
	disp.set_text_size(W_F_NOTE);
	disp.set_text_color(COL_NOTE,COL_BG);

	disp.print_static(act_note,DX_CENTER+15,DY_CENTER,12);

}

/*Visualizing cent on the display*/
void c_GUI::visualize_cent(bool valid, float act_cent){

	//Declare
	int8_t n_col;	//Number of cent columns


	uint16_t temp_color;

	//Number of columns
	n_col=(int8_t) round(act_cent/5);

//	printf("Actcent:%f, n col:%d\n",act_cent,n_col);

	int8_t n;
	for(n=1;n<=10;n++){

		//Visualize columns

		//Set color of the column
		temp_color=calc_RGB565(100,100-n*10,100-10*n);

		if(valid){
			if (n_col>0){
	//			printf("Show pos\n");
				//Show positive columns
				if(n_col>=n){
					disp.draw_hline(DX_CENTER+(n-1)*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,temp_color);
				}else{
					disp.draw_hline(DX_CENTER+(n-1)*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);
				}

				//Hide negative columns
				disp.draw_hline(DX_CENTER-n*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);

			}else if(n_col<0){
	//			printf("Show neg\n");
				//Show negative columns
				if(n_col<=(-1*n)){
					disp.draw_hline(DX_CENTER-n*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,temp_color);
				}else{
					disp.draw_hline(DX_CENTER-n*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);
				}
				//Hide positive columns
				disp.draw_hline(DX_CENTER+(n-1)*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);

			}else{		//ncol==0 => Match
	//			printf("Show all\n");
				//Show both positive and negative columns
				if(n==1){
					disp.draw_hline(DX_CENTER-n*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,COL_MATCH);
					disp.draw_hline(DX_CENTER+(n-1)*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,COL_MATCH);
				}else{
					disp.draw_hline(DX_CENTER+(n-1)*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);
					disp.draw_hline(DX_CENTER-n*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);

				}

			}

		}else{
			disp.draw_hline(DX_CENTER+(n-1)*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);
			disp.draw_hline(DX_CENTER-n*W_CENTBLOCK,DY_CENTBAR,W_CENTBLOCK,H_CENTBLOCK,0);

		}

	}


}

uint16_t c_GUI::calc_RGB565(uint8_t r,uint8_t g,uint8_t b){
	return (uint8_t)(r*0.31)<<11|(uint8_t)(g*0.63)<<5|(uint8_t)(b*0.31);
}


//Interrupt process
void evm_main(void){
	evm.capture();
}

void evm_backup_trigger(void){
	evm.update_backup_memory();
}

void evm_tuner(void){

	evm.update_tuner();
}

void evm_expression(void){

	evm.update_exppedal();
}

#ifdef __cplusplus
}
#endif

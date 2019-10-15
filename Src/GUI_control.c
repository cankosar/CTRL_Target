/*
 * global_app.c
 *
 *  Created on: 20.04.2019
 *      Author: Can
 */


#include "main.h"
#include "math.h"
#include "stdbool.h"
#include "stm32f7xx_hal.h"
#include "GUI_control.h"
#include "HW_handlers.h"
#include "HW_config.h"
#include "tuner.h"



uint8_t bank; //Current context id
uint8_t init_success=0;

bool mute_state=0;
bool dsp_state=1;

//uint8_t n_context=3;


//Functions

void update_encoder(uint8_t eid, int diff){ //eid=encoder id

//	float updated_val;
	union ctrltypes val;
	val.f32=update_encoder_item(eid, diff);
	update_encoder_value(eid);
//	update_dsp(eid,0); //0=encoder, 1=button
//	trigger_com(); //Trigger communication to DSP board


	send_update(bank,0,eid,val,CTRLNULL,CTRLNULL,CTRLNULL,CTRLNULL);

	//Save settings to non-volatile memory Backup SRAM
//	save_settings_nv();
}

void update_button(uint8_t bid){ //bid=button id


//	printf("Update but:%d in bank %d\n",bid,bank);
	menu[bank].but[bid].value=!(menu[bank].but[bid].value);

//	printf("Set button value=%d\n",menu[bank].but[bid].value);
	update_button_value(bid);
	update_settings(bid,1);
//	update_dsp(bid,1); //0=encoder, 1=button
//	trigger_com(); //Trigger communication to DSP board
	update_active_bits(bid, 1);

	union ctrltypes val;

	if(bid==0){
		val.u32=active_bits;
	}else{
		val.u32=(uint32_t)menu[bank].but[bid].value;
	}

	send_update(bank,1,bid,val,CTRLNULL,CTRLNULL,CTRLNULL,CTRLNULL);

	//Save settings to non-volatile memory Backup SRAM
//	save_settings_nv();
}

float update_encoder_item(uint8_t eid, int diff){

	menu[bank].enc[eid].value+=diff*menu[bank].enc[eid].step_size;

	if(menu[bank].enc[eid].value<menu[bank].enc[eid].lower_limit){
		menu[bank].enc[eid].value=menu[bank].enc[eid].lower_limit;
	}else if (menu[bank].enc[eid].value>menu[bank].enc[eid].upper_limit){
		menu[bank].enc[eid].value=menu[bank].enc[eid].upper_limit;
	}

	return menu[bank].enc[eid].value;
}

void update_encoder_value(uint8_t eid)
{
//	printf("Updating value\n");
	set_text_size(2);
	set_text_color(val_color,0);
	if(menu[bank].enc[eid].state){ //If state==1==active
		print_num(menu[bank].enc[eid].value,menu[bank].enc[eid].format,5,8,rot_offset[eid],val_offset_y);
	}else{
		print_static("",rot_offset[eid],val_offset_y,8);
	}
}

void update_button_value(uint8_t bid)
{
//	printf("Display button:%d in bank %d\n",bid,bank);
	if(menu[bank].but[bid].state){ //If state==1==active
//		printf("In bank\n");
		if(menu[bank].but[bid].value==1){
//			printf("Print on\n");
			set_text_size(2);
			set_text_color(active_color,0);
			print_static("On",but_offset[bid],DP_HEIGHT-val_offset_y,6);
		}else if(menu[bank].but[bid].value==0){
//			printf("Print Off!\n");
			set_text_size(2);
			set_text_color(inactive_color,0);
			print_static("Off",but_offset[bid],DP_HEIGHT-val_offset_y,6);
		}
	}else{
		set_text_size(2);
		set_text_color(active_color,0);
		print_static("",but_offset[bid],DP_HEIGHT-val_offset_y,6);
	}
}

void update_ui_context(int diff)
{
	bank=modulo(bank+diff,n_context);
	update_context();
}

void init_menu(void)
{

	//Bank 0
	strcpy(menu[0].name,"Settings");
	menu[0].bank_id=0;
	menu[0].ctrl_offset=1;

	strcpy(menu[0].enc[0].name,"Tuner A4");
	menu[0].enc[0].state=1;
	menu[0].enc[0].value=440;
	menu[0].enc[0].lower_limit=430;
	menu[0].enc[0].upper_limit=450;
	menu[0].enc[0].step_size=1;
	strcpy(menu[0].enc[0].format,"%.0f");

	strcpy(menu[0].enc[1].name,"Volume");
	menu[0].enc[1].state=1;
	menu[0].enc[1].value=50;
	menu[0].enc[1].lower_limit=0;
	menu[0].enc[1].upper_limit=100;
	menu[0].enc[1].step_size=1;
	strcpy(menu[0].enc[1].format,"%.0f");

	strcpy(menu[0].enc[2].name,"");
	menu[0].enc[2].state=0;

	strcpy(menu[0].but[0].name,"Active");
	menu[0].but[0].state=1;
	menu[0].but[0].value=1;



	strcpy(menu[0].but[1].name,"");
	menu[0].but[1].state=0;


	strcpy(menu[0].but[2].name,"");
	menu[0].but[2].state=0;

	strcpy(menu[0].but[3].name,"");
	menu[0].but[3].state=0;

	//Bank 1
	strcpy(menu[1].name,"Low Mid EQ");
	menu[1].bank_id=2;
	menu[1].fid=2;
	menu[1].ctrl_offset=5;

	strcpy(menu[1].enc[0].name,"Gain");
	menu[1].enc[0].state=1;
	menu[1].enc[0].value=0;
	menu[1].enc[0].lower_limit=-20;
	menu[1].enc[0].upper_limit=20;
	menu[1].enc[0].step_size=0.5;
	strcpy(menu[1].enc[0].format,"%.0f");

	strcpy(menu[1].enc[1].name,"Freq");
	menu[1].enc[1].state=1;
	menu[1].enc[1].value=150;
	menu[1].enc[1].lower_limit=80;
	menu[1].enc[1].upper_limit=500;
	menu[1].enc[1].step_size=10;
	strcpy(menu[1].enc[1].format,"%.0f");

	strcpy(menu[1].enc[2].name,"Width");
	menu[1].enc[2].state=1;
	menu[1].enc[2].value=0.7;
	menu[1].enc[2].lower_limit=0.5;
	menu[1].enc[2].upper_limit=7;
	menu[1].enc[2].step_size=0.1;
	strcpy(menu[1].enc[2].format,"%.1f");

	strcpy(menu[1].but[0].name,"Active");
	menu[1].but[0].state=1;
	menu[1].but[0].value=1;

	strcpy(menu[1].but[1].name,"Bright");
	menu[1].but[1].state=0;
	menu[1].but[1].value=0;

	strcpy(menu[1].but[2].name,"Crisp");
	menu[1].but[2].state=0;
	menu[1].but[2].value=0;

	strcpy(menu[1].but[3].name,"Tube");
	menu[1].but[3].state=0;
	menu[1].but[3].value=0;


	//Bank 2
	strcpy(menu[2].name,"Mid EQ");
	menu[2].bank_id=3;
	menu[2].fid=2;
	menu[2].ctrl_offset=10;

	strcpy(menu[2].enc[0].name,"Gain");
	menu[2].enc[0].state=1;
	menu[2].enc[0].value=0;
	menu[2].enc[0].lower_limit=-20;
	menu[2].enc[0].upper_limit=20;
	menu[2].enc[0].step_size=0.5;
	strcpy(menu[2].enc[0].format,"%.0f");

	strcpy(menu[2].enc[1].name,"Freq");
	menu[2].enc[1].state=1;
	menu[2].enc[1].value=800;
	menu[2].enc[1].lower_limit=400;
	menu[2].enc[1].upper_limit=2000;
	menu[2].enc[1].step_size=10;
	strcpy(menu[2].enc[1].format,"%.0f");

	strcpy(menu[2].enc[2].name,"Width");
	menu[2].enc[2].state=1;
	menu[2].enc[2].value=0.7;
	menu[2].enc[2].lower_limit=0.5;
	menu[2].enc[2].upper_limit=7;
	menu[2].enc[2].step_size=0.1;
	strcpy(menu[2].enc[2].format,"%.1f");

	strcpy(menu[2].but[0].name,"Active");
	menu[2].but[0].state=1;
	menu[2].but[0].value=1;

	strcpy(menu[2].but[1].name,"Bright");
	menu[2].but[1].state=0;
	menu[2].but[1].value=0;

	strcpy(menu[2].but[2].name,"Crisp");
	menu[2].but[2].state=0;
	menu[2].but[2].value=0;

	strcpy(menu[2].but[3].name,"Tube");
	menu[2].but[3].state=0;
	menu[2].but[3].value=0;


	//Bank 3
	strcpy(menu[3].name,"Hi Mid EQ");
	menu[3].bank_id=4;
	menu[3].fid=2;
	menu[3].ctrl_offset=15;

	strcpy(menu[3].enc[0].name,"Gain");
	menu[3].enc[0].state=1;
	menu[3].enc[0].value=0;
	menu[3].enc[0].lower_limit=-20;
	menu[3].enc[0].upper_limit=20;
	menu[3].enc[0].step_size=0.5;
	strcpy(menu[3].enc[0].format,"%.0f");

	strcpy(menu[3].enc[1].name,"Freq");
	menu[3].enc[1].state=1;
	menu[3].enc[1].value=4000;
	menu[3].enc[1].lower_limit=2000;
	menu[3].enc[1].upper_limit=5000;
	menu[3].enc[1].step_size=50;
	strcpy(menu[3].enc[1].format,"%.0f");

	strcpy(menu[3].enc[2].name,"Width");
	menu[3].enc[2].state=1;
	menu[3].enc[2].value=0.7;
	menu[3].enc[2].lower_limit=0.5;
	menu[3].enc[2].upper_limit=7;
	menu[3].enc[2].step_size=0.1;
	strcpy(menu[3].enc[2].format,"%.1f");

	strcpy(menu[3].but[0].name,"Active");
	menu[3].but[0].state=1;
	menu[3].but[0].value=1;

	strcpy(menu[3].but[1].name,"Bright");
	menu[3].but[1].state=0;
	menu[3].but[1].value=0;

	strcpy(menu[3].but[2].name,"Crisp");
	menu[3].but[2].state=0;
	menu[3].but[2].value=0;

	strcpy(menu[3].but[3].name,"Tube");
	menu[3].but[3].state=0;
	menu[3].but[3].value=0;

	//Bank 4
	strcpy(menu[4].name,"Delay");
	menu[4].bank_id=5;
//	menu[4].fid=2;
	menu[4].ctrl_offset=20;

	strcpy(menu[4].enc[0].name,"Mix");
	menu[4].enc[0].state=1;
	menu[4].enc[0].value=20;
	menu[4].enc[0].lower_limit=0;
	menu[4].enc[0].upper_limit=100;
	menu[4].enc[0].step_size=1;
	strcpy(menu[4].enc[0].format,"%.0f");

	strcpy(menu[4].enc[1].name,"Feedback");
	menu[4].enc[1].state=1;
	menu[4].enc[1].value=30;
	menu[4].enc[1].lower_limit=0;
	menu[4].enc[1].upper_limit=100;
	menu[4].enc[1].step_size=1;
	strcpy(menu[4].enc[1].format,"%.0f");

	strcpy(menu[4].enc[2].name,"Time");
	menu[4].enc[2].state=1;
	menu[4].enc[2].value=600;
	menu[4].enc[2].lower_limit=10;
	menu[4].enc[2].upper_limit=2000;
	menu[4].enc[2].step_size=100;
	strcpy(menu[4].enc[2].format,"%.0f");

	strcpy(menu[4].but[0].name,"Active");
	menu[4].but[0].state=1;
	menu[4].but[0].value=1;

	strcpy(menu[4].but[1].name,"Bright");
	menu[4].but[1].state=0;
	menu[4].but[1].value=0;

	strcpy(menu[4].but[2].name,"Crisp");
	menu[4].but[2].state=0;
	menu[4].but[2].value=0;

	strcpy(menu[4].but[3].name,"Tube");
	menu[4].but[3].state=0;
	menu[4].but[3].value=0;


	//Bank 6
	strcpy(menu[5].name,"Chorus");
	menu[5].bank_id=6;
//	menu[5].fid=2;
	menu[5].ctrl_offset=25;

	strcpy(menu[5].enc[0].name,"Mix");
	menu[5].enc[0].state=1;
	menu[5].enc[0].value=50;
	menu[5].enc[0].lower_limit=0;
	menu[5].enc[0].upper_limit=100;
	menu[5].enc[0].step_size=1;
	strcpy(menu[5].enc[0].format,"%.0f");

	strcpy(menu[5].enc[1].name,"Depth");
	menu[5].enc[1].state=1;
	menu[5].enc[1].value=5;
	menu[5].enc[1].lower_limit=0;
	menu[5].enc[1].upper_limit=20;
	menu[5].enc[1].step_size=1;
	strcpy(menu[5].enc[1].format,"%.0f");

	strcpy(menu[5].enc[2].name,"Rate");
	menu[5].enc[2].state=1;
	menu[5].enc[2].value=5;
	menu[5].enc[2].lower_limit=1;
	menu[5].enc[2].upper_limit=10;
	menu[5].enc[2].step_size=1;
	strcpy(menu[5].enc[2].format,"%.0f");

	strcpy(menu[5].but[0].name,"Active");
	menu[5].but[0].state=1;
	menu[5].but[0].value=1;

	strcpy(menu[5].but[1].name,"Bright");
	menu[5].but[1].state=0;
	menu[5].but[1].value=0;

	strcpy(menu[5].but[2].name,"Crisp");
	menu[5].but[2].state=0;
	menu[5].but[2].value=0;

	strcpy(menu[5].but[3].name,"Tube");
	menu[5].but[3].state=0;
	menu[5].but[3].value=0;

	//Bank 7
	strcpy(menu[6].name,"Overdrive");
	menu[6].bank_id=7;
//	menu[6].fid=2;
	menu[6].ctrl_offset=30;

	strcpy(menu[6].enc[0].name,"Gain");
	menu[6].enc[0].state=1;
	menu[6].enc[0].value=3;
	menu[6].enc[0].lower_limit=0;
	menu[6].enc[0].upper_limit=10;
	menu[6].enc[0].step_size=1;
	strcpy(menu[6].enc[0].format,"%.0f");

	strcpy(menu[6].enc[1].name,"Lo Cut");
	menu[6].enc[1].state=1;
	menu[6].enc[1].value=220;
	menu[6].enc[1].lower_limit=30;
	menu[6].enc[1].upper_limit=300;
	menu[6].enc[1].step_size=10;
	strcpy(menu[6].enc[1].format,"%.0f");

	strcpy(menu[6].enc[2].name,"Hi Cut");
	menu[6].enc[2].state=1;
	menu[6].enc[2].value=4000;
	menu[6].enc[2].lower_limit=800;
	menu[6].enc[2].upper_limit=10000;
	menu[6].enc[2].step_size=100;
	strcpy(menu[6].enc[2].format,"%.0f");

	strcpy(menu[6].but[0].name,"Active");
	menu[6].but[0].state=1;
	menu[6].but[0].value=0;

	strcpy(menu[6].but[1].name,"Lo-Cut");
	menu[6].but[1].state=0;
	menu[6].but[1].value=1;

	strcpy(menu[6].but[2].name,"Crisp");
	menu[6].but[2].state=0;
	menu[6].but[2].value=0;

	strcpy(menu[6].but[3].name,"Tube");
	menu[6].but[3].state=0;
	menu[6].but[3].value=0;

	//Bank 7
	strcpy(menu[7].name,"Reverb");
	menu[7].bank_id=8;

	strcpy(menu[7].enc[0].name,"Mix");
	menu[7].enc[0].state=1;
	menu[7].enc[0].value=10;
	menu[7].enc[0].lower_limit=0;
	menu[7].enc[0].upper_limit=100;
	menu[7].enc[0].step_size=1;
	strcpy(menu[7].enc[0].format,"%.0f");

	strcpy(menu[7].enc[1].name,"Size");
	menu[7].enc[1].state=1;
	menu[7].enc[1].value=50;
	menu[7].enc[1].lower_limit=0;
	menu[7].enc[1].upper_limit=100;
	menu[7].enc[1].step_size=1;
	strcpy(menu[7].enc[1].format,"%.0f");

	strcpy(menu[7].enc[2].name,"Damp");
	menu[7].enc[2].state=1;
	menu[7].enc[2].value=50;
	menu[7].enc[2].lower_limit=0;
	menu[7].enc[2].upper_limit=100;
	menu[7].enc[2].step_size=1;
	strcpy(menu[7].enc[2].format,"%.0f");

	strcpy(menu[7].but[0].name,"Active");
	menu[7].but[0].state=1;
	menu[7].but[0].value=0;

	strcpy(menu[7].but[1].name,"");
	menu[7].but[1].state=0;

	strcpy(menu[7].but[2].name,"");
	menu[7].but[2].state=0;

	strcpy(menu[7].but[3].name,"");
	menu[7].but[3].state=0;

	//Bank 8
	strcpy(menu[8].name,"Tremolo");
	menu[8].bank_id=9;

	strcpy(menu[8].enc[0].name,"Depth");
	menu[8].enc[0].state=1;
	menu[8].enc[0].value=10;
	menu[8].enc[0].lower_limit=0;
	menu[8].enc[0].upper_limit=100;
	menu[8].enc[0].step_size=1;
	strcpy(menu[8].enc[0].format,"%.0f");

	strcpy(menu[8].enc[1].name,"Rate");
	menu[8].enc[1].state=1;
	menu[8].enc[1].value=10;
	menu[8].enc[1].lower_limit=0;
	menu[8].enc[1].upper_limit=20;
	menu[8].enc[1].step_size=1;
	strcpy(menu[8].enc[1].format,"%.0f");

	strcpy(menu[8].enc[2].name,"Type");
	menu[8].enc[2].state=1;
	menu[8].enc[2].value=1;
	menu[8].enc[2].lower_limit=0;
	menu[8].enc[2].upper_limit=2;
	menu[8].enc[2].step_size=1;
	strcpy(menu[8].enc[2].format,"%.0f");

	strcpy(menu[8].but[0].name,"Active");
	menu[8].but[0].state=1;
	menu[8].but[0].value=0;

	strcpy(menu[8].but[1].name,"");
	menu[8].but[1].state=0;

	strcpy(menu[8].but[2].name,"");
	menu[8].but[2].state=0;

	strcpy(menu[8].but[3].name,"");
	menu[8].but[3].state=0;

	//Bank 9
	strcpy(menu[9].name,"Rotary");
	menu[9].bank_id=10;

	strcpy(menu[9].enc[0].name,"Depth");
	menu[9].enc[0].state=1;
	menu[9].enc[0].value=10;
	menu[9].enc[0].lower_limit=0;
	menu[9].enc[0].upper_limit=100;
	menu[9].enc[0].step_size=1;
	strcpy(menu[9].enc[0].format,"%.0f");

	strcpy(menu[9].enc[1].name,"Rate");
	menu[9].enc[1].state=1;
	menu[9].enc[1].value=10;
	menu[9].enc[1].lower_limit=0;
	menu[9].enc[1].upper_limit=20;
	menu[9].enc[1].step_size=1;
	strcpy(menu[9].enc[1].format,"%.0f");

	strcpy(menu[9].enc[2].name,"Type");
	menu[9].enc[2].state=0;
	menu[9].enc[2].value=1;
	menu[9].enc[2].lower_limit=0;
	menu[9].enc[2].upper_limit=2;
	menu[9].enc[2].step_size=1;
	strcpy(menu[9].enc[2].format,"%.0f");

	strcpy(menu[9].but[0].name,"Active");
	menu[9].but[0].state=1;
	menu[9].but[0].value=0;

	strcpy(menu[9].but[1].name,"");
	menu[9].but[1].state=0;

	strcpy(menu[9].but[2].name,"");
	menu[9].but[2].state=0;

	strcpy(menu[9].but[3].name,"");
	menu[9].but[3].state=0;

	//Bank 10
	strcpy(menu[10].name,"Compressor");
	menu[10].bank_id=11;

	strcpy(menu[10].enc[0].name,"Threshold");
	menu[10].enc[0].state=1;
	menu[10].enc[0].value=-10;
	menu[10].enc[0].lower_limit=-40;
	menu[10].enc[0].upper_limit=0;
	menu[10].enc[0].step_size=1;
	strcpy(menu[10].enc[0].format,"%.0f");

	strcpy(menu[10].enc[1].name,"Ratio");
	menu[10].enc[1].state=1;
	menu[10].enc[1].value=4;
	menu[10].enc[1].lower_limit=1;
	menu[10].enc[1].upper_limit=60;
	menu[10].enc[1].step_size=1;
	strcpy(menu[10].enc[1].format,"%.0f");

	strcpy(menu[10].enc[2].name,"Attack");
	menu[10].enc[2].state=1;
	menu[10].enc[2].value=10;
	menu[10].enc[2].lower_limit=5;
	menu[10].enc[2].upper_limit=50;
	menu[10].enc[2].step_size=1;
	strcpy(menu[10].enc[2].format,"%.0f");

	strcpy(menu[10].but[0].name,"Active");
	menu[10].but[0].state=1;
	menu[10].but[0].value=0;

	strcpy(menu[10].but[1].name,"");
	menu[10].but[1].state=0;

	strcpy(menu[10].but[2].name,"");
	menu[10].but[2].state=0;

	strcpy(menu[10].but[3].name,"");
	menu[10].but[3].state=0;



	//Update active bits
	active_bits=0;

	//Set template
	set_template();

	//Initialize DSP sets
//	init_settings();


	for(int i=1;i<n_context;i++){
		bank=i;
		update_dsp(0,1);
	}

	//Load from backup memory
//	 printf("Loading bank: %d\n",*(__IO uint8_t *) (BKPSRAM_BASE+BKPSRAM_BANK_OFFSET));

	if(*(uint8_t *) (BKPSRAM_BASE+BKPSRAM_BANK_OFFSET)<n_context){
		bank=*(uint8_t *) (BKPSRAM_BASE+BKPSRAM_BANK_OFFSET); //Load bank
	}else{
		bank=0;
	}

	init_success=1;

	update_context();

//	trigger_com();

	//Init LED
	update_led();




}

void update_context(void)
{

//	printf("Updating context\n");

	int i;

	set_text_size(4);
	set_text_color(desc_color,0);

//	printf("Bank: %d, Name: %s\n",bank, menu[bank].name);

	print_static(menu[bank].name,DP_WIDTH/2,DP_HEIGHT/2,12);
	set_text_size(2);

	for(i=0;i<3;i++){
		if(menu[bank].enc[i].state){ //If state==1==active
			print_static(menu[bank].enc[i].name,rot_offset[i],desc_offset_y,8); //Set the name
		}else{
			print_static("",rot_offset[i],desc_offset_y,8);	//Set 9 spaces
		}
	}

	for(i=0;i<4;i++){
		if(menu[bank].but[i].state){
			print_static(menu[bank].but[i].name,but_offset[i],DP_HEIGHT-desc_offset_y,6);
		}else{
			print_static("",but_offset[i],DP_HEIGHT-desc_offset_y,6);
		}
	}

	for(i=0;i<3;i++){
			update_encoder_value(i);
	}

	for(i=0;i<4;i++){
			update_button_value(i);
	}

	save_settings_nv();

}

void update_display(void){
//	printf("R1:%.1f\tR2:%.1f\tR3:%.1f\tB1:%d\tB2:%d\tB3:%d\tB4:%d\t\n",menu[bank].enc[0].value,menu[bank].enc[1].value,menu[bank].enc[2].value,menu[bank].but[0].value,menu[bank].but[1].value,menu[bank].but[2].value,menu[bank].but[3].value);
}

int modulo(int x,int n){
    return (x % n + n) %n;
}

//id: button id or encoder id,
//type: 0=encoder, 1=button
void update_dsp(uint8_t id, uint8_t type){

	switch(bank){

		case 0:
			update_settings(id,type);
			break;
		case 1:
			write_bqf_param(&menu[bank].ctrl_offset, &menu[bank].fid, &menu[bank].enc[0].value, &menu[bank].enc[1].value,&menu[bank].enc[2].value);
			break;
		case 2:
			write_bqf_param(&menu[bank].ctrl_offset, &menu[bank].fid, &menu[bank].enc[0].value, &menu[bank].enc[1].value,&menu[bank].enc[2].value);
			break;
		case 3:
			write_bqf_param(&menu[bank].ctrl_offset, &menu[bank].fid, &menu[bank].enc[0].value, &menu[bank].enc[1].value,&menu[bank].enc[2].value);
			break;
		case 4:
			update_delay();
			break;
		case 5:
			update_chorus();
			break;
		case 6:
			update_overdrive();
			break;
	}
}

void update_settings(uint8_t id, uint8_t type){

	if(id==0&&type==1){ //Button #0: Activating/Deactivating
		if(menu[bank].but[0].value){
			ctrlreg_tx[0].u32|=1<<menu[bank].bank_id; 	//Set active bits
		}else{
			ctrlreg_tx[0].u32=ctrlreg_tx[0].u32&~(1<<menu[bank].bank_id);	//Set inactive bits
		}

		update_led();

	}else if(id==1&&type==0){ //Encoder #1: Volume
		//Set volume
		ctrlreg_tx[1].f32=vol2logvol(menu[0].enc[1].value);
	}else if(id==0&&type==0){
		//Update tuner frequency bins
		update_note_bins((double)menu[0].enc[0].value);

	}


}


uint32_t update_active_bits(uint8_t id, uint8_t type){

	if(type==1 && id==0){
		if(menu[bank].but[0].value){
			active_bits|=1<<menu[bank].bank_id; 	//Set active bits
		}else{
			active_bits=active_bits&~(1<<menu[bank].bank_id);	//Set inactive bits
		}
	}

	return active_bits;
}


void init_settings(void){

	uint8_t i,j,k;

	struct context menu_restore[n_context];
	//Get check hash


	//Check Backup SRAM Hardware
	uint16_t hw_check=SRAM_HWCHECK;														//Assign a random value
	uint16_t c_hash=0;
	memcpy((void*)(BKPSRAM_BASE+BKPSRAM_HWCHECK_OFFSET),&hw_check,2);					//Write the value into Backup SRAM
//	printf("SRAM HW check:%d\n",*(uint16_t*)(BKPSRAM_BASE+BKPSRAM_HWCHECK_OFFSET));		//Print

	if(*(uint16_t*)(BKPSRAM_BASE+BKPSRAM_HWCHECK_OFFSET)==hw_check){
		printf("SRAM HW check successful\n");
		memcpy(&c_hash,(void*)(BKPSRAM_BASE+BKPSRAM_HASHCHECK_OFFSET),2);				//Load hash value from SRAM
//		printf("Loaded hash:%d -> %d\n",*(uint16_t*)(BKPSRAM_BASE+BKPSRAM_HASHCHECK_OFFSET), c_hash);
	}else{
		printf("Backup SRAM HW error!\n");												//Error loop
		while(1){}
	}








	if(c_hash==CHECKHASH){
		printf("Hash check successful...Loading settings\n");
		memcpy(menu_restore,(void *)(BKPSRAM_BASE+BKPSRAM_MENU_HASH_OFFSET),sizeof(menu));

		for(i=0;i<n_context;i++){
			//Update Encoder values
			for(j=0;j<3;j++){
				if(menu_restore[i].enc[j].value<=menu[i].enc[j].upper_limit && menu_restore[i].enc[j].value>=menu[i].enc[j].lower_limit){
					menu[i].enc[j].value=menu_restore[i].enc[j].value;
				}
			}
			//Update button values
			for(k=0;k<4;k++){
				if(menu_restore[i].but[k].value==1 || menu_restore[i].but[k].value==0){
					menu[i].but[k].value=menu_restore[i].but[k].value;
				}
			}
		}
	}else{
		//Re-initialize BACKUP SRAM
		printf("Re-initializing Backup SRAM\n");
		memcpy((void *)(BKPSRAM_BASE+BKPSRAM_MENU_HASH_OFFSET),menu,sizeof(menu));	//Restore menu
		c_hash=CHECKHASH;															//Restore checkhash
//		printf("c_hash:%d\n",c_hash);
		memcpy((void*)(BKPSRAM_BASE+BKPSRAM_HASHCHECK_OFFSET),&c_hash,2);
//		printf("Written hash%d\n",*(uint16_t*)(BKPSRAM_BASE+BKPSRAM_HASHCHECK_OFFSET));

	}


	//Disable every bank
	ctrlreg_tx[0].u32=0;
	//Set active flags of the banks
	for(int i=0;i<n_context;i++){
		if(menu[i].but[0].value){
			ctrlreg_tx[0].u32|=1<<i; 	//Set active bits
		}else{
			ctrlreg_tx[0].u32=ctrlreg_tx[0].u32&~(1<<i);	//Set inactive bits
		}

		//Set volume
		ctrlreg_tx[1].f32=vol2logvol(menu[0].enc[1].value);
	}

	//Tuner
	//Update tuner frequency bins
	root2_12=pow((double) 2,(double) 1/12);
	update_note_bins((double)menu[0].enc[0].value);

}

void toggle_dsp(void){

//	printf("Toggle DSP\n");
	//DSP State: menu[0].but[0].value
	menu[0].but[0].value=!menu[0].but[0].value;

	if(menu[0].but[0].value){
		ctrlreg_tx[0].u32|=1;
	}else{
		ctrlreg_tx[0].u32=ctrlreg_tx[0].u32&~1;
	}

//	printf("DSP state=%d \t Hash: %d\n",dsp_state,ctrlreg_tx[0].u32);
	if(bank==0){ //Update display if Bank 0 is active
		update_button_value(0);

	}

//	trigger_com();
	update_led();
//	printf("LED updated\n");
}

void toggle_mute(void){

	//Update mute state
	mute_state=!mute_state;

	if(mute_state){							//Turned on
		init_tuner();
		ctrlreg_tx[0].u32|=1<<tuner_bank;
	}else{									//Turned off
		deinit_tuner();
		ctrlreg_tx[0].u32=ctrlreg_tx[0].u32&~(1<<tuner_bank);
	}

	//Update pins
	if(mute_state){
		HAL_GPIO_WritePin(PA_Standby_Port,PA_Standby_PIN,1);// Pull up Standby Pin
	}else{
		HAL_GPIO_WritePin(PA_Standby_Port,PA_Standby_PIN,0);// Pull down Standby Pin
	}

	update_led();
}

void init_tuner(void){

	//Clean central area
	draw_rect(0,ca_area_offset_y+w_l_thick,DP_WIDTH,DP_HEIGHT-2*(ca_area_offset_y+w_l_thick),0);

}

void deinit_tuner(void){

	//Clean central area
	draw_rect(0,ca_area_offset_y+w_l_thick,DP_WIDTH,DP_HEIGHT-2*(ca_area_offset_y+w_l_thick),0);

	//Load bank again
	update_context();

}

void update_led(void){

	if(mute_state){
		LED_set_color(0,0,1);
	}else{
		if(menu[0].but[0].value){
			LED_set_color(1,1,1);
		}else{
			LED_set_color(0,1,0);
		}
	}
}

float vol2logvol(float linvol){
	return 5*pow(10,((linvol-100)*0.02));
}

void save_settings_nv(void){

	//Saving bank to backup memory
	 *(uint8_t *)(BKPSRAM_BASE+BKPSRAM_BANK_OFFSET)=bank;

	 //Saving menu hash to backup memory
	 memcpy((void *)(BKPSRAM_BASE+BKPSRAM_MENU_HASH_OFFSET),menu,sizeof(menu));
}

//void trigger_com(void)
//{
//
////	printf("Com trig\n");
//	if(init_success){
//
//		HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) ctrlreg_tx, (uint8_t*) ctrlreg_rx, ctrl_len*4,10);
//		//		HAL_SPI_Transmit_IT(&hspi5, (uint8_t*) ctrlreg_tx,ctrl_len*4); //Find new concept with cyclic DMA
//		//		HAL_SPI_Transmit_DMA(&hspi5, (uint8_t*) ctrlreg_tx,ctrl_len*4); //Find new concept with cyclic DMA
//
////		printf("Check hash:%d\n",(long unsigned int)ctrlreg_rx[0].u32);
//
//
//	}
//
//}



void send_update(uint8_t bank_id, uint8_t type, uint8_t ctrl_id, union ctrltypes w1, union ctrltypes w2, union ctrltypes w3, union ctrltypes w4,union ctrltypes w5){

//	printf("Sending update\n");
	ctrl_tx[0].u8[0]=menu[bank].bank_id;
	ctrl_tx[0].u8[1]=type;
	ctrl_tx[0].u8[2]=ctrl_id;
	ctrl_tx[0].u8[3]=0;

	if(type==1){
		ctrl_tx[1].u32=w1.u32;
//		printf("Button incoming:%lu float=%lu\n",ctrl_tx[1].u32, w1.u32);
	}else{
		ctrl_tx[1].f32=w1.f32;
	}

	ctrl_tx[2].f32=w2.f32;
	ctrl_tx[3].f32=w3.f32;
	ctrl_tx[4].f32=w4.f32;
	ctrl_tx[5].f32=w5.f32;

//	printf("Hash set %d\n",ctrl_tx[0].u32);

	HAL_SPI_Transmit(&hspi5, (uint8_t*) ctrl_tx, l_ctrl*4, 100);

//	printf("Update sent\n");

}

/*
 * menu.cpp
 *
 *  Created on: 21.10.2019
 *      Author: can
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"
#include "../inc/menu.hpp"
#include "../../GUI/inc/GUI.hpp"

extern c_GUI GUI;
extern c_com_ctrl com;

void c_menu::init(void){

	//Capture inactive
	capture_state=0;

	//Reset active bits
	active_bits=0;

	//Load presets
	load_presets();

	//Load backup data
	load_backup();

	//Load UI
	init_ui_context();

	//Init tuner
	tuner.init();
	tuner.update_note_bins(banks[i_general].enc[eid_freqA].value);

	//Transmit settings  DSP
	init_DSP_settings();

	//Capture active
	capture_state=1;

	//Init LED
	GUI.LED.init();


}

void c_menu::init_DSP_settings(void){

	//Transmit encoder settings
	uint8_t i,j;

	for(i=0;i<n_bank;i++){
		for(j=0;j<n_enc_menu;j++){
			send_word.f32=banks[i].enc[j].value;
			com.send_update(i,0,j,send_word);
		}
	}

	//Transmit active bits
	send_word.u32=active_bits;
	com.send_update(0,1,bid_active,send_word);
}




void c_menu::update_encoder(uint8_t eid, int8_t val){

	//Update the value
	float new_val=banks[act_bank].enc[eid].add_value((float)val);

	//Update GUI
	GUI.update_enc_value(eid,banks[act_bank].enc[eid].status, &new_val,banks[act_bank].enc[eid].format);

	//Transmit the change to the DSP-uC
	send_word.f32=new_val;
	com.send_update(act_bank,0,eid,send_word);

}

void c_menu::update_button(uint8_t bid){

	//Update the value
	bool new_val=banks[act_bank].but[bid].toggle_value();

	//Update active bits

	send_word.u32=update_active_bits(act_bank,new_val);

	//Update the GUI
	GUI.update_but_value(bid,banks[act_bank].but[bid].status,new_val);

	//Transmit the change to the DSP-uC
	com.send_update(act_bank,1,bid,send_word);


}

uint32_t c_menu::update_active_bits(uint8_t bank_id, bool val){

	if(val){
		active_bits|=1<<bank_id; 		//Set active bits
	}else{
		active_bits&=(~(1<<bank_id));	//Set inactive bits
	}

	return active_bits;
}

void c_menu::load_active_banks(uint32_t active_bits){

	uint8_t i;

	for(i=0;i<n_bank;i++){
		banks[i].but[bid_active].value=active_bits&(1<<i);
	}


}

void c_menu::toggle_dsp(void){

	//Toggle the value
	bool dsp_state=banks[i_general].but[bid_active].toggle_value();

	//Save backups
	if(!dsp_state){
		save_backup();
	}

	//Update active bits
	send_word.u32=update_active_bits(i_general,dsp_state);

	//Update the GUI if active bank is general bank
	if(act_bank==i_general){
		GUI.update_but_value(bid_active,banks[i_general].but[bid_active].status,dsp_state);
	}
	//Transmit the change to the DSP-uC
	com.send_update(i_general,1,bid_active,send_word);

	//Update LED
	GUI.LED.dsp(dsp_state);



}

void c_menu::toggle_mute(void){

	//Toggle tuner
	mute_state=banks[i_tuner].but[bid_active].toggle_value();

	//Save backups
	if(mute_state){
		save_backup();
	}

	//Mute/Release power amp
	com.set_PA_status(!mute_state);

	//Update LED
	GUI.LED.mute(mute_state);

	//Deinit tuner display
	if(!mute_state){
		GUI.clean_center_area();
		update_ui_context(0);
	}
}

void c_menu::init_ui_context(void){

	//Update the context with no increment
	update_ui_context(0);
}

void c_menu::update_ui_context(int8_t val){

	//Update active bank
	act_bank=mod_positive(act_bank+val,n_bank);

	//Search for the next active bank
	while(1){
		if(banks[act_bank].status){
			break;
		}else{
			if(val>0){
				act_bank=(act_bank+1)%n_bank;
			}else{
				act_bank=(act_bank-1)%n_bank;
			}
		}
	}


	//Update title
	GUI.update_title(banks[act_bank].name);

	//Update the encoders
	uint8_t i;

	for(i=0;i<n_enc_menu;i++){
		//Update encoder descriptions
		GUI.update_enc_desc(i,banks[act_bank].enc[i].status,banks[act_bank].enc[i].name);

		//Update encoder values
		GUI.update_enc_value(i,banks[act_bank].enc[i].status,&banks[act_bank].enc[i].value,banks[act_bank].enc[i].format);
	}

	//Update the buttons
	for(i=0;i<n_but_menu;i++){
		//Update button descriptions
		GUI.update_but_desc(i,banks[act_bank].but[i].status,banks[act_bank].but[i].name);

		//Update button values
		GUI.update_but_value(i,banks[act_bank].but[i].status, banks[act_bank].but[i].value);
	}
}

void c_menu::save_backup(void){

	//Save active bits
	backup_preset.active_bits=active_bits;

	//Save states
	backup_preset.dsp_state=dsp_state;
	backup_preset.mute_state=mute_state;

	//Save active bank
	backup_preset.act_bank=act_bank;

	//Save encoder values
	uint8_t i,j;

	for(i=0;i<n_bank;i++){
		for(j=0;j<n_enc_menu;j++){

			backup_preset.encval[i][j]=banks[i].enc[j].value;
		}
	}

	memcpy((uint8_t*)BKPSRAM_BASE, &backup_preset,sizeof(backup_preset));

}

void c_menu::load_backup(void){

	memcpy(&backup_preset, (uint8_t*)BKPSRAM_BASE ,sizeof(backup_preset));

	//Load active bits
	active_bits=backup_preset.active_bits;
	load_active_banks(active_bits);

	//Load states : Don't load mute and DSP states since it's always written in mute state
//	dsp_state=backup_preset.dsp_state;
//	mute_state=backup_preset.mute_state;

	//Load active bank
	act_bank=backup_preset.act_bank;

	//Load encoder values
	uint8_t i,j;

	for(i=0;i<n_bank;i++){
		for(j=0;j<n_enc_menu;j++){
			if(backup_preset.encval[i][j] <= banks[i].enc[j].max && backup_preset.encval[i][j] >= banks[i].enc[j].min){
				banks[i].enc[j].value=backup_preset.encval[i][j];
			}
		}
	}

}

#ifdef __cplusplus
}
#endif



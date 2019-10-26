/*
 * menu.cpp
 *
 *  Created on: 21.10.2019
 *      Author: can
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "../inc/menu.hpp"
#include "../../GUI/inc/GUI.hpp"

extern c_GUI GUI;
extern c_com_ctrl com;

void c_menu::init(void){

	//Load presets
	load_presets();

	//Load UI
	init_ui_context();

	//Init tuner
	tuner.init();
	tuner.update_note_bins(banks[i_general].enc[eid_freqA].value);

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

void c_menu::toggle_dsp(void){

	//Toggle the value
	bool dsp_state=banks[i_general].but[bid_active].toggle_value();

	//Update active bits
	send_word.u32=update_active_bits(i_general,dsp_state);

	//Update the GUI if active bank is general bank
	if(act_bank==i_general){
		GUI.update_but_value(bid_active,banks[i_general].but[bid_active].status,dsp_state);
	}
	//Transmit the change to the DSP-uC
	com.send_update(i_general,1,bid_active,send_word);

	//Update LED
	//...



}

void c_menu::toggle_mute(void){

	//Toggle tuner
	mute_state=!(banks[i_tuner].but[bid_active].toggle_value());

	//Mute/Release power amp
	//...

	//Update LED
	//...

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


#ifdef __cplusplus
}
#endif



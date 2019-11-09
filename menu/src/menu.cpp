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
	load_preset_from_RAM(&backup_preset,ADDRESS_BACKUP_PRESET);

	//Expression pedal state initialize
	exp_state=banks[bankid_wahwah].but[0].value;

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
			HAL_Delay(50);	//This is important because the DSP target is interrupt driven and the data can be lost
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

void c_menu::toggle_active_button(void){

			//Update the value
		bool new_val=banks[act_bank].but[i_activate_button].toggle_value();

		//Update active bits
		send_word.u32=update_active_bits(act_bank,new_val);

		//Update the GUI
		GUI.update_but_value(i_activate_button,banks[act_bank].but[i_activate_button].type, banks[act_bank].but[i_activate_button].status,new_val);

		//Transmit the change to the DSP-uC
		com.send_update(act_bank,1,i_activate_button,send_word);

		//Update the expression state
		if(act_bank==bankid_wahwah){
			exp_state=banks[bankid_wahwah].but[i_activate_button].value;
		}
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
		if(banks[i].status){
			banks[i].but[bid_active].value=active_bits&(1<<i);
		}else{
			banks[i].but[bid_active].value=0;
		}
	}


}

void c_menu::toggle_dsp(void){

	//Toggle the value
	bool dsp_state=banks[i_general].but[bid_active].toggle_value();

	//Update active bits
	send_word.u32=update_active_bits(bankid_general,dsp_state);

	//Update the GUI if active bank is general bank
	if(act_bank==i_general){
		GUI.update_but_value(bid_active,banks[i_general].but[bid_active].type,banks[i_general].but[bid_active].status,dsp_state);
	}
	//Transmit the change to the DSP-uC
	com.send_update(bankid_general,1,bid_active,send_word);

	//Update LED
	GUI.LED.dsp(dsp_state);



}

void c_menu::toggle_mute(void){

	//Toggle tuner
	mute_state=banks[i_tuner].but[bid_active].toggle_value();

	//Mute/Release power amp
	com.set_PA_status(!mute_state);

	//Update LED
	GUI.LED.mute(mute_state);

	//Deinit tuner display
	if(!mute_state){
		GUI.clean_center_area();
		update_ui_context(0);
	}

	//Update active bits
	send_word.u32=update_active_bits(bankid_tuner,mute_state);

	//Transmit the change to the DSP-uC
	com.send_update(bankid_general,1,bid_active,send_word);

}

void c_menu::init_ui_context(void){

	//Update the context with no increment
	update_ui_context(0);

	//Preset buttons
	GUI.update_but_desc(i_save_button_0,1,"SET 1");
	GUI.update_but_desc(i_save_button_1,1,"SET 2");
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
		GUI.update_but_value(i,banks[act_bank].but[i].type, banks[act_bank].but[i].status, banks[act_bank].but[i].value);
	}

}

void c_menu::save_backup(void){


	save_preset_to_RAM(&backup_preset,ADDRESS_BACKUP_PRESET);

}

void c_menu::save_preset_to_RAM(s_preset *preset, uint32_t address){

	//Save active bits
	preset->active_bits=active_bits;

	//Save active bank
	preset->act_bank=act_bank;

	//Save encoder values
	uint8_t i,j;

	for(i=0;i<n_bank;i++){
		for(j=0;j<n_enc_menu;j++){
			preset->encval[i][j]=banks[i].enc[j].value;
		}
	}

	printf("Copying from: %#X to adress: %#X, size: %d\n",&preset, address, sizeof(*preset) );
	memcpy((uint8_t*)address, &preset,sizeof(preset));
}


void c_menu::load_preset_from_RAM(s_preset *preset, uint32_t address){

	memcpy(preset, (uint8_t*)address ,sizeof(backup_preset));

	//Load active bits
	active_bits=preset.active_bits;

	//Startup: Deactivate tuner always at startup
	active_bits&=(~(1<<bankid_tuner));

	load_active_banks(active_bits);

	//Load states : Don't load mute and DSP states since it's always written in mute state
//	dsp_state=backup_preset.dsp_state;
//	mute_state=backup_preset.mute_state;

	//Load active bank
	act_bank=preset.act_bank;

	//Load encoder values
	uint8_t i,j;

	for(i=0;i<n_bank;i++){
		for(j=0;j<n_enc_menu;j++){
			if(preset.encval[i][j] <= banks[i].enc[j].max && preset.encval[i][j] >= banks[i].enc[j].min){
				banks[i].enc[j].value=preset.encval[i][j];
			}
		}
	}

}

void c_menu::exp_pedal_update(uint16_t val){

	//Send hash
	send_word.u16[0]=val;

	//Transmit the change to the DSP-uC
	com.send_update(bankid_wahwah,type_enc,i_exp_value,send_word);

//	printf("%d\n",val);

}

void c_menu::update_fs0(bool val){

	//Update the value
	banks[fs0_bank].but[0].value=val;

	//Update active bits
	send_word.u32=update_active_bits(fs0_bank,val);

	//Update the GUI
	if(fs0_bank==act_bank){
		GUI.update_but_value(i_activate_button,banks[fs0_bank].but[i_activate_button].type,banks[fs0_bank].but[i_activate_button].status,val);
	}

	//Transmit the change to the DSP-uC
	com.send_update(fs0_bank,1,0,send_word);

}

void c_menu::update_fs1(bool val){

	//Update the value
	banks[fs1_bank].but[0].value=val;

	//Update active bits
	send_word.u32=update_active_bits(fs1_bank,val);

	//Update the GUI
	if(fs1_bank==act_bank){
		GUI.update_but_value(i_activate_button,banks[fs1_bank].but[i_activate_button].type,banks[fs1_bank].but[i_activate_button].status,val);
	}

	//Transmit the change to the DSP-uC
	com.send_update(fs1_bank,1,0,send_word);

}

void c_menu::init_tap(void){

	reset_tap_maf_buffer();
}

void c_menu::process_tap(void){

	uint32_t tap, dist;

	//Moving average value
	float ma;

	tap=HAL_GetTick();
	dist=tap-last_tap;
	last_tap=tap;

	//Delay bank
	if(act_bank==bankid_delay){

		//Check the plausibility
		if(dist>(uint32_t) banks[bankid_delay].enc[1].min && dist<(uint32_t) banks[bankid_delay].enc[1].max){

			//Increase the valid taps
			if(valid_taps<l_maf_tap){
				valid_taps++;
			}

			//Insert the value to the buffer
			maf_tap_buf[maf_ptr]=dist;


			//Update moving average filter pointer
			maf_ptr++;
			if(maf_ptr>=l_maf_tap){
				maf_ptr=0;
			}

			//Calculate moving average
			uint8_t i;
			for(i=0;i<l_maf_tap; i++){
				ma+=(float)maf_tap_buf[i];
			}

			ma=ma/valid_taps;

			if(valid_taps>=4){
				//Update the value
				banks[bankid_delay].enc[i_tap_button].value=ma;

				//Update GUI
				GUI.update_enc_value(i_tap_button,banks[bankid_delay].enc[i_tap_button].status, &ma,banks[bankid_delay].enc[i_tap_button].format);

				//Send message
				//Send hash
				send_word.f32=ma;

				//Transmit the change to the DSP-uC
				com.send_update(bankid_delay,type_enc,i_tap_button,send_word);

			}


		}else{
			reset_tap_maf_buffer();
		}

		//Update GUI
		GUI.update_but_value(i_tap_button,banks[bankid_delay].but[i_tap_button].type,banks[bankid_delay].but[i_tap_button].status,0);

	}
}


void c_menu::reset_tap_maf_buffer(void){

	maf_ptr=0;
	valid_taps=0;
	memset(maf_tap_buf, 0, l_maf_tap*4);

}




void  c_menu::save_user_preset(uint8_t i_preset){

	//Save to RAM
	save_preset_to_RAM(&user_preset[i_preset], ADDRESS_USER_PRESETS + i_preset*MAX_SIZE_PRESET);

	//Show save message
	GUI.update_but_value(i_save_button_0,but_type_save,1,0);
}

void  c_menu::load_user_preset(uint8_t i_preset){

	//Save to RAM
	load_preset_from_RAM(&user_preset[i_preset], ADDRESS_USER_PRESETS + i_preset*MAX_SIZE_PRESET);

}


#ifdef __cplusplus
}
#endif



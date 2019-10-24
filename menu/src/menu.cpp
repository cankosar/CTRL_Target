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

}

void c_menu::update_encoder(uint8_t eid, int8_t val){

	//Update the value
	float new_val=banks[act_bank].enc[eid].add_value((float)val);

	//Update GUI
	GUI.update_enc_value(eid,&new_val,banks[act_bank].enc[eid].format);

	//Transmit the change to the DSP-uC
	send_word.f32=new_val;
	com.send_update(act_bank,0,eid,send_word);
	//Update NV RAM

}

void c_menu::update_button(uint8_t bid){

	//Update the value
	bool new_val=banks[act_bank].but[bid].toggle_value();

	//Update active bits
	send_word.u32=update_active_bits(act_bank,new_val);

	//Update the GUI
	GUI.update_but_value(bid,new_val);

	//Transmit the change to the DSP-uC
	com.send_update(act_bank,1,bid,send_word);

	//Update the non-volatile memory


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

	//Toggle value
	dsp_state=banks[i_general].but[bid_active].toggle_value();
}

void c_menu::toggle_mute(void){

	//Activate tuner
	mute_state=!(banks[i_tuner].but[bid_active].toggle_value());


}

void c_menu::update_ui_context(uint8_t val){



}




#ifdef __cplusplus
}
#endif



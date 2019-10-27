/*
 * menu.hpp
 *
 *  Created on: 21.10.2019
 *      Author: can
 */

#ifndef INC_MENU_HPP_
#define INC_MENU_HPP_

#include "stm32f7xx_hal.h"
#include "../inc/bank.hpp"
#include "../inc/tuner.hpp"
#include "../../com/inc/com_ctrl.hpp"

#define n_bank 16

#define i_general 	0
#define i_tuner 	1
#define i_lowshelf 	2
#define i_lowmid 	3
#define i_mid		4
#define i_highmid	5
#define i_highshelf	6
#define i_delay		7
#define i_chorus	8
#define i_overdrive	9
#define	i_reverb	10
#define i_comp		11
#define i_tremolo	12
#define i_rotary	13
#define i_flanger	14
#define i_autowah	15

//General button ids
#define bid_active 0

#define eid_freqA 0

struct s_preset{

	//Active bits
	uint32_t active_bits;

	//States
	bool dsp_state;
	bool mute_state;

	//Active bank
	uint8_t act_bank;

	//Encoder values
	float encval[n_bank][n_enc_menu];

};

//s_preset backup_pset;

class c_menu{

	public:
		//Methods
		void init(void);
		void load_presets(void);
		void update_encoder(uint8_t eid, int8_t val);
		void update_button(uint8_t bid);
		void init_ui_context(void);
		void update_ui_context(int8_t val);
		void toggle_dsp(void);
		void toggle_mute(void);

		//States
		bool mute_state;
		bool dsp_state;

		//Flag indicating the state of capture
		bool capture_state=0;

		//Tuner
		c_tuner tuner;

	private:

		//Presets
		void save_backup(void);
		void load_backup(void);
		void load_active_banks(uint32_t active_bits);
		void init_DSP_settings(void);

		s_preset backup_preset;

		inline uint8_t mod_positive(int a, int b) { return (a % b + b) % b; }
		uint32_t update_active_bits(uint8_t bank_id, bool val);

		//Variables
		uint8_t act_bank;

		//Menu
		s_bank banks[n_bank];

		//Update hash
		union ctrltypes send_word;

		uint32_t active_bits;

};

#endif /* INC_MENU_HPP_ */

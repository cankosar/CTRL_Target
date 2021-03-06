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
#include "../../../common/common.hpp"

//Addresses of the presets on backup SRAM
#define MAX_SIZE_PRESET 500u	//Max size=500Bytes
#define ADDRESS_BACKUP_PRESET 	BKPSRAM_BASE
#define ADDRESS_USER_PRESETS 		BKPSRAM_BASE+MAX_SIZE_PRESET

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
#define i_wahwah	16

//General button ids
#define bid_active 0

#define eid_freqA 0

struct s_preset{

	//Active bits
	uint32_t active_bits;

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
		void toggle_active_button(void);
		void init_ui_context(void);
		void update_ui_context(int8_t val);
		void toggle_dsp(void);
		void toggle_mute(void);
		void exp_pedal_update(uint16_t val);
		void update_fs0(bool val);
		void update_fs1(bool val);
		void save_backup(void);
		void process_tap(void);
		void save_user_preset(uint8_t i_preset);
		void load_user_preset(uint8_t i_preset);

		//States
		bool mute_state;
		bool dsp_state;
		bool exp_state;

		//Flag indicating the state of capture
		bool capture_state=0;

		//Tuner
		c_tuner tuner;

	private:

		//Presets
		void save_preset_to_RAM(s_preset *preset, uint32_t address);
		void load_preset_from_RAM(s_preset *preset, uint32_t address);

		s_preset backup_preset;
		s_preset user_preset[2];


		void load_active_banks(uint32_t active_bits);
		void send_settings_DSP(void);

		//Tapping
		void init_tap(void);
		void reset_tap_maf_buffer(void);
		uint32_t 	last_tap;
//		uint32_t 	min_dist;
//		uint32_t 	max_dist;
		uint8_t 	maf_ptr;


		static const uint8_t l_maf_tap=10;
		uint32_t maf_tap_buf[l_maf_tap];
		uint8_t valid_taps;



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

/*
 * evm.hpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifndef INC_EVM_HPP_
#define INC_EVM_HPP_
#include "stm32f7xx_hal.h"
#include "../../hw/inc/HW_config.hpp"

class c_evm{

	public:
		void init(void);
		void capture(void);
		void update_tuner(void);
		void update_exppedal(void);
		void update_backup_memory(void);
		void process(void);

	private:
		bool UI_updated;
		//Button update table
		uint8_t t_but_update;
		//Encoder update table
		uint8_t t_enc_update;

		//FIFO register for encoders
		int8_t enc_fifo[n_enc];

		//Gray code register for encoders
		uint8_t enc_greycode[n_enc];

		//LUT counter value
		uint8_t ctr=0;
		//Look up table for counting up and down
		int8_t lut[16]={0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};

		//Buttons
		uint32_t tic[n_but];
		uint16_t t_debounce=10;
		uint8_t release[n_but];;
		uint8_t key_debounced[n_but];
		uint8_t but_trig=0;

		//Process lock
		bool P_LOCK;

		//States
		bool f_tnr_update;
		bool f_bkpsram_update;
		bool f_exp_update;
		bool tuner_update_lock;

		//Expression
		uint16_t last_exp_value;

		int16_t enc[n_enc];
		uint8_t but[n_but];

		//Foot switch current and latest values
		bool c_fs0, d_fs0;
		bool c_fs1, d_fs1;

		uint32_t tic_fs0, tic_fs1;
		uint8_t t_debounce_fs=100;
};



#endif /* INC_EVM_HPP_ */

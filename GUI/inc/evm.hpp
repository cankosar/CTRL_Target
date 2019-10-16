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
		void capture(void);
		void process(void);

	private:
		bool capture_status;
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
		bool mute_state;
		bool tnr_update;
		bool tuner_update_lock;

		int16_t enc[n_enc];
		uint8_t but[n_but];
};



#endif /* INC_EVM_HPP_ */

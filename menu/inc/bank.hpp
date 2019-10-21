/*
 * bank.hpp
 *
 *  Created on: 21.10.2019
 *      Author: can
 */

#ifndef INC_BANK_HPP_
#define INC_BANK_HPP_

#include "stm32f7xx_hal.h"
#include "../../hw/inc/HW_config.hpp"

struct s_enc{

		bool status;
		const char* name;
		float value;
		float min;
		float max;
		float step;
		const char* format;
};

struct s_but{

		const char* name;
		bool status;
		bool value;
};

struct s_bank{

		//Encoder and button instances
		s_enc enc[n_enc];
		s_but but[n_but];

		//Bank parameters
		const char* name;
		bool status;
		uint8_t id;
};



#endif /* INC_BANK_HPP_ */

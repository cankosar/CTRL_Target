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

class c_enc{

	public:
		float add_value(float val);

		bool status;
		const char* name;
		float value;
		float min;
		float max;
		float step;
		const char* format;
};

class c_but{

	public:
		bool toggle_value(void);

		const char* name;
		bool status;
		bool value;
		bool type=0;	//0 is standard, 1 is tap
};

struct s_bank{

		//Encoder and button instances
		c_enc enc[n_enc];
		c_but but[n_but];

		//Bank parameters
		const char* name;
		bool status;
		uint8_t id;
};



#endif /* INC_BANK_HPP_ */

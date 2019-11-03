/*
 * exppedal.hpp
 *
 *  Created on: 03.11.2019
 *      Author: Can
 */

#ifndef INC_EXPPEDAL_HPP_
#define INC_EXPPEDAL_HPP_

#include "stm32f7xx_hal.h"

class c_exppedal{

	public:
		void init(void);

		void start(void);
		void stop(void);
		uint16_t get_value(void);

	private:
		uint32_t adc_val;

};



#endif /* INC_EXPPEDAL_HPP_ */

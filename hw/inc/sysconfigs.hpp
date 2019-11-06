/*
 * sysconfigs.hpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifndef INC_SYSCONFIGS_HPP_
#define INC_SYSCONFIGS_HPP_

class c_sysconfig{
	public:
		void init(void);
		void SystemClock_Config(void);
		void MX_GPIO_Init(void);
		void MX_TIM2_Init(void);
		void MX_TIM3_Init(void);
		void MX_TIM4_Init(void);
		void MX_ADC1_Init(void);
		void enable_backup_sram(void);
};



#endif /* INC_SYSCONFIGS_HPP_ */

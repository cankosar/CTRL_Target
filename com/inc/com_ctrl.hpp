/*
 * com_ctrl.hpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifndef INC_COM_CTRL_HPP_
#define INC_COM_CTRL_HPP_

#include "../../../common/common.hpp"

#define SPI_TIMEOUT 10

//Waiting time in ms
#define t_com_wait 200

class c_com_ctrl{

	public:
		void init(void);
		void send_update(uint8_t bank_id, bool type, uint8_t ctrl_id, union ctrltypes w);
		void request_update(void);
		float request_tuner_value(void);

		//PA
		void set_PA_status(bool flag);

	private:

		bool LOCK=1;
		void setup_DSP_com(void);

		void MX_SPI5_Init(void);

		union ctrltypes ctrl_tx[l_ctrl];
		union ctrltypes ctrl_rx[l_ctrl];

};



#endif /* INC_COM_CTRL_HPP_ */

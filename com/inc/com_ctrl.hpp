/*
 * com_ctrl.hpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifndef INC_COM_CTRL_HPP_
#define INC_COM_CTRL_HPP_

union ctrltypes{
	float f32;
	uint32_t u32;
	uint16_t u16[2];
	uint8_t u8[4];
};


#define l_ctrl 2
#define SPI_TIMEOUT 10

class c_com_ctrl{

	public:
		void init(void);
		void send_update(uint8_t bank_id, bool type, uint8_t ctrl_id, union ctrltypes w);

	private:
		void MX_SPI5_Init(void);

		union ctrltypes ctrl_tx[l_ctrl];
		union ctrltypes ctrl_rx[l_ctrl];

};



#endif /* INC_COM_CTRL_HPP_ */

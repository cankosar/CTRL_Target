/*
 * dsp_control.h
 *
 *  Created on: 28.04.2019
 *      Author: Can
 */

#ifndef DSP_CONTROL_H_
#define DSP_CONTROL_H_



#endif /* DSP_CONTROL_H_ */



//DSP Control structs
#define ctrl_len 44

#define l_ctrl 6

extern float fs;

union ctrltypes{
	float f32;
	uint32_t u32;
	uint16_t u16[2];
	uint8_t u8[4];
};

union ctrltypes ctrlreg_tx[ctrl_len];

union ctrltypes ctrlreg_rx[ctrl_len];

union ctrltypes ctrl_tx[l_ctrl];

uint32_t active_bits;
union ctrltypes CTRLNULL;

float LP_old, HP_old;



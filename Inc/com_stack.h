/*
 * com_stack.h
 *
 *  Created on: 08.09.2019
 *      Author: Can
 */

#ifndef COM_STACK_H_
#define COM_STACK_H_

void init_com(void);

#define SPICOM_CHKHASH 21
#define mask_r2i 0b1					//Flag ready to initialize
#define mask_init 0b10				//Flag : Initialization status
#define TX_CHK_REG	4 //The CHECK hash register from uC

#endif /* COM_STACK_H_ */

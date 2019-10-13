///*
// * com_stack.c
// *
// *  Created on: 08.09.2019
// *      Author: Can
// */
//
//#include "stm32f7xx_hal.h"
//#include "stm32f7xx.h"
//#include "HW_handlers.h"
//#include "HW_config.h"
//#include "dsp_control.h"
//#include "com_stack.h"
//#include "display.h"
//
//void init_com(void){
//
//	LED_set_color(1,0,0);
//	//Wait for the check flag
//	while(1){
//
//
//		/*BUG*/
//		/*Deactivating check hash! Buggy*/
//		/*Validate SPI connection!!!*/
//
//
//		printf("%lu\n",ctrlreg_rx[0].u32);
//		if(ctrlreg_rx[0].u32==SPICOM_CHKHASH){
//			printf("Check hash successful\n");
//			break;
//		}else{
//
//
//			//Wait for 10ms
//
//			//Request the control hash again
//			HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) ctrlreg_tx, (uint8_t*) ctrlreg_rx, ctrl_len*4,10);
//			printf("Trying again to check hash: %d\n",ctrlreg_rx[0].u32);
//
//
//
//		}
//		HAL_Delay(100);
//
//	}
//
//	LED_set_color(1,1,0);
//	//Wait for the flag "Ready to initialize"
//	while(1){
//		if(mask_r2i&ctrlreg_rx[1].u32){
//			printf("DSP ready to be initialized\n");
//			break;
//		}else{
//			printf("Waiting for the init ready flag %d\n",ctrlreg_rx[0].u32);
//			//Wait for 10ms
//			HAL_Delay(100);
//			//Request the control hash again
//			HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) ctrlreg_tx, (uint8_t*) ctrlreg_rx, ctrl_len*4,10);
//		}
//	}
//
//	LED_set_color(1,1,1);
//	//Ready to initialize
//	//Set Check hash in the TX stream
//	ctrlreg_tx[TX_CHK_REG].u32=SPICOM_CHKHASH;
//
//	//Wait for the flag "Initialized"
//		while(1){
//			if(mask_init&ctrlreg_rx[1].u32){
//				printf("DSP initialized\n");
//				break;
//			}else{
//				printf("Waiting for the initialization\n");
//				//Wait for 10ms
//				HAL_Delay(100);
//				//Request the control hash again
//				HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) ctrlreg_tx, (uint8_t*) ctrlreg_rx, ctrl_len*4,10);
//			}
//		}
//
//}

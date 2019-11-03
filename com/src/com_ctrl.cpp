/*
 * com_ctrl.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "../../hw/inc/HW_config.hpp"
#include "../inc/com_ctrl.hpp"

//extern DMA_HandleTypeDef hdma_spi5_tx;
//extern DMA_HandleTypeDef hdma_spi5_rx;
extern SPI_HandleTypeDef hspi5;

extern c_com_ctrl com;

void c_com_ctrl::init(void){

	//Initialize SPI for communication
	MX_SPI5_Init();

	//Set up the communication to DSP
//	setup_DSP_com();

	//Set PA status
	set_PA_status(1);

}

void c_com_ctrl::setup_DSP_com(void){

	//Lock process
	LOCK=1;

	//Set the ready flags of uC
	ctrl_tx[n_cmd].u8[i_bank]=i_com_bank;
	ctrl_tx[n_cmd].u8[i_type]=0;
	ctrl_tx[n_cmd].u8[i_id]=0;
	ctrl_tx[n_cmd].u8[i_reserved]=0;

	ctrl_tx[n_val].u32=uC_ready;

	//Set up the DSP communication

	while(1){
		request_update();

		if(ctrl_rx[n_cmd].u8[i_bank]==i_com_bank && ctrl_rx[n_val].u32 == DSP_ready){
			printf("Communication to DSP is up!\n");
			break;
		}else{
			HAL_Delay(t_com_wait);
			printf("Waiting for DSP!\n");
//			printf("Bank:%d val:%ld",ctrl_rx[n_cmd].u8[i_bank],ctrl_rx[n_val].u32);
		}
	}

	LOCK=0;
}


void c_com_ctrl::set_PA_status(bool flag){

	HAL_GPIO_WritePin(PA_Standby_Port,PA_Standby_PIN,(GPIO_PinState)!flag);		// Set status


}

/* SPI5 init function */
void c_com_ctrl::MX_SPI5_Init(void)
{
	/* SPI5 parameter configuration*/
	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi5.Init.CRCPolynomial = 7;
	hspi5.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi5.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi5) != HAL_OK)
	{
//	_Error_Handler(__FILE__, __LINE__);
	}

}

void c_com_ctrl::send_update(uint8_t bank_id, bool type, uint8_t ctrl_id, union ctrltypes w){

//	printf("Sending update\n");
	ctrl_tx[n_cmd].u8[i_bank]=bank_id;
	ctrl_tx[n_cmd].u8[i_type]=type;
	ctrl_tx[n_cmd].u8[i_id]=ctrl_id;
	ctrl_tx[n_cmd].u8[i_reserved]=0;

	if(type==1){
		ctrl_tx[n_val].u32=w.u32;
//		printf("Button incoming:%lu float=%lu\n",ctrl_tx[1].u32, w1.u32);
	}else{
		ctrl_tx[n_val].f32=w.f32;
	}

//	printf("Hash set %d\n",ctrl_tx[0].u32);

	HAL_SPI_Transmit(&hspi5, (uint8_t*) ctrl_tx, l_ctrl*4, SPI_TIMEOUT);

//	printf("Update sent\n");

}

void c_com_ctrl::request_update(void){

	HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) ctrl_tx, (uint8_t*) ctrl_rx, l_ctrl*4, SPI_TIMEOUT);

}

float c_com_ctrl::request_tuner_value(void){


	if(!LOCK){
		//Request Update
		request_update();
	}

	//Tuner mode is on and will be updated periodically
	return ctrl_rx[n_val].f32;

}

#ifdef __cplusplus
}
#endif

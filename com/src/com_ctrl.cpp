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
#include "../inc/com_ctrl.hpp"

//extern DMA_HandleTypeDef hdma_spi5_tx;
//extern DMA_HandleTypeDef hdma_spi5_rx;
extern SPI_HandleTypeDef hspi5;

void c_com_ctrl::init(void){

	//Initialize SPI for communication
	MX_SPI5_Init();


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




#ifdef __cplusplus
}
#endif

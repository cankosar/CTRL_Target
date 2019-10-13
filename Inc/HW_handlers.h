/*
 * HW_handlers.h
 *
 *  Created on: 10.08.2019
 *      Author: Can
 */

#ifndef HW_HANDLERS_H_
#define HW_HANDLERS_H_


DMA_HandleTypeDef hdma_spi5_tx;
DMA_HandleTypeDef hdma_spi5_rx;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart3;
PCD_HandleTypeDef hpcd_USB_OTG_FS;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi5;


#endif /* HW_HANDLERS_H_ */

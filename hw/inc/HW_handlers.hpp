/*
 * HW_handlers.h
 *
 *  Created on: 10.08.2019
 *      Author: Can
 */

#ifndef HW_HANDLERS_HPP_
#define HW_HANDLERS_HPP_



//Timer handlers
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

//SPI handlers
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi5;
DMA_HandleTypeDef hdma_spi5_tx;
DMA_HandleTypeDef hdma_spi5_rx;

//ADC handlers
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

//GPIO sockets of encoders
GPIO_TypeDef* enc_GPIO_Port[4][2];
uint16_t enc_GPIO_Pin[4][2];

//GPIO sockets of buttons
GPIO_TypeDef* but_GPIO_Port[6];
uint16_t but_GPIO_Pin[6];


#endif /* HW_HANDLERS_H_ */

/*
 * exp_pedal.cpp
 *
 *  Created on: 03.11.2019
 *      Author: Can
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "../inc/exppedal.hpp"


extern ADC_HandleTypeDef hadc1;

void c_exppedal::init(void){

	adc_val=0;

}

void c_exppedal::start(void){

	//Request using interrupt mode
//	HAL_ADC_Start_DMA(&hadc1, &adc_val,1);


}

void c_exppedal::stop(void){

	//Request using interrupt mode
//	HAL_ADC_Stop_DMA(&hadc1);

}

uint16_t c_exppedal::get_value(void){

	//Interrupt mode
	HAL_ADC_Start_IT(&hadc1);
	adc_val=HAL_ADC_GetValue(&hadc1);

	return (uint16_t) adc_val;

}


#ifdef __cplusplus
}
#endif

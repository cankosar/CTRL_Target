/*
 * bank.cpp
 *
 *  Created on: 21.10.2019
 *      Author: can
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "../inc/bank.hpp"


float c_enc::add_value(float val){

	value+=val*step;

	if(value<min){
		value=min;
	}else if(value>max){
		value=max;
	}

	return value;
}

bool c_but::toggle_value(void){

	value=!value;

	return value;
}




#ifdef __cplusplus
}
#endif

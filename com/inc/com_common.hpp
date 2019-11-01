/*
 * com_common.hpp
 *
 *  Created on: 24.10.2019
 *      Author: can
 */

#ifndef INC_COM_COMMON_HPP_
#define INC_COM_COMMON_HPP_

#include "com_ctrl.hpp"

union ctrltypes ctrl_tx[l_ctrl];
union ctrltypes ctrl_rx[l_ctrl];

c_com_ctrl com;


#endif /* INC_COM_COMMON_HPP_ */

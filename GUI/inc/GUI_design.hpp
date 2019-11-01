/*
 * GUI_design.hpp
 *
 *  Created on: 18.10.2019
 *      Author: KOS2ST
 */

#ifndef INC_GUI_DESIGN_HPP_
#define INC_GUI_DESIGN_HPP_

#define DP_WIDTH 320
#define DP_HEIGHT 240

//Dimensioning

#define DX_CENTER 160
#define DY_CENTER 120

#define DY_DESC 15
#define DY_VAL 45

#define DX_ENC01 106
#define DX_ENC12 212

#define DX_BUT01 80
#define DX_BUT12 160
#define DX_BUT23 240

//Top and bottom bars
#define H_BAR 70
#define H_BAR_LINE 60

//Tuner
#define DX_FREQ 130
#define DY_FREQ 160

#define DY_CENTBAR 80

#define H_CENTBAR 40
#define H_CENTBLOCK 15
#define W_CENTBLOCK 15

//Lines
#define LT_THICK 3
#define LT_THIN 1

//Center area
#define DX_CENTER_AREA 0
#define DY_CENTER_AREA H_BAR+LT_THICK
#define W_CENTER_AREA DP_WIDTH
#define H_CENTER_AREA DP_HEIGHT-(H_BAR+LT_THICK)*2

//Font size
#define W_F_TITLE 4
#define W_F_DESC 2
#define W_F_VAL 2
#define W_F_NOTE 5
#define W_F_FREQ 2

//Max count of characters
#define MAX_CHAR_ENC 8
#define MAX_CHAR_BUT 6
#define MAX_CHAR_TITLE 12


//Colors
#define COL_WHITE 65535
#define COL_BLACK 0

#define COL_BG 0
#define COL_DESC 0xFFFF
#define COL_NOTE 0xFFFF
#define COL_FREQ 0xFFFF
#define COL_MATCH 0xD7F8
#define COL_TITLE 0xFFFF
#define COL_VAL 0xAE3F
#define COL_ACTIVE 0xD7F8
#define COL_INACTIVE 0xFE38

#endif /* INC_GUI_DESIGN_HPP_ */

/*
 * menu.cpp
 *
 *  Created on: 21.10.2019
 *      Author: can
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "../inc/bank.hpp"
#include "../inc/menu.hpp"

s_bank menu[n_bank];

void c_menu::init(void){

	/*
			Bank 0: General
	*/
	menu[i_general].name=			"General";
	menu[i_general].id=				0;
	menu[i_general].status=			1;

	//Encoder 0
	menu[i_general].enc[0].name=	"F Tune";
	menu[i_general].enc[0].status=	1;
	menu[i_general].enc[0].value=	440;
	menu[i_general].enc[0].min=		430;
	menu[i_general].enc[0].max=		450;
	menu[i_general].enc[0].step=	1;
	menu[i_general].enc[0].format=	"%.0f";

	//Encoder 1
	menu[i_general].enc[1].name=	"Volume";
	menu[i_general].enc[1].status=	1;
	menu[i_general].enc[1].value=	50;
	menu[i_general].enc[1].min=		0;
	menu[i_general].enc[1].max=		100;
	menu[i_general].enc[1].step=	1;
	menu[i_general].enc[1].format=	"%.0f";

	//Encoder 2
	menu[i_general].enc[2].name=	"";
	menu[i_general].enc[2].status=	0;
	menu[i_general].enc[2].value=	50;
	menu[i_general].enc[2].min=		0;
	menu[i_general].enc[2].max=		100;
	menu[i_general].enc[2].step=	1;
	menu[i_general].enc[2].format=	"%.0f";

	//Button 0
	menu[i_general].but[0].name=	"Active";
	menu[i_general].but[0].status=	1;
	menu[i_general].but[0].value=	1;

	//Button 1
	menu[i_general].but[1].name=	"";
	menu[i_general].but[1].status=	0;
	menu[i_general].but[1].value=	1;

	//Button 2
	menu[i_general].but[2].name=	"";
	menu[i_general].but[2].status=	0;
	menu[i_general].but[2].value=	1;

	//Button 3
	menu[i_general].but[3].name=	"";
	menu[i_general].but[3].status=	0;
	menu[i_general].but[3].value=	1;




}


#ifdef __cplusplus
}
#endif



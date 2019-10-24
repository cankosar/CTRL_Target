/*
 * menu_presets.cpp
 *
 *  Created on: 24.10.2019
 *      Author: can
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "../inc/bank.hpp"
#include "../inc/menu.hpp"
//#include "../inc/menu_common.hpp"

void c_menu::load_presets(void){
	/*
			Bank 0: General
	*/
	banks[i_general].name=			"General";
	banks[i_general].id=				0;
	banks[i_general].status=			1;

	//Encoder 0
	banks[i_general].enc[0].name=	"F Tune";
	banks[i_general].enc[0].status=	1;
	banks[i_general].enc[0].value=	440;
	banks[i_general].enc[0].min=		430;
	banks[i_general].enc[0].max=		450;
	banks[i_general].enc[0].step=	1;
	banks[i_general].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_general].enc[1].name=	"Volume";
	banks[i_general].enc[1].status=	1;
	banks[i_general].enc[1].value=	50;
	banks[i_general].enc[1].min=		0;
	banks[i_general].enc[1].max=		100;
	banks[i_general].enc[1].step=	1;
	banks[i_general].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_general].enc[2].name=	"";
	banks[i_general].enc[2].status=	0;
	banks[i_general].enc[2].value=	50;
	banks[i_general].enc[2].min=		0;
	banks[i_general].enc[2].max=		100;
	banks[i_general].enc[2].step=	1;
	banks[i_general].enc[2].format=	"%.0f";

	//Button 0
	banks[i_general].but[0].name=	"Active";
	banks[i_general].but[0].status=	1;
	banks[i_general].but[0].value=	1;

	//Button 1
	banks[i_general].but[1].name=	"";
	banks[i_general].but[1].status=	0;
	banks[i_general].but[1].value=	1;

	//Button 2
	banks[i_general].but[2].name=	"";
	banks[i_general].but[2].status=	0;
	banks[i_general].but[2].value=	1;

	//Button 3
	banks[i_general].but[3].name=	"";
	banks[i_general].but[3].status=	0;
	banks[i_general].but[3].value=	1;


	/*
			Bank 1: Low Shelf
	*/
	banks[i_lowshelf].name=			"Low shelf";
	banks[i_lowshelf].id=				0;
	banks[i_lowshelf].status=			1;

	//Encoder 0
	banks[i_lowshelf].enc[0].name=	"Gain";
	banks[i_lowshelf].enc[0].status=	1;
	banks[i_lowshelf].enc[0].value=	0;
	banks[i_lowshelf].enc[0].min=		-20;
	banks[i_lowshelf].enc[0].max=		20;
	banks[i_lowshelf].enc[0].step=	1;
	banks[i_lowshelf].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_lowshelf].enc[1].name=	"Freq";
	banks[i_lowshelf].enc[1].status=	1;
	banks[i_lowshelf].enc[1].value=	125;
	banks[i_lowshelf].enc[1].min=		50;
	banks[i_lowshelf].enc[1].max=		250;
	banks[i_lowshelf].enc[1].step=	5;
	banks[i_lowshelf].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_lowshelf].enc[2].name=	"";
	banks[i_lowshelf].enc[2].status=	0;
	banks[i_lowshelf].enc[2].value=	50;
	banks[i_lowshelf].enc[2].min=		0;
	banks[i_lowshelf].enc[2].max=		100;
	banks[i_lowshelf].enc[2].step=	1;
	banks[i_lowshelf].enc[2].format=	"%.0f";

	//Button 0
	banks[i_lowshelf].but[0].name=	"Active";
	banks[i_lowshelf].but[0].status=	1;
	banks[i_lowshelf].but[0].value=	1;

	//Button 1
	banks[i_lowshelf].but[1].name=	"";
	banks[i_lowshelf].but[1].status=	0;
	banks[i_lowshelf].but[1].value=	1;

	//Button 2
	banks[i_lowshelf].but[2].name=	"";
	banks[i_lowshelf].but[2].status=	0;
	banks[i_lowshelf].but[2].value=	1;

	//Button 3
	banks[i_lowshelf].but[3].name=	"";
	banks[i_lowshelf].but[3].status=	0;
	banks[i_lowshelf].but[3].value=	1;
}



#ifdef __cplusplus
}
#endif


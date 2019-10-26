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
	banks[i_lowshelf].name=				"Low shelf";
	banks[i_lowshelf].id=				2;
	banks[i_lowshelf].status=			1;

	//Encoder 0
	banks[i_lowshelf].enc[0].name=		"Gain";
	banks[i_lowshelf].enc[0].status=	1;
	banks[i_lowshelf].enc[0].value=		0;
	banks[i_lowshelf].enc[0].min=		-20;
	banks[i_lowshelf].enc[0].max=		20;
	banks[i_lowshelf].enc[0].step=		1;
	banks[i_lowshelf].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_lowshelf].enc[1].name=		"Freq";
	banks[i_lowshelf].enc[1].status=	1;
	banks[i_lowshelf].enc[1].value=		125;
	banks[i_lowshelf].enc[1].min=		60;
	banks[i_lowshelf].enc[1].max=		200;
	banks[i_lowshelf].enc[1].step=		5;
	banks[i_lowshelf].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_lowshelf].enc[2].name=		"";
	banks[i_lowshelf].enc[2].status=	0;
	banks[i_lowshelf].enc[2].value=		50;
	banks[i_lowshelf].enc[2].min=		0;
	banks[i_lowshelf].enc[2].max=		100;
	banks[i_lowshelf].enc[2].step=		1;
	banks[i_lowshelf].enc[2].format=	"%.0f";

	//Button 0
	banks[i_lowshelf].but[0].name=		"Active";
	banks[i_lowshelf].but[0].status=	1;
	banks[i_lowshelf].but[0].value=		0;

	//Button 1
	banks[i_lowshelf].but[1].name=		"";
	banks[i_lowshelf].but[1].status=	0;
	banks[i_lowshelf].but[1].value=		0;

	//Button 2
	banks[i_lowshelf].but[2].name=		"";
	banks[i_lowshelf].but[2].status=	0;
	banks[i_lowshelf].but[2].value=		0;

	//Button 3
	banks[i_lowshelf].but[3].name=		"";
	banks[i_lowshelf].but[3].status=	0;
	banks[i_lowshelf].but[3].value=		0;

	/*
			Bank 2: Low mid
	*/
	banks[i_lowmid].name=			"Low mid";
	banks[i_lowmid].id=				3;
	banks[i_lowmid].status=			1;

	//Encoder 0
	banks[i_lowmid].enc[0].name=	"Gain";
	banks[i_lowmid].enc[0].status=	1;
	banks[i_lowmid].enc[0].value=		0;
	banks[i_lowmid].enc[0].min=		-20;
	banks[i_lowmid].enc[0].max=		20;
	banks[i_lowmid].enc[0].step=		1;
	banks[i_lowmid].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_lowmid].enc[1].name=	"Freq";
	banks[i_lowmid].enc[1].status=	1;
	banks[i_lowmid].enc[1].value=	200;
	banks[i_lowmid].enc[1].min=		80;
	banks[i_lowmid].enc[1].max=		500;
	banks[i_lowmid].enc[1].step=		5;
	banks[i_lowmid].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_lowmid].enc[2].name=	"Quality";
	banks[i_lowmid].enc[2].status=	1;
	banks[i_lowmid].enc[2].value=	1;
	banks[i_lowmid].enc[2].min=		0.3;
	banks[i_lowmid].enc[2].max=		5;
	banks[i_lowmid].enc[2].step=		0.1;
	banks[i_lowmid].enc[2].format=	"%.1f";

	//Button 0
	banks[i_lowmid].but[0].name=	"Active";
	banks[i_lowmid].but[0].status=	1;
	banks[i_lowmid].but[0].value=	0;

	//Button 1
	banks[i_lowmid].but[1].name=	"";
	banks[i_lowmid].but[1].status=	0;
	banks[i_lowmid].but[1].value=	0;

	//Button 2
	banks[i_lowmid].but[2].name=	"";
	banks[i_lowmid].but[2].status=	0;
	banks[i_lowmid].but[2].value=		0;

	//Button 3
	banks[i_lowmid].but[3].name=	"";
	banks[i_lowmid].but[3].status=	0;
	banks[i_lowmid].but[3].value=	0;

	/*
			Bank 4: Mid
	*/
	banks[i_mid].name=			"Mid";
	banks[i_mid].id=				4;
	banks[i_mid].status=			1;

	//Encoder 0
	banks[i_mid].enc[0].name=	"Gain";
	banks[i_mid].enc[0].status=	1;
	banks[i_mid].enc[0].value=		0;
	banks[i_mid].enc[0].min=		-20;
	banks[i_mid].enc[0].max=		20;
	banks[i_mid].enc[0].step=		1;
	banks[i_mid].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_mid].enc[1].name=	"Freq";
	banks[i_mid].enc[1].status=	1;
	banks[i_mid].enc[1].value=	800;
	banks[i_mid].enc[1].min=		400;
	banks[i_mid].enc[1].max=		2000;
	banks[i_mid].enc[1].step=		5;
	banks[i_mid].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_mid].enc[2].name=	"Quality";
	banks[i_mid].enc[2].status=	1;
	banks[i_mid].enc[2].value=	1;
	banks[i_mid].enc[2].min=		0.3;
	banks[i_mid].enc[2].max=		5;
	banks[i_mid].enc[2].step=		0.1;
	banks[i_mid].enc[2].format=	"%.1f";

	//Button 0
	banks[i_mid].but[0].name=	"Active";
	banks[i_mid].but[0].status=	1;
	banks[i_mid].but[0].value=	0;

	//Button 1
	banks[i_mid].but[1].name=	"";
	banks[i_mid].but[1].status=	0;
	banks[i_mid].but[1].value=	0;

	//Button 2
	banks[i_mid].but[2].name=	"";
	banks[i_mid].but[2].status=	0;
	banks[i_mid].but[2].value=		0;

	//Button 3
	banks[i_mid].but[3].name=	"";
	banks[i_mid].but[3].status=	0;
	banks[i_mid].but[3].value=	0;

	/*
			Bank 5: High middle
	*/
	banks[i_highmid].name=			"High mid";
	banks[i_highmid].id=				5;
	banks[i_highmid].status=			1;

	//Encoder 0
	banks[i_highmid].enc[0].name=	"Gain";
	banks[i_highmid].enc[0].status=	1;
	banks[i_highmid].enc[0].value=		0;
	banks[i_highmid].enc[0].min=		-20;
	banks[i_highmid].enc[0].max=		20;
	banks[i_highmid].enc[0].step=		1;
	banks[i_highmid].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_highmid].enc[1].name=	"Freq";
	banks[i_highmid].enc[1].status=	1;
	banks[i_highmid].enc[1].value=	3000;
	banks[i_highmid].enc[1].min=		2000;
	banks[i_highmid].enc[1].max=		5000;
	banks[i_highmid].enc[1].step=		100;
	banks[i_highmid].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_highmid].enc[2].name=	"Quality";
	banks[i_highmid].enc[2].status=	1;
	banks[i_highmid].enc[2].value=	1;
	banks[i_highmid].enc[2].min=		0.3;
	banks[i_highmid].enc[2].max=		5;
	banks[i_highmid].enc[2].step=		0.1;
	banks[i_highmid].enc[2].format=	"%.1f";

	//Button 0
	banks[i_highmid].but[0].name=	"Active";
	banks[i_highmid].but[0].status=	1;
	banks[i_highmid].but[0].value=	0;

	//Button 1
	banks[i_highmid].but[1].name=	"";
	banks[i_highmid].but[1].status=	0;
	banks[i_highmid].but[1].value=	0;

	//Button 2
	banks[i_highmid].but[2].name=	"";
	banks[i_highmid].but[2].status=	0;
	banks[i_highmid].but[2].value=		0;

	//Button 3
	banks[i_highmid].but[3].name=	"";
	banks[i_highmid].but[3].status=	0;
	banks[i_highmid].but[3].value=	0;

	/*
			Bank 1: High Shelf
	*/
	banks[i_highshelf].name=				"High shelf";
	banks[i_highshelf].id=				6;
	banks[i_highshelf].status=			1;

	//Encoder 0
	banks[i_highshelf].enc[0].name=		"Gain";
	banks[i_highshelf].enc[0].status=	1;
	banks[i_highshelf].enc[0].value=		0;
	banks[i_highshelf].enc[0].min=		-20;
	banks[i_highshelf].enc[0].max=		20;
	banks[i_highshelf].enc[0].step=		1;
	banks[i_highshelf].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_highshelf].enc[1].name=		"Freq";
	banks[i_highshelf].enc[1].status=	1;
	banks[i_highshelf].enc[1].value=		8000;
	banks[i_highshelf].enc[1].min=		4000;
	banks[i_highshelf].enc[1].max=		16000;
	banks[i_highshelf].enc[1].step=		100;
	banks[i_highshelf].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_highshelf].enc[2].name=		"";
	banks[i_highshelf].enc[2].status=	0;
	banks[i_highshelf].enc[2].value=		50;
	banks[i_highshelf].enc[2].min=		0;
	banks[i_highshelf].enc[2].max=		100;
	banks[i_highshelf].enc[2].step=		1;
	banks[i_highshelf].enc[2].format=	"%.0f";

	//Button 0
	banks[i_highshelf].but[0].name=		"Active";
	banks[i_highshelf].but[0].status=	1;
	banks[i_highshelf].but[0].value=		0;

	//Button 1
	banks[i_highshelf].but[1].name=		"";
	banks[i_highshelf].but[1].status=	0;
	banks[i_highshelf].but[1].value=		0;

	//Button 2
	banks[i_highshelf].but[2].name=		"";
	banks[i_highshelf].but[2].status=	0;
	banks[i_highshelf].but[2].value=		0;

	//Button 3
	banks[i_highshelf].but[3].name=		"";
	banks[i_highshelf].but[3].status=	0;
	banks[i_highshelf].but[3].value=		0;

	/*
			Bank 7: Delay
	*/
	banks[i_delay].name=			"Delay";
	banks[i_delay].id=				7;
	banks[i_delay].status=			1;

	//Encoder 0
	banks[i_delay].enc[0].name=	"Dry/wet";
	banks[i_delay].enc[0].status=	1;
	banks[i_delay].enc[0].value=		50;
	banks[i_delay].enc[0].min=		0;
	banks[i_delay].enc[0].max=		100;
	banks[i_delay].enc[0].step=		1;
	banks[i_delay].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_delay].enc[1].name=	"Time";
	banks[i_delay].enc[1].status=	1;
	banks[i_delay].enc[1].value=	600;
	banks[i_delay].enc[1].min=		10;
	banks[i_delay].enc[1].max=		1000;
	banks[i_delay].enc[1].step=		10;
	banks[i_delay].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_delay].enc[2].name=	"Feedback";
	banks[i_delay].enc[2].status=	1;
	banks[i_delay].enc[2].value=	50;
	banks[i_delay].enc[2].min=		0;
	banks[i_delay].enc[2].max=		100;
	banks[i_delay].enc[2].step=		1;
	banks[i_delay].enc[2].format=	"%.0f";

	//Button 0
	banks[i_delay].but[0].name=	"Active";
	banks[i_delay].but[0].status=	1;
	banks[i_delay].but[0].value=	0;

	//Button 1
	banks[i_delay].but[1].name=	"";
	banks[i_delay].but[1].status=	0;
	banks[i_delay].but[1].value=	0;

	//Button 2
	banks[i_delay].but[2].name=	"";
	banks[i_delay].but[2].status=	0;
	banks[i_delay].but[2].value=		0;

	//Button 3
	banks[i_delay].but[3].name=	"";
	banks[i_delay].but[3].status=	0;
	banks[i_delay].but[3].value=	0;

	/*
			Bank 8: Chorus
	*/
	banks[i_chorus].name=			"Chorus";
	banks[i_chorus].id=				8;
	banks[i_chorus].status=			1;

	//Encoder 0
	banks[i_chorus].enc[0].name=	"Dry/wet";
	banks[i_chorus].enc[0].status=	1;
	banks[i_chorus].enc[0].value=		50;
	banks[i_chorus].enc[0].min=		0;
	banks[i_chorus].enc[0].max=		100;
	banks[i_chorus].enc[0].step=		1;
	banks[i_chorus].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_chorus].enc[1].name=	"Depth";
	banks[i_chorus].enc[1].status=	1;
	banks[i_chorus].enc[1].value=	50;
	banks[i_chorus].enc[1].min=		0;
	banks[i_chorus].enc[1].max=		100;
	banks[i_chorus].enc[1].step=	1;
	banks[i_chorus].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_chorus].enc[2].name=	"Freq";
	banks[i_chorus].enc[2].status=	1;
	banks[i_chorus].enc[2].value=	5;
	banks[i_chorus].enc[2].min=		1;
	banks[i_chorus].enc[2].max=		10;
	banks[i_chorus].enc[2].step=		1;
	banks[i_chorus].enc[2].format=	"%.0f";

	//Button 0
	banks[i_chorus].but[0].name=	"Active";
	banks[i_chorus].but[0].status=	1;
	banks[i_chorus].but[0].value=	0;

	//Button 1
	banks[i_chorus].but[1].name=	"";
	banks[i_chorus].but[1].status=	0;
	banks[i_chorus].but[1].value=	0;

	//Button 2
	banks[i_chorus].but[2].name=	"";
	banks[i_chorus].but[2].status=	0;
	banks[i_chorus].but[2].value=		0;

	//Button 3
	banks[i_chorus].but[3].name=	"";
	banks[i_chorus].but[3].status=	0;
	banks[i_chorus].but[3].value=	0;

	/*
			Bank 8: Overdrive
	*/
	banks[i_overdrive].name=			"Overdrive";
	banks[i_overdrive].id=				9;
	banks[i_overdrive].status=			1;

	//Encoder 0
	banks[i_overdrive].enc[0].name=	"Gain";
	banks[i_overdrive].enc[0].status=	1;
	banks[i_overdrive].enc[0].value=		50;
	banks[i_overdrive].enc[0].min=		0;
	banks[i_overdrive].enc[0].max=		100;
	banks[i_overdrive].enc[0].step=		1;
	banks[i_overdrive].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_overdrive].enc[1].name=	"HP Freq.";
	banks[i_overdrive].enc[1].status=	1;
	banks[i_overdrive].enc[1].value=	250;
	banks[i_overdrive].enc[1].min=		100;
	banks[i_overdrive].enc[1].max=		300;
	banks[i_overdrive].enc[1].step=	10;
	banks[i_overdrive].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_overdrive].enc[2].name=	"LP Freq.";
	banks[i_overdrive].enc[2].status=	1;
	banks[i_overdrive].enc[2].value=	2500;
	banks[i_overdrive].enc[2].min=		2000;
	banks[i_overdrive].enc[2].max=		10000;
	banks[i_overdrive].enc[2].step=		100;
	banks[i_overdrive].enc[2].format=	"%.0f";

	//Button 0
	banks[i_overdrive].but[0].name=	"Active";
	banks[i_overdrive].but[0].status=	1;
	banks[i_overdrive].but[0].value=	0;

	//Button 1
	banks[i_overdrive].but[1].name=	"";
	banks[i_overdrive].but[1].status=	0;
	banks[i_overdrive].but[1].value=	0;

	//Button 2
	banks[i_overdrive].but[2].name=	"";
	banks[i_overdrive].but[2].status=	0;
	banks[i_overdrive].but[2].value=		0;

	//Button 3
	banks[i_overdrive].but[3].name=	"";
	banks[i_overdrive].but[3].status=	0;
	banks[i_overdrive].but[3].value=	0;

	/*
			Bank 8: Reverb
	*/
	banks[i_reverb].name=			"Reverb";
	banks[i_reverb].id=				10;
	banks[i_reverb].status=			1;

	//Encoder 0
	banks[i_reverb].enc[0].name=		"Dry/Wet";
	banks[i_reverb].enc[0].status=	1;
	banks[i_reverb].enc[0].value=		50;
	banks[i_reverb].enc[0].min=		0;
	banks[i_reverb].enc[0].max=		100;
	banks[i_reverb].enc[0].step=		1;
	banks[i_reverb].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_reverb].enc[1].name=	"Size";
	banks[i_reverb].enc[1].status=	1;
	banks[i_reverb].enc[1].value=	50;
	banks[i_reverb].enc[1].min=		0;
	banks[i_reverb].enc[1].max=		100;
	banks[i_reverb].enc[1].step=		1;
	banks[i_reverb].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_reverb].enc[2].name=		"Damp";
	banks[i_reverb].enc[2].status=	1;
	banks[i_reverb].enc[2].value=	50;
	banks[i_reverb].enc[2].min=		0;
	banks[i_reverb].enc[2].max=		100;
	banks[i_reverb].enc[2].step=		1;
	banks[i_reverb].enc[2].format=	"%.0f";

	//Button 0
	banks[i_reverb].but[0].name=	"Active";
	banks[i_reverb].but[0].status=	1;
	banks[i_reverb].but[0].value=	0;

	//Button 1
	banks[i_reverb].but[1].name=	"";
	banks[i_reverb].but[1].status=	0;
	banks[i_reverb].but[1].value=	0;

	//Button 2
	banks[i_reverb].but[2].name=	"";
	banks[i_reverb].but[2].status=	0;
	banks[i_reverb].but[2].value=		0;

	//Button 3
	banks[i_reverb].but[3].name=	"";
	banks[i_reverb].but[3].status=	0;
	banks[i_reverb].but[3].value=	0;

	/*
			Bank 11: Compressor
	*/
	banks[i_comp].name=			"Compressor";
	banks[i_comp].id=				11;
	banks[i_comp].status=			1;

	//Encoder 0
	banks[i_comp].enc[0].name=		"Threshold";
	banks[i_comp].enc[0].status=	1;
	banks[i_comp].enc[0].value=		-10;
	banks[i_comp].enc[0].min=		-40;
	banks[i_comp].enc[0].max=		0;
	banks[i_comp].enc[0].step=		1;
	banks[i_comp].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_comp].enc[1].name=	"Ratio";
	banks[i_comp].enc[1].status=	1;
	banks[i_comp].enc[1].value=	4;
	banks[i_comp].enc[1].min=		1;
	banks[i_comp].enc[1].max=		60;
	banks[i_comp].enc[1].step=		1;
	banks[i_comp].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_comp].enc[2].name=		"Attack";
	banks[i_comp].enc[2].status=	1;
	banks[i_comp].enc[2].value=	10;
	banks[i_comp].enc[2].min=		5;
	banks[i_comp].enc[2].max=		100;
	banks[i_comp].enc[2].step=		5;
	banks[i_comp].enc[2].format=	"%.0f";

	//Button 0
	banks[i_comp].but[0].name=	"Active";
	banks[i_comp].but[0].status=	1;
	banks[i_comp].but[0].value=	0;

	//Button 1
	banks[i_comp].but[1].name=	"";
	banks[i_comp].but[1].status=	0;
	banks[i_comp].but[1].value=	0;

	//Button 2
	banks[i_comp].but[2].name=	"";
	banks[i_comp].but[2].status=	0;
	banks[i_comp].but[2].value=		0;

	//Button 3
	banks[i_comp].but[3].name=	"";
	banks[i_comp].but[3].status=	0;
	banks[i_comp].but[3].value=	0;

	/*
			Bank 12: Tremolo
	*/
	banks[i_tremolo].name=			"Tremolo";
	banks[i_tremolo].id=				12;
	banks[i_tremolo].status=			1;

	//Encoder 0
	banks[i_tremolo].enc[0].name=		"Depth";
	banks[i_tremolo].enc[0].status=	1;
	banks[i_tremolo].enc[0].value=		50;
	banks[i_tremolo].enc[0].min=		0;
	banks[i_tremolo].enc[0].max=		100;
	banks[i_tremolo].enc[0].step=		1;
	banks[i_tremolo].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_tremolo].enc[1].name=	"Freq.";
	banks[i_tremolo].enc[1].status=	1;
	banks[i_tremolo].enc[1].value=	10;
	banks[i_tremolo].enc[1].min=		0;
	banks[i_tremolo].enc[1].max=		20;
	banks[i_tremolo].enc[1].step=		1;
	banks[i_tremolo].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_tremolo].enc[2].name=		"Type";
	banks[i_tremolo].enc[2].status=	1;
	banks[i_tremolo].enc[2].value=	1;
	banks[i_tremolo].enc[2].min=		0;
	banks[i_tremolo].enc[2].max=		2;
	banks[i_tremolo].enc[2].step=		1;
	banks[i_tremolo].enc[2].format=	"%.0f";

	//Button 0
	banks[i_tremolo].but[0].name=	"Active";
	banks[i_tremolo].but[0].status=	1;
	banks[i_tremolo].but[0].value=	0;

	//Button 1
	banks[i_tremolo].but[1].name=	"";
	banks[i_tremolo].but[1].status=	0;
	banks[i_tremolo].but[1].value=	0;

	//Button 2
	banks[i_tremolo].but[2].name=	"";
	banks[i_tremolo].but[2].status=	0;
	banks[i_tremolo].but[2].value=		0;

	//Button 3
	banks[i_tremolo].but[3].name=	"";
	banks[i_tremolo].but[3].status=	0;
	banks[i_tremolo].but[3].value=	0;

	/*
			Bank 13: Rotary
	*/
	banks[i_rotary].name=			"Rotary";
	banks[i_rotary].id=				13;
	banks[i_rotary].status=			1;

	//Encoder 0
	banks[i_rotary].enc[0].name=		"Depth";
	banks[i_rotary].enc[0].status=	1;
	banks[i_rotary].enc[0].value=		50;
	banks[i_rotary].enc[0].min=		0;
	banks[i_rotary].enc[0].max=		100;
	banks[i_rotary].enc[0].step=		1;
	banks[i_rotary].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_rotary].enc[1].name=	"Freq.";
	banks[i_rotary].enc[1].status=	1;
	banks[i_rotary].enc[1].value=	10;
	banks[i_rotary].enc[1].min=		0;
	banks[i_rotary].enc[1].max=		24;
	banks[i_rotary].enc[1].step=		1;
	banks[i_rotary].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_rotary].enc[2].name=		"";
	banks[i_rotary].enc[2].status=	0;
	banks[i_rotary].enc[2].value=	1;
	banks[i_rotary].enc[2].min=		0;
	banks[i_rotary].enc[2].max=		2;
	banks[i_rotary].enc[2].step=		1;
	banks[i_rotary].enc[2].format=	"%.0f";

	//Button 0
	banks[i_rotary].but[0].name=	"Active";
	banks[i_rotary].but[0].status=	1;
	banks[i_rotary].but[0].value=	0;

	//Button 1
	banks[i_rotary].but[1].name=	"";
	banks[i_rotary].but[1].status=	0;
	banks[i_rotary].but[1].value=	0;

	//Button 2
	banks[i_rotary].but[2].name=	"";
	banks[i_rotary].but[2].status=	0;
	banks[i_rotary].but[2].value=		0;

	//Button 3
	banks[i_rotary].but[3].name=	"";
	banks[i_rotary].but[3].status=	0;
	banks[i_rotary].but[3].value=	0;

	/*
			Bank 14: Flanger
	*/
	banks[i_flanger].name=			"Flanger";
	banks[i_flanger].id=				14;
	banks[i_flanger].status=			1;

	//Encoder 0
	banks[i_flanger].enc[0].name=		"Dry/Wet";
	banks[i_flanger].enc[0].status=	1;
	banks[i_flanger].enc[0].value=		50;
	banks[i_flanger].enc[0].min=		0;
	banks[i_flanger].enc[0].max=		100;
	banks[i_flanger].enc[0].step=		1;
	banks[i_flanger].enc[0].format=	"%.0f";

	//Encoder 1
	banks[i_flanger].enc[1].name=	"Freq.";
	banks[i_flanger].enc[1].status=	1;
	banks[i_flanger].enc[1].value=	10;
	banks[i_flanger].enc[1].min=		0;
	banks[i_flanger].enc[1].max=		24;
	banks[i_flanger].enc[1].step=		1;
	banks[i_flanger].enc[1].format=	"%.0f";

	//Encoder 2
	banks[i_flanger].enc[2].name=		"Feedback";
	banks[i_flanger].enc[2].status=	1;
	banks[i_flanger].enc[2].value=	50;
	banks[i_flanger].enc[2].min=		0;
	banks[i_flanger].enc[2].max=		100;
	banks[i_flanger].enc[2].step=		1;
	banks[i_flanger].enc[2].format=	"%.0f";

	//Button 0
	banks[i_flanger].but[0].name=	"Active";
	banks[i_flanger].but[0].status=	1;
	banks[i_flanger].but[0].value=	0;

	//Button 1
	banks[i_flanger].but[1].name=	"";
	banks[i_flanger].but[1].status=	0;
	banks[i_flanger].but[1].value=	0;

	//Button 2
	banks[i_flanger].but[2].name=	"";
	banks[i_flanger].but[2].status=	0;
	banks[i_flanger].but[2].value=		0;

	//Button 3
	banks[i_flanger].but[3].name=	"";
	banks[i_flanger].but[3].status=	0;
	banks[i_flanger].but[3].value=	0;

	/*
			Bank 15: Autowah
	*/
	banks[i_autowah].name=				"Auto-Wah";
	banks[i_autowah].id=				15;
	banks[i_autowah].status=			1;

	//Encoder 0
	banks[i_autowah].enc[0].name=		"Depth";
	banks[i_autowah].enc[0].status=		1;
	banks[i_autowah].enc[0].value=		50;
	banks[i_autowah].enc[0].min=		0;
	banks[i_autowah].enc[0].max=		100;
	banks[i_autowah].enc[0].step=		1;
	banks[i_autowah].enc[0].format=		"%.0f";

	//Encoder 1
	banks[i_autowah].enc[1].name=		"Freq.";
	banks[i_autowah].enc[1].status=		1;
	banks[i_autowah].enc[1].value=		1;
	banks[i_autowah].enc[1].min=		0.1;
	banks[i_autowah].enc[1].max=		5;
	banks[i_autowah].enc[1].step=		0.1;
	banks[i_autowah].enc[1].format=		"%.1f";

	//Encoder 2
	banks[i_autowah].enc[2].name=		"Quality";
	banks[i_autowah].enc[2].status=		1;
	banks[i_autowah].enc[2].value=		1;
	banks[i_autowah].enc[2].min=		0.3;
	banks[i_autowah].enc[2].max=		5;
	banks[i_autowah].enc[2].step=		0.1;
	banks[i_autowah].enc[2].format=		"%.1f";

	//Button 0
	banks[i_autowah].but[0].name=		"Active";
	banks[i_autowah].but[0].status=		1;
	banks[i_autowah].but[0].value=		0;

	//Button 1
	banks[i_autowah].but[1].name=		"";
	banks[i_autowah].but[1].status=		0;
	banks[i_autowah].but[1].value=		0;

	//Button 2
	banks[i_autowah].but[2].name=		"";
	banks[i_autowah].but[2].status=		0;
	banks[i_autowah].but[2].value=		0;

	//Button 3
	banks[i_autowah].but[3].name=		"";
	banks[i_autowah].but[3].status=		0;
	banks[i_autowah].but[3].value=		0;
}



#ifdef __cplusplus
}
#endif


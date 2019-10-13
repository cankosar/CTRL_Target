/*
 * dsp_control.c
 *
 *  Created on: 28.04.2019
 *      Author: Can
 */

#include "main.h"
#include "math.h"
#include "stm32f7xx_hal.h"
#include "GUI_control.h"
//#include "dsp_control.h"

float fs=48000;


void write_bqf_param(uint16_t *offset, uint8_t *type, float *G, float *Fc, float *Q ){


//	printf("b0:%f, type:%d, G=%f, Fc:%f, Q:%f\n",ctrlreg_tx[*offset+1].f32, *type, *G, *Fc, *Q);

	double A,w0,cosw0,sinw0,alpha,a0;

	//Intermediate vars
	A=pow(10,(*G)/40);
	w0=2*M_PI *((*Fc)/fs);
	cosw0=cos(w0);
	sinw0=sin(w0);
	alpha=sinw0/(2*(*Q));

	switch(*type){

		case 0: //Lowpass filter
//			printf("Low pass\n");
			a0=1+alpha;
			ctrlreg_tx[*offset+0].f32=(float)((1-cosw0)*0.5/a0);
			ctrlreg_tx[*offset+1].f32=(float)((1-cosw0)/a0);
			ctrlreg_tx[*offset+2].f32=(float)((1-cosw0)*0.5/a0);
//			bqf[fid].a[0]=1;
			ctrlreg_tx[*offset+3].f32=(float)((-2*cosw0)/a0);
			ctrlreg_tx[*offset+4].f32=(float)((1-alpha)/a0);
			break;

		case 1: //Highpass filter
//			printf("Highpass\n");
			a0=1+alpha;
			ctrlreg_tx[*offset+0].f32=(float)((1+cosw0)*0.5/a0);
			ctrlreg_tx[*offset+1].f32=(float)(-(1+cosw0)/a0);
			ctrlreg_tx[*offset+2].f32=(float)((1+cosw0)*0.5/a0);
//			bqf[fid].a[0]=1;
			ctrlreg_tx[*offset+3].f32=(float)(-2*cosw0/a0);
			ctrlreg_tx[*offset+4].f32=(float)((1-alpha)/a0);
			break;
		case 2: //Peak filter
//			printf("Peak filter\n");
			a0=1+alpha/A;
			ctrlreg_tx[*offset+0].f32=(float)((1+alpha*A)/a0);
			ctrlreg_tx[*offset+1].f32=(float)((-2*cosw0)/a0);
			ctrlreg_tx[*offset+2].f32=(float)((1-alpha*A)/a0);
//			bqf[fid].a[0]=1;
			ctrlreg_tx[*offset+3].f32=(float)((-2*cosw0)/a0);
			ctrlreg_tx[*offset+4].f32=(float)((1-alpha/A)/a0);
			break;
		case 3: //Low shelf filter
//			printf("Low shelf filter\n");
			a0=(A+1)+(A-1)*cosw0+2*sqrt(A)*alpha;
			ctrlreg_tx[*offset+0].f32=(float)((A*((A+1)-(A-1)*cosw0+2*sqrt(A)*alpha))/a0);
			ctrlreg_tx[*offset+1].f32=(float)((2*A*((A-1)-(A+1)*cosw0))/a0);
			ctrlreg_tx[*offset+2].f32=(float)((A*((A+1)-(A-1)*cosw0-2*sqrt(A)*alpha))/a0);
//			bqf[fid].a[0]=1;
			ctrlreg_tx[*offset+3].f32=(float)((-2*((A-1)+(A+1)*cosw0))/a0);
			ctrlreg_tx[*offset+4].f32=(float)(((A+1)+(A-1)*cosw0-2*sqrt(A)*alpha)/a0);
			break;
		case 4:
//			printf("High shelf filter\n");
			a0=(A+1)-(A-1)*cosw0+2*sqrt(A)*alpha;
			ctrlreg_tx[*offset+0].f32=(float)((A*((A+1)+(A-1)*cosw0+2*sqrt(A)*alpha))/a0);
			ctrlreg_tx[*offset+1].f32=(float)((-2*A*((A-1)+(A+1)*cosw0))/a0);
			ctrlreg_tx[*offset+2].f32=(float)((A*((A+1)+(A-1)*cosw0-2*sqrt(A)*alpha))/a0);
//			ctrlreg_tx[*offset+0].f32=1;
			ctrlreg_tx[*offset+3].f32=(float)((2*((A-1)-(A+1)*cosw0))/a0);
			ctrlreg_tx[*offset+4].f32=(float)(((A+1)-(A-1)*cosw0-2*sqrt(A)*alpha)/a0);
			break;
	}


//	printf("b0:%f\t b1:%f\t b2:%f\t a1:%f\t a2:%f\n",ctrlreg_tx[*offset].f32,ctrlreg_tx[*offset+1].f32,ctrlreg_tx[*offset+2].f32,ctrlreg_tx[*offset+3].f32,ctrlreg_tx[*offset+4].f32);


}

void update_chorus(void){

	uint16_t offset=menu[bank].ctrl_offset;
	ctrlreg_tx[offset+0].f32=(float)menu[bank].enc[0].value*0.01; 		//Wet mix
	ctrlreg_tx[offset+1].f32=1-ctrlreg_tx[offset+0].f32;					//Dry mix
	ctrlreg_tx[offset+2].f32=(float)menu[bank].enc[1].value;			//Depth
	ctrlreg_tx[offset+3].f32=(float)10-menu[bank].enc[2].value;		//Rate
}

void update_delay(void){
	uint16_t offset=menu[bank].ctrl_offset;
	ctrlreg_tx[offset+0].f32=(float)menu[bank].enc[0].value*0.01; 		//Wet mix
	ctrlreg_tx[offset+1].f32=1-ctrlreg_tx[offset+0].f32;					//Dry mix
	ctrlreg_tx[offset+2].f32=(float)menu[bank].enc[1].value*0.01;		//Feedback
	ctrlreg_tx[offset+3].f32=(float)menu[bank].enc[2].value*0.001;		//Time in ms
}

void update_overdrive(void){
	uint16_t offset=menu[bank].ctrl_offset;
	ctrlreg_tx[offset+0].f32=(float)1+menu[bank].enc[0].value*menu[bank].enc[0].value;		//Gain
	ctrlreg_tx[offset+1].f32=(float)1.5-menu[bank].enc[0].value*0.1;	//Attenuation (Convert it to a correction gain)

	if(HP_old!=menu[bank].enc[1].value){
		//High pass variables
		uint16_t HP_offset=offset+2;		//Offset of ctrlreg_tx to write
		uint8_t HP_type=1;					//High pass
		float HP_G=-10;						//Gain
		float HP_F=menu[bank].enc[1].value;	//Frequency
		float HP_Q=0.7;						//Quality
		write_bqf_param(&HP_offset, &HP_type,&HP_G,&HP_F,&HP_Q);
	}
	HP_old=menu[bank].enc[1].value;

	if(LP_old!=menu[bank].enc[2].value){
		//Low pass variables
		uint16_t LP_offset=offset+7;		//Offset of ctrlreg_tx to write
		uint8_t LP_type=0;					//High pass
		float LP_G=-10;						//Gain
		float LP_F=menu[bank].enc[2].value;	//Frequency
		float LP_Q=0.7;						//Quality
		write_bqf_param(&LP_offset, &LP_type,&LP_G,&LP_F,&LP_Q);
	}
	LP_old=menu[bank].enc[2].value;

}

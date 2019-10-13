/*
 * tuner.c
 *
 *  Created on: 07.09.2019
 *      Author: Can
 */

#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include <stdlib.h>
#include "HW_handlers.h"
#include "HW_config.h"
#include "display.h"
#include "math.h"
#include "tuner.h"
#include "dsp_control.h"

void calculate_note(double freq);
double calculate_cent(double f, double fr);
uint8_t find_note_index(double freq);

void visualize_cent(bool valid);

uint32_t cnt;

char *note;
uint8_t cents;
double pot;

#define num_notes 50

double note_bins[num_notes];
double notes[num_notes];

char *s_notes[] = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};
double act_cent;
char* act_note;


void update_tuner(void){

	//Declaration
	float freq;
	float freq_lower_limit=10;
	float freq_upper_limit=470;

	const uint8_t note_text_size=5;
	//Test freq.
//	freq=100+cnt;

	//Request the current note frequency from DSP
//	HAL_SPI_TransmitReceive(&hspi5, (uint8_t*) ctrlreg_tx, (uint8_t*) ctrlreg_rx, ctrl_len*4,10);

	freq=ctrlreg_rx[reg_f_tuner].f32;

//	printf("Freq:%.2f\n",freq);
	//Calculate notes and update the global register
	calculate_note(freq);

	//Print frequency

	printf("%f\n",freq);

	set_text_size(2);
	set_text_color(val_color,0);
	if(freq>freq_lower_limit && freq<freq_upper_limit ){
		print_num(freq,"%.1f Hz",5,12,DP_WIDTH/2,DP_HEIGHT/2+35);
	}else{
		print_num(freq," ",5,12,DP_WIDTH/2,DP_HEIGHT/2+35);
	}

	//Print Note
	set_text_size(note_text_size);
	set_text_color(desc_color,0);

	if(freq>freq_lower_limit && freq<freq_upper_limit ){
		print_static(act_note,DP_WIDTH/2+15,DP_HEIGHT/2,12);
	}else{
		print_static("-",DP_WIDTH/2+15,DP_HEIGHT/2,12);
	}

	//Show cent
	if(freq>freq_lower_limit && freq<freq_upper_limit ){
		visualize_cent(1);
	}else{
		visualize_cent(0);
	}

	cnt++;

}

/*Visualizing cent on the display*/
void visualize_cent(bool valid){

	//Declare
	int8_t n_col;	//Number of cent columns
	int8_t n;
	uint8_t line_offset_y=40;
	uint8_t block_width=15;
	uint8_t block_height=15;
	uint16_t match_color=calc_RGB565(75,100,75);

	uint16_t temp_color;

	//Number of columns
	n_col=(int8_t) round(act_cent/5);

//	printf("Actcent:%d\n",n_col);

	for(n=1;n<=10;n++){

		//Visualize columns

		//Set color of the column
		temp_color=calc_RGB565(100,100-n*10,100-10*n);

		if(valid){
			if (n_col>0){
	//			printf("Show pos\n");
				//Show positive columns
				if(n_col>=n){
					draw_hline(DP_WIDTH/2+(n-1)*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,temp_color);
				}else{
					draw_hline(DP_WIDTH/2+(n-1)*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);
				}

				//Hide negative columns
				draw_hline(DP_WIDTH/2-n*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);

			}else if(n_col<0){
	//			printf("Show neg\n");
				//Show negative columns
				if(n_col<=(-1*n)){
					draw_hline(DP_WIDTH/2-n*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,temp_color);
				}else{
					draw_hline(DP_WIDTH/2-n*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);
				}
				//Hide positive columns
				draw_hline(DP_WIDTH/2+(n-1)*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);

			}else{		//ncol==0 => Match
	//			printf("Show all\n");
				//Show both positive and negative columns
				if(n==1){
					draw_hline(DP_WIDTH/2-n*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,match_color);
					draw_hline(DP_WIDTH/2+(n-1)*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,match_color);
				}else{
					draw_hline(DP_WIDTH/2+(n-1)*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);
					draw_hline(DP_WIDTH/2-n*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);

				}

			}

		}else{
			draw_hline(DP_WIDTH/2+(n-1)*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);
			draw_hline(DP_WIDTH/2-n*block_width,DP_HEIGHT/2-line_offset_y,block_width,block_height,0);

		}

	}


}


void update_note_bins(double freq_A4){

//	printf("Note bins updating with f:%f\n",freq_A4);



	notes[0]=((double) freq_A4 / (double)16);
	note_bins[0]= notes[0] * pow((double) 2,(double) -1/24);		//A0 + 50cents


	uint8_t i;
	for(i=1;i<num_notes;i++){
		note_bins[i]=(double) note_bins[i-1]*root2_12;
		notes[i]=(double) notes[i-1]*root2_12;
//		printf("i:%d \t  %.3f\n",i, note_bins[i]);
	}
	//Test
//	uint16_t n;
//	for(n=20;n<500;n+=5){
//		calculate_note((double)n);
//
//	}
//
//	printf("Ready\n");

}

//Calculate note and update actual note register
void calculate_note(double freq){

	//Declarations
	uint8_t note_index;

	//Get the note bin (lower border)
	note_index = find_note_index(freq);

	//Get the name of the note
	act_note=s_notes[note_index%12];

	//Calculate the deviation of the current frequency from the aimed note in cents
	act_cent=calculate_cent(freq,notes[note_index]);

//	printf("f:%.2f \t [%.2f - %.2f] \t %s %f\n",(float)freq, note_bins[note_index],note_bins[note_index+1],act_note,act_cent);
}

/*Calculate cent*/
double calculate_cent(double f, double fr){

	//Calculate cents
	return 1200*log2(f/fr);
}


/*Modified binary search*/
uint8_t find_note_index(double freq){

	//Declaration
	uint8_t l,r,c;

	//Start values
	l=0;
	r=num_notes;
	c=floor((l+r)/2);

	//Binary search algorithm
	while((r-l)>1){

		if(freq>=note_bins[c]){
			l=c;
		}else{
			r=c;
		}

		c=floor((l+r)/2);
	}

	return c;
}

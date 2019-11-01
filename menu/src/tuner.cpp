/*
 * tuner.cpp
 *
 *  Created on: 26.10.2019
 *      Author: Can
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "math.h"
#include "../inc/tuner.hpp"
#include "../../GUI/inc/GUI.hpp"
#include "../../com/inc/com_ctrl.hpp"

extern c_GUI GUI;
extern c_com_ctrl com;

void c_tuner::init(void){

	root2_12=pow((double) 2,(double) 1/12);

	freq=220;
}


void c_tuner::update(void){

	//Request the current note frequency from DSP
	freq=com.request_tuner_value();

	//Calculate notes and update the global register
	calculate_note(freq);

//	printf("Note:%s \t Cent: %f\n",act_note, act_cent);

	//Show cent
	if(freq>freq_lower_limit && freq<freq_upper_limit ){
		GUI.update_frequency(freq);
		GUI.update_note(act_note);
		GUI.visualize_cent(1,act_cent);
	}else{
		GUI.update_frequency(0);
		GUI.update_note("-");
		GUI.visualize_cent(0,act_cent);
	}

	//Dummy
	freq+=1;


}


void c_tuner::update_note_bins(double freq_A4){

	notes[0]=((double) freq_A4 / (double)16);
	note_bins[0]= notes[0] * pow((double) 2,(double) -1/24);		//A0 + 50cents


	uint8_t i;
	for(i=1;i<num_notes;i++){
		note_bins[i]=(double) note_bins[i-1]*root2_12;
		notes[i]=(double) notes[i-1]*root2_12;
	}
}

//Calculate note and update actual note register
void c_tuner::calculate_note(double freq){

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
double c_tuner::calculate_cent(double f, double fr){

	//Calculate cents
	return 1200*log2(f/fr);
}


/*Modified binary search*/
uint8_t c_tuner::find_note_index(double freq){

//	printf("Note %f\n",freq);
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




#ifdef __cplusplus
}
#endif

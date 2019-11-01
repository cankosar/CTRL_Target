/*
 * tuner.hpp
 *
 *  Created on: 26.10.2019
 *      Author: Can
 */

#ifndef INC_TUNER_HPP_
#define INC_TUNER_HPP_

#include "stm32f7xx_hal.h"

class c_tuner{

	public:
		void init(void);
		void update(void);
		void update_note_bins(double freq_A4);
		void calculate_note(double freq);
		double calculate_cent(double f, double fr);
		uint8_t find_note_index(double freq);


	private:

		//Declaration of frequency boundries
		float freq;
		const float freq_lower_limit=10;
		const float freq_upper_limit=470;
		const uint8_t note_text_size=5;

		double act_cent;
		const char* act_note;

		static const uint8_t num_notes=50;
		double note_bins[num_notes];
		double notes[num_notes];

		double root2_12;
		const char *s_notes[12] = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};


};


#endif /* INC_TUNER_HPP_ */

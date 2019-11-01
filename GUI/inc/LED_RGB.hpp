/*
 * LED_RGB.hpp
 *
 *  Created on: 27.10.2019
 *      Author: Can
 */

#ifndef INC_LED_RGB_HPP_
#define INC_LED_RGB_HPP_

class c_LED_RGB{

	public:
		void init(void);
		void set_color(void);
		void mute(bool flag);
		void error(bool flag);
		void dsp(bool flag);

	private:

		void update_status(void);

		void reset(void);

		bool r,g,b;

		bool mute_status;
		bool dsp_status;
		bool error_status;
};



#endif /* INC_LED_RGB_HPP_ */

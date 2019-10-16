/*
 * main.c
 *
 *  Created on: 20.04.2019
 *      Author: Can
 */

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "../hw/inc/sysconfigs.hpp"
#include "../GUI/inc/GUI.hpp"

c_sysconfig sysconfig;

c_GUI GUI;

//Main routine
int main(void)
{

	//Init system configurations
	sysconfig.init();

	//Init GUI
	GUI.init();

	//Start GUI
	GUI.start();

}

#ifdef __cplusplus
}
#endif

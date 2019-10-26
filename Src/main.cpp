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
#include "../menu/inc/menu.hpp"

c_sysconfig sysconfig;

c_GUI GUI;

extern c_menu menu;

//Main routine
int main(void)
{

	//Init system configurations
	sysconfig.init();

	//Init GUI
	GUI.init();

	//Init menu
	menu.init();

	//Start GUI
	GUI.start();

}

#ifdef __cplusplus
}
#endif

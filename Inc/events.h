/*
 * events.h
 *
 *  Created on: 10.08.2019
 *      Author: Can
 */

#ifndef EVENTS_H_
#define EVENTS_H_

//Function declarations
#include "stdbool.h"

void init_events(void);
void capture_events(void);
void evm(void);
void test_counter(uint8_t type, uint8_t id, int16_t val);
void tuner_handler(void);

//Capture status
bool capture_status;

//Tuner
bool tnr_update;	//Tuner update flag
bool tuner_update_lock;
#endif /* EVENTS_H_ */


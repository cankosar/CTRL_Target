/*
 * global_app.h
 *
 *  Created on: 20.04.2019
 *      Author: Can
 */

#ifndef GUI_CONTROL_H_
#define GUI_CONTROL_H_

#include <string.h>
#include "display.h"
#include "dsp_control.h"

extern uint8_t bank;
extern uint8_t n_context;
extern uint8_t init_success;
//extern union ctrltypes;

void update_encoder(uint8_t eid, int diff);
float update_encoder_item(uint8_t eid, int diff);
void update_encoder_value(uint8_t eid);
void update_button_value(uint8_t bid);
void update_button(uint8_t bid);
uint32_t update_active_bits(uint8_t id, uint8_t type);

void init_menu(void);
void update_context(void);
void update_ui_context(int diff);
void update_display(void);
int modulo(int x,int n);
void update_dsp(uint8_t id, uint8_t type);
void update_settings(uint8_t id, uint8_t type);
void init_settings(void);
float vol2logvol(float linvol);


//DSP & Communication
void update_bqf(uint8_t type);
void write_bqf_param(uint16_t *offset, uint8_t *type, float *G, float *Fc, float *Q );
void update_chorus(void);
void update_delay(void);
void update_overdrive(void);
//void trigger_com(void);
void send_update(uint8_t bank_id, uint8_t type, uint8_t ctrl_id, union ctrltypes w1, union ctrltypes w2, union ctrltypes w3, union ctrltypes w4, union ctrltypes w5);
void save_settings_nv(void);

//DSP and mute
void toggle_dsp(void);
void toggle_mute(void);
void update_led(void);

//Tuner
void init_tuner(void);
void deinit_tuner(void);


#define n_context 7

struct encoder{
	char name[16];
	bool state;				//1: Active, 0: Inactive
	float value;			//Current value
	float lower_limit;		//Lower limit of the field
	float upper_limit;		//Upper limit of the field
	float step_size;		//Step size
	char format[8];
};

struct button{
	char name[16];
	bool state;		//1: Active, 0: Inactive
	bool value;		//Current value: 0=>Off, 1=>On
};

struct context{
	char name[16];
	uint8_t fid;
	uint16_t ctrl_offset;
	struct button but[4];
	struct encoder enc[3];
};

struct context menu[n_context];

//Mute and DSP states
bool mute_state,DSP_state;

//Backup RAM
#define BKPSRAM_HWCHECK_OFFSET 0x0
#define BKPSRAM_HASHCHECK_OFFSET 0x2
#define BKPSRAM_BANK_OFFSET 0x4
#define BKPSRAM_MENU_HASH_OFFSET 0x8
#define SRAM_HWCHECK 1234
#define CHECKHASH 5678

#endif /* GUI_CONTROL_H_ */

//Tuner
#define tuner_bank 31

/* Includes ------------------------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32f7xx_it.h"
#include "HW_config.h"
#include "GUI_control.h"
#include "events.h"
#include "tuner.h"

//Setting header variables
//Event triggers
bool UI_updated;
//Button update table
uint8_t t_but_update;
//Encoder update table
uint8_t t_enc_update;
//FIFO register for encoders
int8_t enc_fifo[4];

//Gray code register for encoders
uint8_t enc_greycode[4];

//LUT counter value
uint8_t ctr=0;
//Look up table for counting up and down
int8_t lut[]={0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};

//Buttons
uint32_t tic[6];
uint16_t t_debounce=10;
uint8_t release[6];;
uint8_t key_debounced[6];
uint8_t but_trig=0;

//Process lock
bool P_LOCK;

int16_t enc[4];
uint8_t but[6];


void init_events(void){

	//Process lock on
	P_LOCK=1;

	//Event triggers
	UI_updated=0;
	//Button update table
	t_but_update=0;
	//Encoder update table
	t_enc_update=0;

	//Port&Pins for encoder 0
	enc_GPIO_Port[0][0]=ENC0A_PORT;
	enc_GPIO_Pin[0][0]=ENC0A_PIN;
	enc_GPIO_Port[0][1]=ENC0B_PORT;
	enc_GPIO_Pin[0][1]=ENC0B_PIN;

	//Port&Pins for encoder 1
	enc_GPIO_Port[1][0]=ENC1A_PORT;
	enc_GPIO_Pin[1][0]=ENC1A_PIN;
	enc_GPIO_Port[1][1]=ENC1B_PORT;
	enc_GPIO_Pin[1][1]=ENC1B_PIN;

	//Port&Pins for encoder 2
	enc_GPIO_Port[2][0]=ENC2A_PORT;
	enc_GPIO_Pin[2][0]=ENC2A_PIN;
	enc_GPIO_Port[2][1]=ENC2B_PORT;
	enc_GPIO_Pin[2][1]=ENC2B_PIN;

	//Port&Pins for encoder 3
	enc_GPIO_Port[3][0]=ENC3A_PORT;
	enc_GPIO_Pin[3][0]=ENC3A_PIN;
	enc_GPIO_Port[3][1]=ENC3B_PORT;
	enc_GPIO_Pin[3][1]=ENC3B_PIN;

	//Initialize grey codes of encoders
	for(int i=0;i<4;i++){
		//Evaluate grey code
		enc_greycode[i]=(HAL_GPIO_ReadPin(enc_GPIO_Port[i][0],enc_GPIO_Pin[i][0])<<1);
		enc_greycode[i]|=HAL_GPIO_ReadPin(enc_GPIO_Port[i][1],enc_GPIO_Pin[i][1]);
		enc_greycode[i]|=(HAL_GPIO_ReadPin(enc_GPIO_Port[i][0],enc_GPIO_Pin[i][0])<<3);
		enc_greycode[i]|=(HAL_GPIO_ReadPin(enc_GPIO_Port[i][0],enc_GPIO_Pin[i][0])<<2);
	}

	//Port&Pins for button 0
	but_GPIO_Port[0]=BUT0_PORT;
	but_GPIO_Pin[0]=BUT0_PIN;
	//Port&Pins for GPIOC 1
	but_GPIO_Port[1]=BUT1_PORT;
	but_GPIO_Pin[1]=BUT1_PIN;
	//Port&Pins for button 2
	but_GPIO_Port[2]=BUT2_PORT;
	but_GPIO_Pin[2]=BUT2_PIN;
	//Port&Pins for button 3
	but_GPIO_Port[3]=BUT3_PORT;
	but_GPIO_Pin[3]=BUT3_PIN;
	//Port&Pins for button 4
	but_GPIO_Port[4]=BUT4_PORT;
	but_GPIO_Pin[4]=BUT4_PIN;
	//Port&Pins for button 5
	but_GPIO_Port[5]=BUT5_PORT;
	but_GPIO_Pin[5]=BUT5_PIN;

	P_LOCK=0;

}

void capture_events(void){


	if(capture_status){
	//Capture encoders
		for(int i=0;i<4;i++){
			//Evaluate grey code
			enc_greycode[i]=0b00001100&(enc_greycode[i]<<2);	//Shift to left by 2
			enc_greycode[i]=enc_greycode[i]|(HAL_GPIO_ReadPin(enc_GPIO_Port[i][0],enc_GPIO_Pin[i][0])<<1);		//Put the first pin value to the second place from right
			enc_greycode[i]=enc_greycode[i]|HAL_GPIO_ReadPin(enc_GPIO_Port[i][1],enc_GPIO_Pin[i][1]);			//Put the first pin value to the right

			//Get the counter value of the grey code counter
			ctr=lut[enc_greycode[i]];

			//Take action if any changes
			if(ctr!=0){
				enc_fifo[i]=enc_fifo[i]+ctr;
	//			printf("Update enc %d:%d\n",i,enc_fifo[i]);
				//Save the encoders which are affected
				t_enc_update=t_enc_update|(1<<i);
				//Set GUI update
				UI_updated=1;
			}
		}

		//Capture buttons
		for(int k=0;k<6;k++){
			//Debounce
			if(!HAL_GPIO_ReadPin(but_GPIO_Port[k],but_GPIO_Pin[k])){	//If button pressed (polarity high)
			  tic[k]=HAL_GetTick();										//Set counter start
			  release[k]=1;												//Release lock
			}else if(release[k]&&HAL_GetTick()>tic[k]+t_debounce){		//If release time filled
			  key_debounced[k]=1;										//Set key debounced flag
			  release[k]=0;												//Unrelease
			}

			//Action
			if(key_debounced[k]){										//If debounced
			  t_but_update=t_but_update|(1<<k);							//Update corresponding button flag
	//		  printf("Button %d update\n",k);
			  key_debounced[k]=0;										//Unset debounced flag
			  UI_updated=1;												//Set updated flag
			}
		}


	}
}


/*Main event manager*/
void evm(void){

	uint8_t last_but_id;
	uint8_t last_enc_id;
	int8_t getval;

	//UI processing
	if(!P_LOCK){									//Check if there's a process lock
		if(UI_updated){								//Check if there's an update
			P_LOCK=1;								//Set process lock
			UI_updated=0;							//Raise down UI updated flag

			//Get encoder number
			for(int i=0;i<4;i++){
				if(t_enc_update&(1<<i)){
					t_enc_update=0;					//Raise down encoder updated flags
					getval=enc_fifo[i];				//Write down the value in FIFO...
					enc_fifo[i]=0;					//...and reset it.
					last_enc_id=i;					//Encoder id

				/*******BEGIN Process encoder changes********/
				if(last_enc_id==3){					//Enc ID 3 is context encoder
					update_ui_context(getval);
				}else{
					update_encoder(last_enc_id,getval);
				}
//				test_counter(1,last_enc_id,getval);
				/*******END Process encoder changes********/



				last_enc_id=0;							//Unset last button id
				break;
				}
			}

			//Get button number
			for(int i=0;i<6;i++){
				if(t_but_update&(1<<i)){
					t_but_update=0;					//Raise down button updated flags
					last_but_id=i;					//Button id

					/*******BEGIN Process button changes********/
					if(last_but_id==4){
						toggle_dsp();
					}else if(last_but_id==5){
						toggle_mute();
					}else{
						update_button(last_but_id);
					}

					//test_counter(0,last_but_id,0);
					/*******END Process button changes********/

					//last_but_id=0;						//Unset last button id //Obsolete
					break;
				}
			}
		}



		P_LOCK=0;									//Unset process lock
	}


	//Tuner processing
	if(mute_state && !tuner_update_lock){				//Mute active=>Turn on tuner
		if(tnr_update){									//Tuner update request on
			tuner_update_lock=1;						//Lock tuner update
			update_tuner();								//Update tuner
			tnr_update=0;								//Raise down the tuner update request
			tuner_update_lock=0;						//Unlock tuner update
		}
	}
}


void tuner_handler(void){
	//Raise tuner update flag
	tnr_update=1;
}

//void test_counter(uint8_t type, uint8_t id, int16_t val){
//
//	if(type){//Encoder
//		enc[id]+=val;
//	}else{//Button
//		but[id]=!but[id];
//	}
//
////	printf("Count\n");
//	printf("E0:%d E1:%d E2:%d E3:%d B0:%d B1:%d B2:%d B3:%d B4:%d B5:%d \n",enc[0],enc[1],enc[2],enc[3],but[0],but[1],but[2],but[3],but[4],but[5]);
//	HAL_Delay(1000);
//}




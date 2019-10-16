/*
 * evm.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "../inc/evm.hpp"
#include "../inc/evm_common.hpp"
//#include "../../hw/inc/HW_handlers.hpp"

//GPIO sockets of encoders
extern GPIO_TypeDef* enc_GPIO_Port[n_enc][2];
extern uint16_t enc_GPIO_Pin[n_enc][2];

//GPIO sockets of buttons
extern GPIO_TypeDef* but_GPIO_Port[n_but];
extern uint16_t but_GPIO_Pin[n_but];


void c_evm::capture(void){


	if(capture_status){
	//Capture encoders
		for(int i=0;i<n_enc;i++){
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
		for(int k=0;k<n_but;k++){
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


void c_evm::process(void){

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
//					update_ui_context(getval);
				}else{
//					update_encoder(last_enc_id,getval);
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
//						toggle_dsp();
					}else if(last_but_id==5){
//						toggle_mute();
					}else{
//						update_button(last_but_id);
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
//			update_tuner();								//Update tuner
			tnr_update=0;								//Raise down the tuner update request
			tuner_update_lock=0;						//Unlock tuner update
		}
	}


}



#ifdef __cplusplus
}
#endif
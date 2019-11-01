/*
 * HW_config.h
 *
 *  Created on: 10.08.2019
 *      Author: Can
 */

#ifndef HW_CONFIG_HPP_
#define HW_CONFIG_HPP_

//Display SPI pins
#define DP_RST_PIN GPIO_PIN_8
#define DP_RST_PORT GPIOC
#define DP_CS_PIN GPIO_PIN_2
#define DP_CS_PORT GPIOD
#define DP_DC_PIN GPIO_PIN_9
#define DP_DC_PORT GPIOC

//PA Standby Pin
#define PA_Standby_PIN GPIO_PIN_12
#define PA_Standby_Port GPIOF

//LED Pins
#define LED_RGB_PORT GPIOA
#define LED_R_PIN GPIO_PIN_5
#define LED_G_PIN GPIO_PIN_6
#define LED_B_PIN GPIO_PIN_7

//Encoder pins
#define ENC0A_PORT GPIOG
#define ENC0A_PIN GPIO_PIN_14
#define ENC0B_PORT GPIOB
#define ENC0B_PIN GPIO_PIN_6

#define ENC1A_PORT GPIOF
#define ENC1A_PIN GPIO_PIN_15
#define ENC1B_PORT GPIOF
#define ENC1B_PIN GPIO_PIN_4

#define ENC2A_PORT GPIOC
#define ENC2A_PIN GPIO_PIN_2
#define ENC2B_PORT GPIOE
#define ENC2B_PIN GPIO_PIN_13

#define ENC3A_PORT GPIOF
#define ENC3A_PIN GPIO_PIN_14
#define ENC3B_PORT GPIOB
#define ENC3B_PIN GPIO_PIN_1

//Button pins
#define BUT0_PORT GPIOB
#define BUT0_PIN GPIO_PIN_0

#define BUT1_PORT GPIOB
#define BUT1_PIN GPIO_PIN_10

#define BUT2_PORT GPIOA
#define BUT2_PIN GPIO_PIN_0

#define BUT3_PORT GPIOE
#define BUT3_PIN GPIO_PIN_15

#define BUT4_PORT GPIOB
#define BUT4_PIN GPIO_PIN_11

#define BUT5_PORT GPIOE
#define BUT5_PIN GPIO_PIN_0


#define n_enc 4
#define n_but 6

#define n_enc_menu 3
#define n_but_menu 4

//Positions of the buttons
#define DX_ENC0 53
#define DX_ENC1 160
#define DX_ENC2 267

#define DX_BUT0 40
#define DX_BUT1 120
#define DX_BUT2 200
#define DX_BUT3 280

#endif /* HW_CONFIG_H_ */

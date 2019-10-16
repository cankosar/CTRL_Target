/*
 * ili9341.cpp
 *
 *  Created on: 16.10.2019
 *      Author: Can
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "../inc/ili9341.hpp"
#include "stm32f7xx_hal.h"
#include "../../hw/inc/HW_config.hpp"

extern SPI_HandleTypeDef hspi3;


void c_ili9341::init(void){

	//Initialize SPI connection
	MX_SPI3_Init();

	//Init ili9341 chip
	init_chip();


}

void c_ili9341::init_chip(void){

	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,(GPIO_PinState)1);// Reset Pin
	HAL_Delay(100);
	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,(GPIO_PinState)0);// Reset Pin
	HAL_Delay(100);
	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,(GPIO_PinState)1);// Reset Pin
	HAL_Delay(100);
	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,(GPIO_PinState)0);// CS Pin
	HAL_Delay(100);

	send_command(0xCB); //Power control A
	send_data(0x39);
	send_data(0x2C);
	send_data(0x00);
	send_data(0x34);
	send_data(0x02);

	send_command(0xCF);//Power control B
	send_data(0x00);
	send_data(0XC1);
	send_data(0X30);

	send_command(0xE8); //Driver timing control A
	send_data(0x85);
	send_data(0x00);
	send_data(0x78);

	send_command(0xEA); //Driver timing control A
	send_data(0x00);
	send_data(0x00);

	send_command(0xED); //Power on sequence control
	send_data(0x64);
	send_data(0x03);
	send_data(0X12);
	send_data(0X81);

	send_command(0xF7);  //Pump ratio control
	send_data(0x20);

	send_command(0xC0);  //Power control
	send_data(0b00001001);      //3,3V

	send_command(0xC1);  //Power control
	send_data(0x10);      //SAP[2:0];BT[3:0]

	send_command(0xC5);  //VCM control
	send_data(0x3e);
	send_data(0x28);

	send_command(0xC7);    //VCM control2
	send_data(0x86);

	send_command(0x36);    // Memory Access Control
	send_data(0b11111100);

	send_command(0x3A); //Pixel format
	send_data(0x55);

	send_command(0xB1); //Frame rate control
	send_data(0x00);
	send_data(0x18);

	send_command(0xB6);    // Display Function Control
	send_data(0x08);
	send_data(0x82);
	send_data(0x27);

	send_command(0xF2);    // 3Gamma Function Disable
	send_data(0x00);

	send_command(0x26);    //Gamma curve selected
	send_data(0x01);

	send_command(0xE0);    //Set Gamma
	send_data(0x0F);
	send_data(0x31);
	send_data(0x2B);
	send_data(0x0C);
	send_data(0x0E);
	send_data(0x08);
	send_data(0x4E);
	send_data(0xF1);
	send_data(0x37);
	send_data(0x07);
	send_data(0x10);
	send_data(0x03);
	send_data(0x0E);
	send_data(0x09);
	send_data(0x00);

	send_command(0XE1);    //Set Gamma
	send_data(0x00);
	send_data(0x0E);
	send_data(0x14);
	send_data(0x03);
	send_data(0x11);
	send_data(0x07);
	send_data(0x31);
	send_data(0xC1);
	send_data(0x48);
	send_data(0x08);
	send_data(0x0F);
	send_data(0x0C);
	send_data(0x31);
	send_data(0x36);
	send_data(0x0F);

	send_command(0x11);    //Exit Sleep
	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,(GPIO_PinState)1);// Reset Pin

	send_command(0x29);    //Display on
	send_command(0x2c);

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,(GPIO_PinState)1);// CS Pin

}

void c_ili9341::send_command(uint8_t cmd) {
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,(GPIO_PinState)0);// D/C Pin
	HAL_SPI_Transmit(&hspi3,&cmd,1,1000);
}

void c_ili9341::send_data(uint8_t data) {
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,(GPIO_PinState)1);// D/C Pin
	HAL_SPI_Transmit(&hspi3,&data,1,1000);
}

void c_ili9341::send_data16(uint16_t *pdata)
{

//	printf("Pointer: %d\t Content: %d\n",(int)pdata, *pdata);
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,(GPIO_PinState)1);// D/C Pin
	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata+1,1,1000);
	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata,1,1000);
//	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata,2,1000); //Reihenfolge andersherum
}

void c_ili9341::print_image( const uint8_t *ptr, unsigned width, unsigned height, unsigned x1, unsigned y1 ){

	unsigned idx;

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,(GPIO_PinState)0);// CS Pin lo

	set_address(x1, y1, x1 + width -1, y1 + height -1);
	idx = 0;
	while (idx < width*height*2)
	{
	send_data(*ptr++);
	idx++;
	}

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,(GPIO_PinState)1);// CS Pin hi



}

void c_ili9341::set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
//	printf("Address: x1:%d\tx2:%d\ty1:%d\ty2:%d\n",x1, x2,y1,y2);
   send_command(0x2a);
   send_data16(&x1);
   send_data16(&x2);

   send_command(0x2b);
   send_data16(&y1);
   send_data16(&y2);

   send_command(0x2C);
}

/* SPI3 init function */
void c_ili9341::MX_SPI3_Init(void)
{

	/* SPI3 parameter configuration*/
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 7;
	hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi3) != HAL_OK)
	{
	//    _Error_Handler(__FILE__, __LINE__);
	}

}

#ifdef __cplusplus
}
#endif

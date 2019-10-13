
//Includes
#include "main.h"
#include "stm32f7xx_hal.h"
//#include "demo.h"
#include "display.h"
#include "font.h"
#include "string.h"
#include "HW_handlers.h"
#include "HW_config.h"

//Global vars
int16_t cursor_x,cursor_y;
uint16_t textsize,textcolor,textbgcolor;


void send_command(uint8_t cmd) {
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,0);// D/C Pin
	HAL_SPI_Transmit(&hspi3,&cmd,1,1000);
}

void send_data(uint8_t data) {
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,1);// D/C Pin
	HAL_SPI_Transmit(&hspi3,&data,1,1000);
}

//union u_type            //Setup a Union
//{
//  uint16_t wrd;
//  uint8_t byt[2];
//}clr;                    //Assign a var name to the Union

void send_data16(uint16_t *pdata)
{

//	printf("Pointer: %d\t Content: %d\n",(int)pdata, *pdata);
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,1);// D/C Pin
	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata+1,1,1000);
	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata,1,1000);
//	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata,2,1000); //Reihenfolge andersherum
}

void send_data16rpt(uint16_t *pdata, uint32_t cnt)
{

//	printf("Pointer: %d\t Content: %d\n",(int)pdata, *pdata);
//	printf("Data:%d\tCount:%ld\n",*pdata,cnt);
	HAL_GPIO_WritePin(DP_DC_PORT,DP_DC_PIN,1);// D/C Pin
	while(cnt>0){
		HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata+1,1,1000);
		HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata,1,1000);
		cnt--;
	}
//	HAL_SPI_Transmit(&hspi3,(uint8_t*)pdata,2,1000); //Reihenfolge andersherum
}

void init_display(void){

	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,1);// Reset Pin
	HAL_Delay(100);
	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,0);// Reset Pin
	HAL_Delay(100);
	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,1);// Reset Pin
	HAL_Delay(100);
	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,0);// CS Pin
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
	HAL_GPIO_WritePin(DP_RST_PORT,DP_RST_PIN,1);// Reset Pin

	send_command(0x29);    //Display on
	send_command(0x2c);

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,1);// CS Pin

}


void show_image ( const uint8_t *ptr, unsigned width, unsigned height, unsigned x1, unsigned y1 )
{
  unsigned idx;
//  w = *ptr++;
//  h = *ptr++;
  //size_t n = sizeof(demo_image);
  //printf("Count: %d\n",n);

  HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,0);// CS Pin lo

  set_address(x1, y1, x1 + width -1, y1 + height -1);
//  printf("Height: %d\nWidth: %d\n",height,width);
  idx = 0;
  while (idx < width*height*2)
  {
    send_data(*ptr++);
    idx++;
  }
//  printf("Total item: %d\n",idx);

  HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,1);// CS Pin hi
}

void set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
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


void set_template(void)
{
	//Template
	desc_offset_y=15;
	val_offset_y=45;

	rot_offset[0]=53;
	rot_offset[1]=160;
	rot_offset[2]=267;

	but_offset[0]=40;
	but_offset[1]=120;
	but_offset[2]=200;
	but_offset[3]=280;

	desc_color=0xFFFF;
	val_color=0xAE3F;
	active_color=0xD7F8;
	inactive_color=0xFE38;

	//Offset central area
	ca_area_offset_x=0;
	ca_area_offset_y=70;

	//Line widths
	w_l_thick=3;
	w_l_thin=1;


	//Draw background
	draw_rect(0,0,DP_WIDTH,DP_HEIGHT,0);
	//Draw line template
	draw_hline(0,170,DP_WIDTH,3,65535);
	draw_hline(0,70,DP_WIDTH,3,65535);
	draw_vline(106,0,60,1,65535);
	draw_vline(212,0,60,1,65535);
	draw_vline(80,DP_HEIGHT,-60,1,65535);
	draw_vline(160,DP_HEIGHT,-60,1,65535);
	draw_vline(DP_HEIGHT,DP_HEIGHT,-60,1,65535);
}

void draw_vline(int16_t x1, int16_t y1, int16_t h, uint16_t t, uint16_t color)
{

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,0);// CS Pin lo
	if(h>0){
		set_address(x1, y1, x1 + t-1, y1+h-1);
		send_data16rpt(&color, ((uint32_t) t) * ((uint32_t) h));
	}else{
		set_address(x1, y1+h, x1 + t-1, y1-1);
		send_data16rpt(&color, ((uint32_t) t) * ((uint32_t) -h));
	}
	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,1);// CS Pin hi
}

void draw_hline(int16_t x1, int16_t y1, int16_t w, uint16_t t, uint16_t color)
{

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,0);// CS Pin lo
	if(w>0){
		set_address(x1, y1, x1 + w-1, y1+t-1);
		send_data16rpt(&color, ((uint32_t) t) * ((uint32_t) w));
	}else{
		set_address(x1 + w, y1, x1-1, y1+t-1);
		send_data16rpt(&color, ((uint32_t) t) * ((uint32_t) -w));
	}

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,1);// CS Pin hi
}

void draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,0);// CS Pin lo
	set_address(x, y, x + w - 1, y + h - 1);
	send_data16rpt(&color, ((uint32_t) w) * ((uint32_t) h));
	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,1);// CS Pin hi
}

void draw_char(int16_t x, int16_t y, unsigned char c, uint16_t fgcolor, uint16_t bgcolor, uint8_t size) {

	//This works by unrolling the drawRect code into here
//	printf("Address: %d %d %d %d\n",x, y, x + 6 * size - 1, y + 8 * size - 1);
	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,0);// CS Pin lo
	set_address(x, y, x + 6 * size - 1, y + 8 * size - 1);

	uint8_t mask = 0x01;
	uint16_t color;
	uint8_t yr;




	for (y = 0; y < 8; y++) {
		for (yr = 0; yr < size; yr++) {
			for (x = 0; x < 5; x++) {
				if (font[c * 5 + x] & mask) {
					color = fgcolor;
				} else {
					color = bgcolor;
				}
				//push pixels fast (this function has less overhead)
				send_data16rpt(&color,size);
			}
			send_data16rpt(&bgcolor,size);
		}
		mask = mask << 1;
	}

	HAL_GPIO_WritePin(DP_CS_PORT,DP_CS_PIN,1);// CS Pin hi
}

void print(char* c, uint16_t xm, uint16_t ym) {
//	printf("Size:%d\n",strlen(c));
	set_cursor(xm-3*textsize*strlen(c), ym-4*textsize);
	while (*c)
		write(*c++);
}

void print_static(char* c, uint16_t xm, uint16_t ym, uint8_t xsize) {

//	printf("String: \"%s\", Size: %d, Width:%d\n",c, strlen(c), xsize);
	set_cursor(xm-3*textsize*xsize, ym-4*textsize);

	//Fill the rest with spaces
	int8_t diff_total=xsize-strlen(c);
	int8_t prefill=diff_total/2;
	int8_t postfill=xsize-strlen(c)-prefill;

	int i;
	char* space=" ";
	for(i=0;i<prefill;i++){
		write(*space);
	}

	for(i=0;i<strlen(c);i++){
		write(c[i]);
	}

	for(i=0;i<postfill;i++){
		write(*space);
	}


}

void write(char c) {

	if (c == '\n') {
		cursor_y += textsize * 8;
		cursor_x = 0;
	} else {
		draw_char(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
		cursor_x += textsize * 6;
	}

}

void print_float(float val, char * format, uint8_t len, uint16_t xm, uint16_t ym)
{
	char buffer[len];
	snprintf(buffer, sizeof buffer, format, val);
	print(buffer,xm,ym);
}

void print_num(float val, char * format, uint8_t len, uint8_t width,uint16_t xm, uint16_t ym)
{

	char buffer[16];
	sprintf(buffer, format, val);
	print_static(buffer,xm,ym,width);

}



void print_int(int16_t val, char * format, uint8_t len, uint16_t xm, uint16_t ym)
{
	char buffer[len];
	snprintf(buffer, sizeof buffer, format, val);
	print(buffer,xm,ym);
}


void set_cursor(int16_t x, int16_t y) {
//	printf("Setting cursor to x: %d \t y:%d\n",x,y);
	cursor_x = x;
	cursor_y = y;
}

void set_text_size(uint8_t s) {
	textsize = s;
}

void set_text_color(uint16_t c, uint16_t b) {
	textcolor = c;
	textbgcolor = b;
}

/*Calculates the RGB565 code*/
/*R,G,B: 0-100*/
uint16_t calc_RGB565(uint8_t r,uint8_t g,uint8_t b){
	return (r*31/100)<<11|(g*63/100)<<5|(b*31/100);
}

void LED_set_color(bool R, bool G, bool B){

	//Reset
	HAL_GPIO_WritePin(LED_RGB_PORT,GPIO_PIN_5,0);
	HAL_GPIO_WritePin(LED_RGB_PORT,GPIO_PIN_6,0);
	HAL_GPIO_WritePin(LED_RGB_PORT,GPIO_PIN_7,0);

	if(R){
		HAL_GPIO_WritePin(LED_RGB_PORT,GPIO_PIN_5,1);
	}
	if(G){
		HAL_GPIO_WritePin(LED_RGB_PORT,GPIO_PIN_6,1);
	}
	if(B){
		HAL_GPIO_WritePin(LED_RGB_PORT,GPIO_PIN_7,1);
	}

}



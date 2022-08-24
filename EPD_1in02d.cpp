/*****************************************************************************
* | File      	:	EPD_1in02.c
* | Author      :   Waveshare team
* | Function    :   Electronic paper driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-03-12
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_1in02d.h"
/**
 * full screen update LUT
**/
const unsigned char lut_w1[] =
{
0x60	,0x5A	,0x5A	,0x00	,0x00	,0x01	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
 	
};	
const unsigned char lut_b1[] =
{
0x90	,0x5A	,0x5A	,0x00	,0x00	,0x01	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,


};
/**
 * partial screen update LUT
**/
const unsigned char lut_w[] =
{
0x60	,0x01	,0x01	,0x00	,0x00	,0x01	,
0x80	,0x0f	,0x00	,0x00	,0x00	,0x01	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,

};	
const unsigned char lut_b[] =
{
0x90	,0x01	,0x01	,0x00	,0x00	,0x01	,
0x40	,0x0f	,0x00	,0x00	,0x00	,0x01	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,

};

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_Reset(void)
{
	DEV_Digital_Write(EPD_RST_PIN, 0);// Module reset
	DEV_Delay_ms(20);
	DEV_Digital_Write(EPD_RST_PIN, 1);
	DEV_Delay_ms(20);
	
}

/******************************************************************************
function :	send command
parameter:
     command : Command register
******************************************************************************/
static void EPD_SendCommand(UBYTE command)
{
	DEV_Digital_Write(EPD_CS_PIN, 0);
	DEV_Digital_Write(EPD_DC_PIN, 0);// command write

	DEV_SPI_WriteByte(command);
	DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_SendData(UBYTE Data)
{
	DEV_Digital_Write(EPD_CS_PIN, 0);
	DEV_Digital_Write(EPD_DC_PIN, 1);	// command write
	DEV_SPI_WriteByte(Data);
	DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	LUT download
******************************************************************************/
void EPD_SetFulltReg(void)
{
	unsigned int count;
	EPD_SendCommand(0x23);
	for(count=0;count<42;count++)	     
	{EPD_SendData(lut_w1[count]);}    
	
	EPD_SendCommand(0x24);
	for(count=0;count<42;count++)	     
	{EPD_SendData(lut_b1[count]);}          
}

/******************************************************************************
function :	LUT download
******************************************************************************/
void EPD_SetPartReg(void)
{
	unsigned int count;
	EPD_SendCommand(0x23);
	for(count=0;count<42;count++){
		EPD_SendData(lut_w[count]);
	}
	
	EPD_SendCommand(0x24);
	for(count=0;count<42;count++){
		EPD_SendData(lut_b[count]);
	}          
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
******************************************************************************/
void EPD_WaitUntilIdle(void)
{
	unsigned char busy;
	do
	{
		EPD_SendCommand(0x71);
		busy = DEV_Digital_Read(EPD_BUSY_PIN);
		busy =!(busy & 0x01);        
	}
	while(busy);   
	DEV_Delay_ms(200);                       
}


/******************************************************************************
function :	Turn On Display
******************************************************************************/
void EPD_TurnOnDisplay(void)
{
    EPD_SendCommand(0x04);  //power on
    EPD_WaitUntilIdle();
    EPD_SendCommand(0x12);  //Start refreshing the screen
    EPD_WaitUntilIdle();
    EPD_SendCommand(0x02);
    EPD_WaitUntilIdle();    //power off
}

/******************************************************************************
function :Initialize the e-Paper register
******************************************************************************/
BlueMicro_EPD::BlueMicro_EPD(void){}

UBYTE BlueMicro_EPD::Init(void)
{
	EPD_Reset(); 
	
	EPD_SendCommand(0xD2);			
	EPD_SendData(0x3F);
						 
	EPD_SendCommand(0x00);  			
	EPD_SendData (0x6F);  //from outside

	EPD_SendCommand(0x01);  //power setting
	EPD_SendData (0x03);	    
	EPD_SendData (0x00);
	EPD_SendData (0x2b);		
	EPD_SendData (0x2b); 
	
	EPD_SendCommand(0x06);  //Configuring the charge pump
	EPD_SendData(0x3f);
	
	EPD_SendCommand(0x2A);  //Setting XON and the options of LUT
	EPD_SendData(0x00); 
	EPD_SendData(0x00); 
	
	EPD_SendCommand(0x30);  //Set the clock frequency
	EPD_SendData(0x13); //50Hz

	EPD_SendCommand(0x50);  //Set VCOM and data output interval
	EPD_SendData(0x57);			

	EPD_SendCommand(0x60);  //Set The non-overlapping period of Gate and Source.
	EPD_SendData(0x22);

	EPD_SendCommand(0x61);  //resolution setting
	EPD_SendData (0x50);    //source 128 	 
	EPD_SendData (0x80);       

	EPD_SendCommand(0x82);  //sets VCOM_DC value
	EPD_SendData(0x12);  //-1v

	EPD_SendCommand(0xe3);//Set POWER SAVING
	EPD_SendData(0x33);
	EPD_SetFulltReg();	
  EPD_SendCommand(0x04);//Set POWER SAVING  
    
  EPD_WaitUntilIdle();
	return 0;
}

/******************************************************************************
function :	Clear screen
******************************************************************************/
void BlueMicro_EPD::Clear (void)
{ 
	unsigned int i;
	EPD_SendCommand(0x10);
	for(i=0;i<1280;i++){
		EPD_SendData(0X00);
	}
	EPD_SendCommand(0x13);	       //Transfer new data
	for(i=0;i<1280;i++){
		EPD_SendData(0xff);
	}
	EPD_TurnOnDisplay();
}

void BlueMicro_EPD::Display(UBYTE *Image)
{ 
  UWORD Width;
  Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
  //EPD_Init();
  EPD_SendCommand(0x10);
  for (UWORD j = 0; j < EPD_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(0xff);
        }
  }

  EPD_SendCommand(0x13);
  for (UWORD j = 0; j < EPD_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(~(Image[i + j * Width]));
        }
  }
  EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
    Image :Displayed data
******************************************************************************/
void BlueMicro_EPD::Display_Image(UBYTE *Image)
{ 
	UWORD Width;
	Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	//EPD_Init();
	EPD_SendCommand(0x10);
	for (UWORD j = 0; j < EPD_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(0xff);
        }
	}

	EPD_SendCommand(0x13);
	for (UWORD j = 0; j < EPD_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(~pgm_read_byte(&Image[i + j * Width]));
        }
	}
	EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
    old_Image:  Last displayed data
    Image2   :  New data
******************************************************************************/
void BlueMicro_EPD::DisplayPartial(UBYTE *old_Image, UBYTE *Image)
{
    /* Set partial Windows */
    EPD_SendCommand(0x91);		//This command makes the display enter partial mode
    EPD_SendCommand(0x90);		//resolution setting
    EPD_SendData(0);           //x-start
    EPD_SendData(79);       //x-end

    EPD_SendData(0);
    EPD_SendData(127);  //y-end
    EPD_SendData(0x00);

    UWORD Width;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);

    /* send data */
    EPD_SendCommand(0x10);
    for (UWORD j = 0; j < EPD_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(old_Image[i + j * Width]);
        }
    }

    EPD_SendCommand(0x13);
    for (UWORD j = 0; j < EPD_HEIGHT; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(Image[i + j * Width]);
        }
    }

    /* Set partial refresh */
    EPD_TurnOnDisplay();
}

/******************************************************************************
function :	Enter sleep mode
******************************************************************************/
void BlueMicro_EPD::Sleep(void)
{
    EPD_SendCommand(0X02);  	//power off
    EPD_WaitUntilIdle();
    EPD_SendCommand(0X07);  	//deep sleep
    EPD_SendData(0xA5);
    DEV_Digital_Write(EPD_RST_PIN, 0);// Module reset
}

/******************************************************************************
function :Partial refresh initialization e-paper
******************************************************************************/
void BlueMicro_EPD::Part_Init(void)
{
EPD_Reset();
  EPD_SendCommand(0xD2);      
  EPD_SendData(0x3F);
             
  EPD_SendCommand(0x00);        
  EPD_SendData (0x6F);  //from outside
    
  EPD_SendCommand(0x01);  //power setting
  EPD_SendData (0x03);
  EPD_SendData (0x00);
  EPD_SendData (0x2b);    
  EPD_SendData (0x2b);
  
  EPD_SendCommand(0x06);  //Configuring the charge pump
  EPD_SendData(0x3f);
  
  EPD_SendCommand(0x2A);  //Setting XON and the options of LUT
  EPD_SendData(0x00);
  EPD_SendData(0x00);
  
  EPD_SendCommand(0x30);  //Set the clock frequency
  EPD_SendData(0x17);
        
  EPD_SendCommand(0x50);  //Set VCOM and data output interval
  EPD_SendData(0xf2);

  EPD_SendCommand(0x60);  //Set The non-overlapping period of Gate and Source.
  EPD_SendData(0x22);

  EPD_SendCommand(0x82);  //Set VCOM_DC value
    EPD_SendData(0x12);//-1v

  EPD_SendCommand(0xe3);//Set POWER SAVING
  EPD_SendData(0x33);

  EPD_SetPartReg(); 
    
  EPD_SendCommand(0x04);//Set POWER SAVING  
    
  EPD_WaitUntilIdle();
}
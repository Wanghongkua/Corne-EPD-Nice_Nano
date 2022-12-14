#include "GUI_Paint.h"
#include "DEV_Config.h"
#include "EPD_1in02d.h"
#include "imagedata.h"
extern "C" {
#include "fonts.h"
}

unsigned char image_temp[1280]={0};
Paint paith(image_temp, 80, 128);
BlueMicro_EPD EPD;
void setup() {
//   pinMode(EPD_CS_PIN, OUTPUT);
//   pinMode(EPD_RST_PIN, OUTPUT);
//   pinMode(EPD_DC_PIN, OUTPUT);
//   pinMode(EPD_BUSY_PIN, INPUT);
// }
 Config_Init();
 if(EPD.Init() != 0) {
     Serial.print("e-Paper init failed\r\n");
 }
 Serial.print("1.02inch e-Paper Module1\r\n");
 EPD.Clear();
 DEV_Delay_ms(500);
 

 Serial.print("Drawing:BlackImage\r\n");
 paith.DrawCNStringAt(10, 10, "微雪", &Font24CN, 0xff);
//  paith.DrawStringAt(13, 0, "1.02inch", &Font12, 0xff);
//  paith.DrawStringAt(22, 13, "epd", &Font12, 0xff);
//  paith.DrawStringAt(10, 30, "ABC123", &Font16, 0xff);
 
//  paith.DrawLine(10, 50, 60, 100, 0xff );
//  paith.DrawLine(10, 100, 60, 50, 0xff);    
//  paith.DrawRectangle(10, 50, 60, 100, 0xff);
//  paith.DrawFilledCircle(35, 75, 20, 0xff);

 Serial.print("EPD_Display\r\n");
 EPD.Display(image_temp);
 DEV_Delay_ms(2000);

 
 EPD.Display_Image((uint8_t*)IMAGE_DATA);
 DEV_Delay_ms(500);
 EPD.Clear();
 
 EPD.Sleep();
 Serial.print("Goto Sleep mode...\r\n");
 DEV_Delay_ms(2000);
}

void loop() {

}

# Corne-EPD-Nice_Nano

Adding WaveShare 1.02 inch E-paper display (EPD) to Nice!Nano V2 board for Corne
keyboard.

## Arduino IDE configuration (TODO)

## Pin Connections

| EPD  | Nice!Nano |
|------|-----------|
| VCC  | 3.3V      |
| GND  | GND       |
| DIN  | P0.10     |
| CLK  | P1.13     |
| CS   | P0.09     |
| DC   | P1.06     |
| RST  | P1.04     |
| BUSY | P0.11     |

The connection points on Nice!Nano for `VCC`, `GND`, `DIN`, and `CLK` pins can't
be changed, but `CS`, `DC`, `RST`, and `BUSY` pins can be changed based on
personal preference.

To enable the above configuration, the file to change is `DEV_Config.h`, and the
code to change can be found below:

```CPP
#define EPD_CS_PIN          (9)
#define EPD_DC_PIN          (38)
#define EPD_RST_PIN         (36)
#define EPD_BUSY_PIN        (11)
```

There are 2 errors in the original [WaveShare Github code]
(https://github.com/waveshare/e-Paper).

The first is the Chinese characters need to be 4 bytes long in `struct CH_CN` in
file `fonts.h`.

```cpp
//GB2312
typedef struct                                          // 汉字字模数据结构
{
  unsigned char index[4];                               // 汉字内码索引
  const char matrix[MAX_HEIGHT_FONT*MAX_WIDTH_FONT/8];  // 点阵码数据
}CH_CN;
```

The second is `IMAGE_DATA` needs to be cast to `uint8_t*` before fed to function
`EPD_DISPLAY_IMAGE` in file `e-ink.ino`.

```cpp
 EPD_Display_Image((uint8_t*)IMAGE_DATA);
```


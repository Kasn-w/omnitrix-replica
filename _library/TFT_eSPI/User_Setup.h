/*Typical pin layout used:
 * ---------------------------------------------
 * Signal               ST7789 IPS    ESP8266
 *                      Module        Interface
 *                      Pin           Pin
 * ---------------------------------------------
 * VCC(3.3V)            VCC           3V3
 * GND(Ground)          GND           GND
 * SDA(Serial Data)     DIN           D7(MOSI)
 * SLK(Serial Clock)    CLK           D5(SCLK)
 * CS(Chip Select)      CS            D8(CS)
 * DC(Data/Command)     DC            D0
 * RST(Reset)           RST           D1
 * BL(Backlight)        BL            D2
  */

#define ST7789_DRIVER      

#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red to display 

#define TFT_WIDTH  240 // ST7789 240 x 320 resolution

#define TFT_HEIGHT 320 // ST7789 240 x 320 resolution

#define TFT_INVERSION_ON

#define TFT_BACKLIGHT_ON HIGH  // HIGH or LOW are options

#define TFT_MOSI 11 // In some display driver board, it might be written as "SDA" and so on.
#define TFT_SCLK 7
#define TFT_CS   6  // Chip select control pin
#define TFT_DC   35  // Data Command control pin
#define TFT_RST  39  // Reset pin (could connect to Arduino RESET pin)
#define TFT_BL   16  // LED back-light

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define SMOOTH_FONT

#define SPI_FREQUENCY  27000000 // Actually sets it to 26.67MHz = 80/3


#define SPI_READ_FREQUENCY  20000000 // Optional reduced SPI frequency for reading TFT

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  2500000

#define SUPPORT_TRANSACTIONS

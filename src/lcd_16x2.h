#ifndef LCD_16X2_H_
#define LCD_16X2_H_

#include "stm32f4xx_hal.h"

// LCD base commands
#define LCD_CLEAR_DISPLAY    0x01
#define LCD_RETURN_HOME      0x02
#define LCD_ENTRY_MODE       0x04
#define LCD_DISPLAY_CONTROL  0x08
#define LCD_CURSOR_SHIFT     0x10
#define LCD_FUNCTION_SET     0x20
#define LCD_SET_CGRAM_ADDR   0x40
#define LCD_SET_DDRAM_ADDR   0x80

// Display control flags
#define LCD_DISPLAY_ON       0x04
#define LCD_DISPLAY_OFF      0x00
#define LCD_CURSOR_ON        0x02
#define LCD_CURSOR_OFF       0x00
#define LCD_BLINK_ON         0x01
#define LCD_BLINK_OFF        0x00

// LCD bit flags
#define LCD_4BIT_MODE        0x00
#define LCD_2LINE_MODE       0x08
#define LCD_5x8_DOTS         0x00

#define LCD_ENABLE_BIT       0x04
#define LCD_BACKLIGHT_BIT    0x08
#define LCD_REGISTER_SELECT  0x01

#define LCD_I2C_ADDR         (0x3F << 1)  // Adjust as needed

// Public API
void LCD16_Init(I2C_HandleTypeDef *hi2c);
void LCD16_Clear(void);
void LCD16_SetCursor(uint8_t col, uint8_t row);
void LCD16_DisplayOn(void);
void LCD16_DisplayOff(void);
void LCD16_ShowCursor(void);
void LCD16_HideCursor(void);
void LCD16_BlinkCursor(void);
void LCD16_StopBlink(void);
void LCD16_PrintStr(const char *str);

#endif /* LCD_16X2_H_ */

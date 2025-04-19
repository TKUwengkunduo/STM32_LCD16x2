#include "lcd_16x2.h"

static I2C_HandleTypeDef *lcd_i2c = NULL;
static uint8_t lcd_control = LCD_DISPLAY_ON;
static uint8_t lcd_backlight = LCD_BACKLIGHT_BIT;

// Internal helpers
static void lcd_send_command(uint8_t cmd);
static void lcd_send_data(uint8_t data);
static void lcd_write(uint8_t data, uint8_t mode);
static void lcd_write_4bits(uint8_t data);
static void lcd_pulse_enable(uint8_t data);
static void lcd_write_i2c(uint8_t data);
static void lcd_delay_us(uint32_t us);

void LCD16_Init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;

    // Enable DWT for delay_us
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    HAL_Delay(50);

    lcd_write_4bits(0x30);
    HAL_Delay(5);
    lcd_write_4bits(0x30);
    HAL_Delay(1);
    lcd_write_4bits(0x30);
    HAL_Delay(1);
    lcd_write_4bits(0x20);

    lcd_send_command(LCD_FUNCTION_SET | LCD_2LINE_MODE | LCD_5x8_DOTS);
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
    LCD16_Clear();
    lcd_send_command(LCD_ENTRY_MODE | 0x02);  // Cursor increment, no shift
}

void LCD16_Clear(void) {
    lcd_send_command(LCD_CLEAR_DISPLAY);
    HAL_Delay(2);
}

void LCD16_SetCursor(uint8_t col, uint8_t row) {
    const uint8_t row_offsets[] = {0x00, 0x40};
    if (row > 1) row = 1;
    lcd_send_command(LCD_SET_DDRAM_ADDR | (col + row_offsets[row]));
}

void LCD16_DisplayOn(void) {
    lcd_control |= LCD_DISPLAY_ON;
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
}

void LCD16_DisplayOff(void) {
    lcd_control &= ~LCD_DISPLAY_ON;
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
}

void LCD16_ShowCursor(void) {
    lcd_control |= LCD_CURSOR_ON;
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
}

void LCD16_HideCursor(void) {
    lcd_control &= ~LCD_CURSOR_ON;
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
}

void LCD16_BlinkCursor(void) {
    lcd_control |= LCD_BLINK_ON;
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
}

void LCD16_StopBlink(void) {
    lcd_control &= ~LCD_BLINK_ON;
    lcd_send_command(LCD_DISPLAY_CONTROL | lcd_control);
}

void LCD16_PrintStr(const char *str) {
    while (*str) {
        lcd_send_data((uint8_t)*str++);
    }
}

// -------------------------- Internal --------------------------

static void lcd_send_command(uint8_t cmd) {
    lcd_write(cmd, 0);
}

static void lcd_send_data(uint8_t data) {
    lcd_write(data, LCD_REGISTER_SELECT);
}

static void lcd_write(uint8_t data, uint8_t mode) {
    uint8_t high = (data & 0xF0) | lcd_backlight | mode;
    uint8_t low  = ((data << 4) & 0xF0) | lcd_backlight | mode;
    lcd_write_4bits(high);
    lcd_write_4bits(low);
}

static void lcd_write_4bits(uint8_t data) {
    lcd_write_i2c(data);
    lcd_pulse_enable(data);
}

static void lcd_pulse_enable(uint8_t data) {
    lcd_write_i2c(data | LCD_ENABLE_BIT);
    lcd_delay_us(20);
    lcd_write_i2c(data & ~LCD_ENABLE_BIT);
    lcd_delay_us(20);
}

static void lcd_write_i2c(uint8_t data) {
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, &data, 1, 10);
}

static void lcd_delay_us(uint32_t us) {
    uint32_t start = DWT->CYCCNT;
    uint32_t delay = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT - start) < delay);
}

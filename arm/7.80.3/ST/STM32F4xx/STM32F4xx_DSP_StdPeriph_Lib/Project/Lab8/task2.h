#include "main.h"

#define LCD_WAKEUP 0x30
#define LCD_FUNC   0x38 // 8bit/2line
#define LCD_DISPLAY_ON_CURS_ON 0x0c
#define LCD_ENTRY_MODE 0x06
#define LCD_CURSOR_TOP_LEFT 0x01
#define LCD_CLEAR 0x01

static void ADC_Config(void);
void TIM2_Config(void);
void display(unsigned int x);
void gpioSetup();
void task2();

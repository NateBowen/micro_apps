#include "main.h"

#define LCD_PORT        GPIOD
#define LCD_PORT_CLOCK  RCC_AHB1Periph_GPIOD
#define LCD_DATA_BUS    0x00FF
#define LCD_ENABLE_PIN  GPIO_Pin_8
#define LCD_RW_PIN      GPIO_Pin_9
#define LCD_RS_PIN      GPIO_Pin_10

#define DIGIT_OFFSET    0x30
#define LETTER_i        0x69
#define LETTER_n        0x6E
#define LETTER_m        0x6D
#define LETTER_v        0x76
#define LETTER_a        0x61
#define LETTER_c        0x63
#define LETTER_l        0x6C
#define LETTER_d        0x64

void LCD_Config(void);
void LCD_Command(uint8_t data);
void LCD_Write(uint8_t data);
void LCD_WriteDigit(uint8_t data);
void LCD_DisplayINVALID(void);
void LCD_ClearDisplay(void);
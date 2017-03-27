#include "lcd.h"
#include "delay.h"



void LCD_Command(uint8_t data){
  LCD_PORT->ODR = data;
  LCD_PORT->ODR &= ~LCD_RS_PIN;
  LCD_PORT->ODR &= ~LCD_RW_PIN;
  LCD_PORT->ODR |= LCD_ENABLE_PIN;
  Delay(1);
  LCD_PORT->ODR &= ~(LCD_ENABLE_PIN);
  Delay(100);
}


void LCD_Write(uint8_t data){ 
  LCD_PORT->ODR = data;
  LCD_PORT->ODR |= LCD_RS_PIN;
  LCD_PORT->ODR &= ~LCD_RW_PIN;
  LCD_PORT->ODR |= LCD_ENABLE_PIN;
  Delay(1);
  LCD_PORT->ODR &= ~(LCD_ENABLE_PIN);
  Delay(100);
}


void LCD_WriteDigit(uint8_t data){ 
  LCD_Write(DIGIT_OFFSET | data);
}


void LCD_DisplayINVALID(void){
  LCD_Write(LETTER_i);
  LCD_Write(LETTER_n);
  LCD_Write(LETTER_v);
  LCD_Write(LETTER_a);
  LCD_Write(LETTER_l);
  LCD_Write(LETTER_i);
  LCD_Write(LETTER_d);
}


void LCD_ClearDisplay(void){
  LCD_Command(0x01);
}


void LCD_Config(void) {
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(LCD_PORT_CLOCK, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = LCD_DATA_BUS | LCD_ENABLE_PIN | LCD_RW_PIN | LCD_RS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LCD_PORT, &GPIO_InitStructure);
   
  LCD_PORT->ODR &= ~LCD_ENABLE_PIN;
  Delay(15);           //Wait >15 msec after power is applied
  LCD_Command(0x30);    //command 0x30 = Wake up
  Delay(5);            //must wait 5ms, busy flag not available
  LCD_Command(0x30);    //command 0x30 = Wake up #2
  Delay(1);            //must wait 160us, busy flag not available
  LCD_Command(0x30);    //command 0x30 = Wake up #3
  Delay(1);            //must wait 160us, busy flag not available

  LCD_Command(0x10);    //Set cursor
  LCD_Command(0x01);    //Clear
  LCD_Command(0x0E);    //Display ON; Cursor ON, Blink ON
  LCD_Command(0x06);    //Entry mode set
}

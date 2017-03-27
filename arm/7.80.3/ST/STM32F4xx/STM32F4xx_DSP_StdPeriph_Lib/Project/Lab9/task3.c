#include "task3.h"

extern __IO uint16_t startCapture;
extern __IO uint16_t stopCapture;
extern __IO uint16_t pulseWidth;

int task3(void)
{
double distance = 0;
  SysTick_Config(SystemCoreClock / 1000);
  LCD_Config();
  SR4_Config();
  switchConfig();
  
    uint16_t ones, tens, hundreds;
  while (1) {
    if( stopCapture > startCapture ) {
      pulseWidth = stopCapture - startCapture;
    } else {
      pulseWidth = startCapture - stopCapture;
    }
    
    if( GPIOA->IDR & GPIO_Pin_0 ) {
      //in
      distance = pulseWidth / 148;
    } else {
      //cm
      distance = pulseWidth / 58;
    }
    
    LCD_ClearDisplay();
    if( pulseWidth >= 640 && pulseWidth <= 5764 ) {
      ones = ( (int) distance) % 10;
      tens = (( (int) distance % 100) - ones) / 10;
      hundreds = ( (int) distance - tens - ones) / 100;      
      LCD_WriteDigit(hundreds); //Write hundreds digit
      LCD_WriteDigit(tens);  //Write tens digit
      LCD_WriteDigit(ones);  //Write ones digit
      if ( GPIOA->IDR & GPIO_Pin_0 ) {
        LCD_Write(LETTER_i);
        LCD_Write(LETTER_n);
      } else {
        LCD_Write(LETTER_c);
        LCD_Write(LETTER_m);
      }
    } else {
      LCD_DisplayINVALID();
    }
    Delay(500);
  }
}

void switchConfig() {
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
}


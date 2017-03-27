#include "task2.h"

extern __IO uint16_t startCapture;
extern __IO uint16_t stopCapture;
extern __IO uint16_t pulseWidth;

int task2(void)
{
double distance = 0;
  SysTick_Config(SystemCoreClock / 1000);
  LCD_Config();
  SR4_Config();
  
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
  }
}


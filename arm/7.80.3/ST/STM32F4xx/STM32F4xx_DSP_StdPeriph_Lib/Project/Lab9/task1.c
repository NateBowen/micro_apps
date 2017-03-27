#include "task1.h"

int task1(void){
  
  SysTick_Config(SystemCoreClock / 1000);
  LCD_Config();
  
  uint16_t count, ones, tens, hundreds;
  
  while(1){    
    for(count = 300; count > -1; count--){
      LCD_ClearDisplay();     
      ones = count % 10;
      tens = ((count % 100) - ones) / 10;
      hundreds = (count - tens - ones) / 100;      
      LCD_WriteDigit(hundreds); //Write hundreds digit
      LCD_WriteDigit(tens);  //Write tens digit
      LCD_WriteDigit(ones);  //Write ones digit
      Delay(1000);
      LCD_ClearDisplay();
      LCD_DisplayINVALID();
      Delay(1000);
    }  
  }
}
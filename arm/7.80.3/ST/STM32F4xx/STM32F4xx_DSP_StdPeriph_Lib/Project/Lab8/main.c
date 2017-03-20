#include "main.h"
#include "lcd.h"
#include "delay.h"

int main(void)
{
  
  SysTick_Config(SystemCoreClock / 1000);
  
  LCD_Config();
 
  char count;
  
  /* Infinite loop */
  while (1)
  {
    Delay(1000);
    LCD_Command(0x01);
    count++;
    LCD_Write(0x30 | count);
    Delay(1000);
    
    
  }
}

#include "main.h"
#include "lcd.h"
#include "delay.h"
#include "lm35.h"
#include "task2.h"

void task1();

int main(void) {
  SysTick_Config(SystemCoreClock / 1000);
  LCD_Config();
  
  //task1();
  task2();
}

void task1() {
  SysTick_Config(SystemCoreClock / 1000);
  
  LCD_Config();
  I2C_Config();
  
  char count, ones, tens, hundreds;
  
  /* Infinite loop */
  while (1)
  {
    for(count = 0; count <= 212; count++){
      
      LCD_Command(0x01); //Clear line, reset cursor
      
      ones = count % 10;
      tens = ((count % 100) - ones) / 10;
      hundreds = (count - tens - ones) / 100;
      
      LCD_WriteDigit(hundreds); //Write hundreds digit
      LCD_WriteDigit(tens);  //Write tens digit
      LCD_WriteDigit(ones);  //Write ones digit
      
      Delay(1000); //Wait 1 second
      
      talkToLM35();
    }
  }
}
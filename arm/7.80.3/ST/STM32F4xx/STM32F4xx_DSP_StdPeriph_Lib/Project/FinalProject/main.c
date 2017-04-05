#include "main.h"
#include "delay.h"
#include "buzzer.h"
#include "led.h"
#include "motor.h"
#include "lcd.h"
#include "switch.h"

int main(void)
{
  Delay_Config();
  LED_Config();
  LCD_Config();
  Buzzer_Config();
  Switch_Config();
  Encoder_Config();
  Motor_Config();

  while (1)
  {

  }
}

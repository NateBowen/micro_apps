#include "main.h"

#define LED_PORT        GPIOA
#define LED_PINS        0xFF

#define SWITCH_PORT     GPIOD
#define SWITCH_PINS     0xFF

GPIO_InitTypeDef   GPIO_InitStructure;

int main(void)
{
  
  /* GPIOA and GPIOD Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* Configure LED_PINS as output */
  GPIO_InitStructure.GPIO_Pin = LED_PINS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(LED_PORT, &GPIO_InitStructure); 
  
  /* Configure SWITCH_PINS as input */
  GPIO_InitStructure.GPIO_Pin = SWITCH_PINS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SWITCH_PORT, &GPIO_InitStructure);   
  
  int switchValue = 0;
  
  while (1)
  {
    /* Read SWITCH_PORT and copy value to LED_PORT */
    //LED_PORT->ODR = (SWITCH_PORT->IDR & 0x00FF);
    switchValue = (SWITCH_PORT->IDR & 0x000F);
    switchValue ^= (SWITCH_PORT->IDR & 0x00F0);
    LED_PORT->ODR = switchValue;
  }
}


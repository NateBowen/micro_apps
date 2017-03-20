#include "stm32f4xx_it.h"
#include "main.h"

__IO uint32_t TimingDelay;

void SysTick_Handler(void)
{
  if (TimingDelay !=0) 
  {
    TimingDelay--;
  }
}


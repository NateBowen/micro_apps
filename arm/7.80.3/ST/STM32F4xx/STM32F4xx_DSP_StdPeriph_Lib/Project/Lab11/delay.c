#include "delay.h"

extern __IO uint32_t TimingDelay;

void Delay_Config(void) {
  //For 1ms delay, divide system clock by 1000
  SysTick_Config(SystemCoreClock / 1000);
}

// Delay function holds in while loop for duration of SysTick clock
void Delay(uint32_t time){
  TimingDelay = time;
  while(TimingDelay != 0);
}

#include "delay.h"

extern __IO uint32_t TimingDelay;

/* Delay function holds in while loop for duration of SysTick clock (1ms) */
void Delay(uint32_t time){
  TimingDelay = time;
  while(TimingDelay != 0);
}


//
///* Delay function holds in while loop for duration of SysTick clock (1ms) */
//void Delay(__IO uint32_t nTime)
//{
//  TimingDelay = nTime;
//  while(TimingDelay != 0);
//}
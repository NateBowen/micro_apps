/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

#define SIG_PIN         GPIO_Pin_15
#define DATA_PINS       0xFF00

void TIM5_IRQHandler(void)
{
  // Check for correct channel interrupt bit
  if(TIM_GetITStatus(TIM5, TIM_IT_CC1) == SET) 
  {
    // Set SIG HIGH
    GPIOC->ODR = SIG_PIN;
    
    // Decrement DATA and write to port
    GPIOD->ODR--;
    
    // Set SIG LOW
    GPIOC->ODR &= ~SIG_PIN;
    
    TIM5->CNT = 0;
    
    // Clear interrupt bit    
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);
  } 
}



void SysTick_Handler(void)
{
  //TimingDelay_Decrement();
}

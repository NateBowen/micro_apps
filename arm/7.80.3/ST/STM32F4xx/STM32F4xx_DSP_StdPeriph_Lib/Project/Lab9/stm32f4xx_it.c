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

void TIM4_IRQHandler(void){
  if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
  {
    /* Clear TIM2 Capture Compare1 interrupt pending bit*/
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
    
    GPIOD->ODR |= GPIO_Pin_12;
    /* LED1 turn-off after 500 ms */
//    STM_EVAL_LEDOff(LED1);
  }
  else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
  {
    /* Clear TIM2 Capture Compare2 interrupt pending bit*/
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
    GPIOD->ODR &= ~GPIO_Pin_13;
    /* LED2 turn-off after 250 ms */
//    STM_EVAL_LEDOff(LED2);
  }
  else if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
  {
    /* Clear TIM2 Capture Compare3 interrupt pending bit*/
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
    GPIOD->ODR &= ~GPIO_Pin_14;
    
    /* LED3 turn-off after 125 ms */
//    STM_EVAL_LEDOff(LED3);
  }
  else
  {
    /* Clear TIM2 Capture Compare4 interrupt pending bit*/
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
    GPIOD->ODR &= ~GPIO_Pin_15;
    /* LED4 turn-off after 62.5 ms */
//    STM_EVAL_LEDOff(LED4);
  }
}
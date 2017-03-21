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

//--------------------------------TASK2--------------------------

extern unsigned int temp;
extern unsigned int f_temp;
extern unsigned int updateDisplay;

void TIM2_IRQHandler(void){
  if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3 );
    //temp = 100 * ADC_GetConversionValue(ADC1) / 4096;
    //ADC_SoftwareStartConv(ADC1);
    updateDisplay = 1;
  }
}

void ADC_IRQHandler() {
  if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET){
    unsigned int dave = ADC_GetConversionValue(ADC1);
    temp = (unsigned int) dave / 41;
    f_temp = temp * 9 / 5 + 32;
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
    ADC_SoftwareStartConv(ADC1);
  }
}
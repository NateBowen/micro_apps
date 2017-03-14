/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
//#include "main.h"

extern uint16_t ADCInputValue;
extern uint16_t SawtoothValue;

void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET){
    
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
    
 
        if(SawtoothValue > 4092)
        {
          SawtoothValue = 0;
        }
        else
        {
          SawtoothValue += 4;
        }
  }
}

void ADC_IRQHandler()
{
  if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET){
    
    ADCInputValue = ADC_GetConversionValue(ADC1);
      
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
    ADC_SoftwareStartConv(ADC1);
  }
}



#include "stm32f4xx_it.h"

__IO uint16_t uhIC2ReadValue1 = 0;
__IO uint16_t uhIC2ReadValue2 = 0;
__IO uint16_t uhIC2ReadValue3 = 0;

__IO uint16_t uhCaptureNumber = 0;
__IO uint32_t uwCapture = 0;
__IO uint32_t uwCapture2 = 0;
__IO uint32_t uwTIM5Freq = 0;
__IO uint32_t uwTIM5Period = 0;
__IO uint32_t uwTIM5Duty = 0;

int sigLevel = 0;

void TIM5_IRQHandler(void)
{ 
  if(TIM_GetITStatus(TIM5, TIM_IT_CC2) == SET) 
  {   
    /* Check the signal level, only measure when starting with a peak */  
    sigLevel = (GPIOA->IDR & 0x02) >> 1;   
    
    if ((uhCaptureNumber == 0) & (sigLevel == 1))
    {    
      /* Get the Input Capture value */
      uhIC2ReadValue1 = TIM_GetCapture2(TIM5);
      uhCaptureNumber = 1;
    } 
    
    else if(uhCaptureNumber == 1)
    {
      /* Get the Input Capture value */
      uhIC2ReadValue2 = TIM_GetCapture2(TIM5); 
      uhCaptureNumber = 2;
    }
    
    
    else if (uhCaptureNumber == 2)
    {     
      /* Get the Input Capture value */
      uhIC2ReadValue3 = TIM_GetCapture2(TIM5); 
      
      /* First period computation */
      if (uhIC2ReadValue2 > uhIC2ReadValue1)
      {
        uwCapture = (uhIC2ReadValue2 - uhIC2ReadValue1); 
      }
      else if (uhIC2ReadValue2 < uhIC2ReadValue1)
      {
        uwCapture = ((0xFFFF - uhIC2ReadValue1) + uhIC2ReadValue2); 
      }
      else
      {
        uwCapture = 0;
      }
      
      /* Second period computation */
      if (uhIC2ReadValue3 > uhIC2ReadValue2)
      {
        uwCapture2 = (uhIC2ReadValue3 - uhIC2ReadValue2); 
      }
      else if (uhIC2ReadValue3 < uhIC2ReadValue2)
      {
        uwCapture2 = ((0xFFFF - uhIC2ReadValue2) + uhIC2ReadValue3); 
      }
      else
      {
        uwCapture2 = 0;
      }
      
      /*  Period computation (in microseconds) */
      uwTIM5Period = 2 * (uwCapture + uwCapture2) / (SystemCoreClock / 1000000);
      
      /* Duty Cycle computation (percentage) */
      uwTIM5Duty = (uwCapture * 100) / (uwCapture + uwCapture2);
      
      /* Frequency computation */ 
      uwTIM5Freq = (uint32_t) SystemCoreClock / (2 * (uwCapture + uwCapture2));
      
      uhCaptureNumber = 0; 
    }
        /* Clear TIM5 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);
  } 
}

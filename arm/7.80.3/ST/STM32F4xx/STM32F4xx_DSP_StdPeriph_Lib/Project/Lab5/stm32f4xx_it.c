#include "stm32f4xx_it.h"

__IO uint16_t uhIC2ReadValue1 = 0;
__IO uint16_t uhIC2ReadValue2 = 0;
__IO uint16_t uhCaptureNumber = 0;
__IO uint32_t uwCapture = 0;
__IO uint32_t uwTIM5Freq = 0;

void TIM5_IRQHandler(void)
{ 
  if(TIM_GetITStatus(TIM5, TIM_IT_CC2) == SET) 
  {
    /* Clear TIM2 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);

    if(uhCaptureNumber == 0)
    {
      /* Get the Input Capture value */
      uhIC2ReadValue1 = TIM_GetCapture2(TIM5);
      uhCaptureNumber = 1;
    }
    
    else if(uhCaptureNumber == 1)
    {
      /* Get the Input Capture value */
      uhIC2ReadValue2 = TIM_GetCapture2(TIM5); 
      
      /* Capture computation */
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

      /* Frequency computation */ 
      uwTIM5Freq = (uint32_t) SystemCoreClock / (2*uwCapture);
      uhCaptureNumber = 0;    
    }
  }
}

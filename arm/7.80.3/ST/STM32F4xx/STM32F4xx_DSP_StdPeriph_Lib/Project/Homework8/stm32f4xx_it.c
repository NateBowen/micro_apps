#include "stm32f4xx_it.h"
#include "main.h"

void SysTick_Handler(void)
{
    // TimingDelay--;
}

uint32_t encoderFrequency, pulse, distance;

void TIM5_IRQHandler(void){
  
  static uint16_t TIM5_CC3_sigLevel = 0;
  static uint16_t IC2ReadValue1 = 0;
  static uint16_t IC2ReadValue2 = 0;
  static uint16_t IC2ReadValue3 = 0;
  static uint16_t CaptureNumber = 0;
  static uint32_t Capture = 0;
  static uint32_t Capture2 = 0;
  
  if(TIM_GetITStatus(TIM5, TIM_IT_CC3) == SET) {
    /* Check the signal level, only measure when starting with a peak */
    TIM5_CC3_sigLevel = (GPIOA->IDR & 0x04) >> 2;
    
    if ((CaptureNumber == 0) & (TIM5_CC3_sigLevel == 1)) {
      /* Get the Input Capture value */
      IC2ReadValue1 = TIM_GetCapture3(TIM5);
      CaptureNumber = 1;
    }
    
    else if(CaptureNumber == 1) {
      /* Get the Input Capture value */
      IC2ReadValue2 = TIM_GetCapture3(TIM5);
      CaptureNumber = 2;
    }
    
    else if (CaptureNumber == 2) {
      /* Get the Input Capture value */
      IC2ReadValue3 = TIM_GetCapture3(TIM5);
      
      /* First period computation */
      if (IC2ReadValue2 > IC2ReadValue1) {
        Capture = (IC2ReadValue2 - IC2ReadValue1);
      }
      else if (IC2ReadValue2 < IC2ReadValue1) {
        Capture = ((0xFFFF - IC2ReadValue1) + IC2ReadValue2);
      }
      else {
        Capture = 0;
      }
      
      /* Second period computation */
      if (IC2ReadValue3 > IC2ReadValue2) {
        Capture2 = (IC2ReadValue3 - IC2ReadValue2);
      }
      else if (IC2ReadValue3 < IC2ReadValue2) {
        Capture2 = ((0xFFFF - IC2ReadValue2) + IC2ReadValue3);
      }
      else {
        Capture2 = 0;
      }   
      /* Frequency computation */
      encoderFrequency = (uint32_t) SystemCoreClock / (2 * (Capture + Capture2));
      
      // Pulse width computation
      pulse = 2 * 84 * Capture / (SystemCoreClock / 1000000);
      distance = pulse / 58;
      
      CaptureNumber = 0;
    }
    /* Clear TIM5 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
  }
}

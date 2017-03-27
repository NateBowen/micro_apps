#include "stm32f4xx_it.h"
#include "main.h"

__IO uint32_t TimingDelay;

__IO uint16_t sigLevel = 0;

__IO uint16_t uhIC2ReadValue1 = 0;
__IO uint16_t uhIC2ReadValue2 = 0;
__IO uint16_t uhIC2ReadValue3 = 0;

__IO uint16_t uhCaptureNumber = 0;
__IO uint32_t uwCapture = 0;
__IO uint32_t uwCapture2 = 0;
__IO uint32_t uwTIM5Freq = 0;
__IO uint32_t uwTIM5Period = 0;
__IO uint32_t uwTIM5Duty = 0;


void SysTick_Handler(void)
{
  if (TimingDelay !=0) 
  {
    TimingDelay--;
  }
}

void TIM2_IRQHandler(void){
  if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET){
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
  }
}

char state = 0;
extern __IO uint16_t startCapture;
extern __IO uint16_t stopCapture;
extern __IO uint16_t pulseWidth;

void TIM5_IRQHandler(void){  
  if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET){
    
    /* Check the signal level, only measure when starting with a peak */  
    sigLevel = (GPIOA->IDR & 0x04) >> 2;   
    
    switch(state) {
    case 0:
      //low to high
      if ( GPIOA->IDR & GPIO_Pin_2 ) {
        startCapture = TIM_GetCapture3(TIM5);
        state = 1;
      }
      break;
    case 1:
      //high to low
      if ( !( GPIOA->IDR & GPIO_Pin_2 ) ) {
        stopCapture = TIM_GetCapture3(TIM5);
        state = 0;
      }
      break;
    }
    /**
    if ((uhCaptureNumber == 0) & (sigLevel == 1))
    {    
      uhIC2ReadValue1 = TIM_GetCapture3(TIM5);
      uhCaptureNumber = 1;
    } 
    
    else if(uhCaptureNumber == 1)
    {
      uhIC2ReadValue2 = TIM_GetCapture3(TIM5); 
      uhCaptureNumber = 2;
    }
    
    
    else if (uhCaptureNumber == 2)
    {     
      uhIC2ReadValue3 = TIM_GetCapture3(TIM5); 
      
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
      
      uwTIM5Period = 2 * 84 *(uwCapture + uwCapture2) / (SystemCoreClock / 1000000);
      
      uwTIM5Duty = (uwCapture * 100) / (uwCapture + uwCapture2);
      
      uwTIM5Freq = (uint32_t) SystemCoreClock / (84 * 2 * (uwCapture + uwCapture2)) - 1;
      
      uhCaptureNumber = 0; 
    }    
    **/
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
  }
}
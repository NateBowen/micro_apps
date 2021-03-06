#include "main.h"
#include "stm32f4xx_it.h"
#include "encoder.h"
#include "sr4.h"

/***************************************************************************
The SysTick_Hander takes care of decrementing the global TimingDelay variable
that is used in the Delay() function.
****************************************************************************/

uint32_t TimingDelay;

void SysTick_Handler(void)
{
  TimingDelay--;
}


/***************************************************************************
The TIM5_IRQHandler handles the the input capture for the Encoder frequency.
It sets the global encoderFrequency variable.
****************************************************************************/

uint32_t encoderFrequency;

void TIM5_IRQHandler(void){

  static uint16_t TIM5_CC2_sigLevel = 0;
  static uint16_t IC2ReadValue1 = 0;
  static uint16_t IC2ReadValue2 = 0;
  static uint16_t IC2ReadValue3 = 0;
  static uint16_t CaptureNumber = 0;
  static uint32_t Capture = 0;
  static uint32_t Capture2 = 0;

  if(TIM_GetITStatus(TIM5, TIM_IT_CC2) == SET) {
    /* Check the signal level, only measure when starting with a peak */
    TIM5_CC2_sigLevel = (ENCODER_PORT->IDR & ENCODER_PIN);

    if ((CaptureNumber == 0) && (TIM5_CC2_sigLevel)) {
      /* Get the Input Capture value */
      IC2ReadValue1 = TIM_GetCapture2(TIM5);
      CaptureNumber = 1;
    }

    else if(CaptureNumber == 1) {
      /* Get the Input Capture value */
      IC2ReadValue2 = TIM_GetCapture2(TIM5);
      CaptureNumber = 2;
    }

    else if (CaptureNumber == 2) {
      /* Get the Input Capture value */
      IC2ReadValue3 = TIM_GetCapture2(TIM5);

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

      CaptureNumber = 0;
    }
    /* Clear TIM5 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);
  }
}


/***************************************************************************
The TIM3_IRQHandler handles the the input capture for the SR4 pulse.
It sets the global distance_CM variable.
****************************************************************************/

uint32_t distance_CM;

void TIM3_IRQHandler(void){

  static uint16_t TIM3_CC2_sigLevel = 0;
  static uint16_t IC2ReadValue1 = 0;
  static uint16_t IC2ReadValue2 = 0;
  static uint16_t IC2ReadValue3 = 0;
  static uint16_t CaptureNumber = 0;
  static uint32_t Capture = 0;
  static uint32_t Capture2 = 0;

  if(TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET) {
    /* Check the signal level, only measure when starting with a peak */
    TIM3_CC2_sigLevel = (ECHO_PORT->IDR & ECHO_PIN);

    if ((CaptureNumber == 0) && (TIM3_CC2_sigLevel)) {
      /* Get the Input Capture value */
      IC2ReadValue1 = TIM_GetCapture2(TIM3);
      CaptureNumber = 1;
    }

    else if(CaptureNumber == 1) {
      /* Get the Input Capture value */
      IC2ReadValue2 = TIM_GetCapture2(TIM3);
      CaptureNumber = 2;
    }

    else if (CaptureNumber == 2) {
      /* Get the Input Capture value */
      IC2ReadValue3 = TIM_GetCapture2(TIM3);

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

      //Distance calculation
      uint32_t pulse = 2 * ECHO_CLOCK_PRESCALAR * Capture / (SystemCoreClock / 1000000);
      distance_CM = pulse / MICROSECONDS_TO_CM;

      CaptureNumber = 0;
    }
    /* Clear TIM3 Capture compare interrupt pending bit */
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
  }
}

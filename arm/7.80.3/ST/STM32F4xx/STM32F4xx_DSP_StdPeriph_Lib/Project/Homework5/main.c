#include "main.h"

#define LED0    GPIO_Pin_12
#define LED1    GPIO_Pin_13

TIM_ICInitTypeDef  TIM_ICInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructureMain;

int main(void)
{
    /* TIM5 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

  /* GPIOA and GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  /* GPIOD output LEDs configuration */
  GPIO_InitStructure.GPIO_Pin =  LED0 | LED1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* TIM5 channel 2 pin (PA1) configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM5 pins to AF1 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
  
  /* Enable the TIM5 global Interrupt */
  NVIC_InitStructureMain.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructureMain.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructureMain.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructureMain.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructureMain);

  /* TIM5 configuration: Input Capture mode ---------------------*/
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);
  
  /* TIM5 enable counter */
  TIM_Cmd(TIM5, ENABLE);

  /* Enable the CC3 Interrupt Request */
  TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);

  while (1)
  {
    /* Doin' nothin', son. */ 
  }
}

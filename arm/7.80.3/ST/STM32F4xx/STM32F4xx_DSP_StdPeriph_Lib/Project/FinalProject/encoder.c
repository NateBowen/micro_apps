#include "encoder.h"

void Encoder_Config(void){

  TIM_ICInitTypeDef  TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructureMain;

  /* TIM5 clock enable */
RCC_APB1PeriphClockCmd(ENCODER_TIMx_CLOCK, ENABLE);

/* GPIOA clock enable */
RCC_AHB1PeriphClockCmd(ENCODER_PORT_CLOCK, ENABLE);

/* TIM5 channel 2 pin (PA1) configuration */
GPIO_InitStructure.GPIO_Pin =  ENCODER_PIN;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(ENCODER_PORT, &GPIO_InitStructure);

/* Connect TIM5 pins to AF1 */
GPIO_PinAFConfig(ENCODER_PORT, ENCODER_PINSOURCE, ENCODER_AF_TIMx);

/* Enable the TIM5 global Interrupt */
NVIC_InitStructureMain.NVIC_IRQChannel = ENCODER_TIMx_IRQ;
NVIC_InitStructureMain.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructureMain.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructureMain.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructureMain);

/* TIM5 configuration: Input Capture mode ---------------------*/
TIM_ICInitStructure.TIM_Channel = ENCODER_TIMx_CHx;
TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
TIM_ICInitStructure.TIM_ICFilter = 0x0;
TIM_ICInit(ENCODER_TIMx, &TIM_ICInitStructure);

/* TIM5 enable counter */
TIM_Cmd(ENCODER_TIMx, ENABLE);

/* Enable the CC3 Interrupt Request */
TIM_ITConfig(ENCODER_TIMx, ENCODER_TIMx_IT_CCx, ENABLE);

}

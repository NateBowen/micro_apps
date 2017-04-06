#include "sr4.h"

void SR4_Config(void){
  SR4_1_EchoConfig();
  SR4_2_EchoConfig();
  SR4_TriggerConfig();
}

void SR4_TriggerConfig(void){

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);

  TIM_TimeBaseStructure.TIM_Period = TRIG_CLOCK_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = TRIG_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TRIG_PULSE;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);

  TIM_Cmd(TIM2, ENABLE);
}

void SR4_1_EchoConfig(void){
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(S1_TIMx_CLOCK, ENABLE);

  RCC_AHB1PeriphClockCmd(S1_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = S1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(S1_PORT, &GPIO_InitStructure);

  GPIO_PinAFConfig(S1_PORT, S1_PINSOURCE, S1_AF_TIMx);

  NVIC_InitStructure.NVIC_IRQChannel = S1_TIMx_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_TimeBaseStructure.TIM_Period = S1_CLOCK_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = S1_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(S1_TIMx, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = S1_TIMx_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(S1_TIMx, &TIM_ICInitStructure);

  TIM_ARRPreloadConfig(S1_TIMx, ENABLE);

  TIM_ITConfig(S1_TIMx, S1_TIM_IT_CCx, ENABLE);

  TIM_Cmd(S1_TIMx, ENABLE);
}

void SR4_2_EchoConfig(void){
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(S1_TIMx_CLOCK, ENABLE);

  RCC_AHB1PeriphClockCmd(S1_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = S1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(S1_PORT, &GPIO_InitStructure);

  GPIO_PinAFConfig(S1_PORT, S1_PINSOURCE, S1_AF_TIMx);

  NVIC_InitStructure.NVIC_IRQChannel = S1_TIMx_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_TimeBaseStructure.TIM_Period = S1_CLOCK_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = S1_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(S1_TIMx, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = S1_TIMx_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(S1_TIMx, &TIM_ICInitStructure);

  TIM_ARRPreloadConfig(S1_TIMx, ENABLE);

  TIM_ITConfig(S1_TIMx, S1_TIM_IT_CCx, ENABLE);

  TIM_Cmd(S1_TIMx, ENABLE);
}

#include "sr4.h"

void SR4_Config(void){
  SR4_EchoConfig();
  SR4_TriggerConfig();
}

void SR4_TriggerConfig(void){

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(TRIG_TIMx_CLOCK, ENABLE);
  RCC_AHB1PeriphClockCmd(TRIG_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);

  GPIO_PinAFConfig(TRIG_PORT, TRIG_PINSOURCE, TRIG_AF_TIMx);

  TIM_TimeBaseStructure.TIM_Period = TRIG_CLOCK_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = TRIG_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TRIG_TIMx, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = TRIG_PULSE;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TRIG_TIMx, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TRIG_TIMx, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TRIG_TIMx, ENABLE);

  TIM_Cmd(TRIG_TIMx, ENABLE);
}

void SR4_EchoConfig(void){
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(ECHO_TIMx_CLOCK, ENABLE);

  RCC_AHB1PeriphClockCmd(ECHO_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(ECHO_PORT, &GPIO_InitStructure);

  GPIO_PinAFConfig(ECHO_PORT, ECHO_PINSOURCE, ECHO_AF_TIMx);

  NVIC_InitStructure.NVIC_IRQChannel = ECHO_TIMx_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_TimeBaseStructure.TIM_Period = ECHO_CLOCK_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = ECHO_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(ECHO_TIMx, &TIM_TimeBaseStructure);

  TIM_ICInitStructure.TIM_Channel = ECHO_TIMx_CHANNEL;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(ECHO_TIMx, &TIM_ICInitStructure);

  TIM_ARRPreloadConfig(ECHO_TIMx, ENABLE);

  TIM_ITConfig(ECHO_TIMx, ECHO_TIM_IT_CCx, ENABLE);

  TIM_Cmd(ECHO_TIMx, ENABLE);
}

uint16_t GetDistance(void){
  return distance_CM;
}

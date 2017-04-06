#include "motor.h"

void Motor_Config(void){
  
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
    
  uint16_t pulseDuration = 16000;
//  uint16_t uhPrescalerValue = 0;
  //interrupt every 1 us
  
  
  
  TIM_TimeBaseStructure.TIM_Period = MOTOR_PWM_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = pulseDuration;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
    
  TIM_Cmd(TIM2, ENABLE);
}


void SetMotorDutyCycle(uint8_t dutyCycle){
  uint16_t pulse = MOTOR_PWM_PERIOD * dutyCycle / 100;
  TIM2->CCR3 = pulse;
}

uint8_t CalculateDutyCycle(uint16_t freq){
  if(freq > 6500){
    freq = 6500;
  }
  else if(freq < 4500){
    freq = 4500;
  }
  uint8_t dutyCycle = (6500-freq)/20;
  return dutyCycle;
}

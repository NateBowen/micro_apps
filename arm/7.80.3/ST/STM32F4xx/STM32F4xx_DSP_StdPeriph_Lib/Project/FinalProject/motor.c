#include "motor.h"

void Motor_Config(void){

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(MOTOR_TIMx_CLOCK, ENABLE);
  RCC_AHB1PeriphClockCmd(MOTOR_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = MOTOR_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(MOTOR_PORT, &GPIO_InitStructure);

  GPIO_PinAFConfig(MOTOR_PORT, MOTOR_PINSOURCE, MOTOR_AF_TIMx);

  TIM_TimeBaseStructure.TIM_Period = MOTOR_PWM_PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_CLOCK_PRESCALAR;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(MOTOR_TIMx, &TIM_TimeBaseStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(MOTOR_TIMx, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(MOTOR_TIMx, TIM_OCPreload_Disable);
  TIM_ARRPreloadConfig(MOTOR_TIMx, ENABLE);

  TIM_Cmd(MOTOR_TIMx, ENABLE);
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

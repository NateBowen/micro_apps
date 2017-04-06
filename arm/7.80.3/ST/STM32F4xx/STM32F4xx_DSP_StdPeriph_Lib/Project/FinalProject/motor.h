#include "main.h"

/*
The motor driver uses TIM2_CH3 (PA2) for generating a PWM value.
To change the pin or port used, modify the following #defines.
*/

#define MOTOR_PORT              GPIOA
#define MOTOR_PIN               GPIO_Pin_2
#define MOTOR_PORT_CLOCK        RCC_AHB1Periph_GPIOA
#define MOTOR_PINSOURCE         GPIO_PinSource2
#define MOTOR_TIMx              TIM2
#define MOTOR_AF_TIMx           GPIO_AF_TIM2
#define MOTOR_TIMx_CLOCK        RCC_APB1Periph_TIM2
#define MOTOR_CLOCK_PRESCALAR   0
#define MOTOR_PWM_PERIOD        2800  //30kHz when running at APB1 = 84kHz


void Motor_Config(void);
void SetMotorDutyCycle(uint8_t dutyCycle);
uint8_t CalculateDutyCycle(uint16_t freq);

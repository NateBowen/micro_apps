#include "main.h"

/*
The motor driver uses TIM2_CH3 (PA2) for generating a PWM value.
To change the pin or port used, modify the following #defines.
*/


#define MOTOR_CLOCK_PRESCALAR   0
#define MOTOR_PWM_PERIOD        2800


void Motor_Config(void);
void SetMotorDutyCycle(uint8_t dutyCycle);
uint8_t CalculateDutyCycle(uint16_t freq);
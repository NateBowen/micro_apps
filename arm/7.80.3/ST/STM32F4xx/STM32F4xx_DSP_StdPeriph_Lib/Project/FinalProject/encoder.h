#include "main.h"

/*
The encoder driver uses TIM5_CH2 (PA1) for reading the frequency coming from the
function generator. To change the pin or port used, modify the following #defines.
*/

#define ENCODER_PORT        GPIOA
#define ENCODER_PORT_CLOCK  RCC_AHB1Periph_GPIOA
#define ENCODER_PIN         GPIO_Pin_1
#define ENCODER_PINSOURCE   GPIO_PinSource1
#define ENCODER_AF_TIMx     GPIO_AF_TIM5

#define ENCODER_TIMx        TIM5
#define ENCODER_TIMx_CLOCK  RCC_APB1Periph_TIM5
#define ENCODER_TIMx_CHx    TIM_Channel_2
#define ENCODER_TIMx_IRQ    TIM5_IRQn
#define ENCODER_TIMx_IT_CCx TIM_IT_CC2

extern uint32_t encoderFrequency;

void Encoder_Config(void);
uint16_t GetEncoderFrequency(void);

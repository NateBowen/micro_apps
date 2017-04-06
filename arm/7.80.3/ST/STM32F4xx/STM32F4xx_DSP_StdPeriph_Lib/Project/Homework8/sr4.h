#include "main.h"

#define TRIG_CLOCK_PRESCALAR  84
#define TRIG_CLOCK_PERIOD     50000
#define TRIG_PULSE            14

#define S1_PORT               GPIOA
#define S1_PIN                GPIO_Pin_2
#define S1_PORT_CLOCK         RCC_AHB1Periph_GPIOA
#define S1_PINSOURCE          GPIO_PinSource2
#define S1_TIMx               TIM5
#define S1_TIMx_CHANNEL       TIM_Channel_3
#define S1_TIMx_CLOCK         RCC_APB1Periph_TIM5
#define S1_AF_TIMx            GPIO_AF_TIM5
#define S1_CLOCK_PRESCALAR    84
#define S1_CLOCK_PERIOD       65535
#define S1_TIMx_IRQ           TIM5_IRQn
#define S1_TIM_IT_CCx         TIM_IT_CC3

#define S2_PORT               GPIOA
#define S2_PIN                GPIO_Pin_0
#define S2_PORT_CLOCK         RCC_AHB1Periph_GPIOA
#define S2_PINSOURCE          GPIO_PinSource0
#define S2_TIMx               TIM5
#define S2_TIMx_CHANNEL       TIM_Channel_1
#define S2_TIMx_CLOCK         RCC_APB1Periph_TIM5
#define S2_AF_TIMx            GPIO_AF_TIM5
#define S2_CLOCK_PRESCALAR    84
#define S2_CLOCK_PERIOD       65535
#define S2_TIMx_IRQ           TIM5_IRQn
#define S2_TIM_IT_CCx         TIM_IT_CC1

void SR4_Config(void);
void SR4_TriggerConfig(void);
void SR4_1_EchoConfig(void);
void SR4_2_EchoConfig(void);
void SR4_3_EchoConfig(void);

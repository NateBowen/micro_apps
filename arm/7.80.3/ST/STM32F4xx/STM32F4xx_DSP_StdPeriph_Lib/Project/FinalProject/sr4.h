#include "main.h"

#define MICROSECONDS_TO_CM      58


#define TRIG_PORT               GPIOA
#define TRIG_PIN                GPIO_Pin_6
#define TRIG_PORT_CLOCK         RCC_AHB1Periph_GPIOA
#define TRIG_PINSOURCE          GPIO_PinSource6
#define TRIG_TIMx               TIM3
#define TRIG_TIMx_CLOCK         RCC_APB1Periph_TIM3
#define TRIG_AF_TIMx            GPIO_AF_TIM3
#define TRIG_CLOCK_PRESCALAR    84
#define TRIG_CLOCK_PERIOD       50000
#define TRIG_PULSE              14

#define ECHO_PORT               GPIOA
#define ECHO_PIN                GPIO_Pin_7
#define ECHO_PORT_CLOCK         RCC_AHB1Periph_GPIOA
#define ECHO_PINSOURCE          GPIO_PinSource7
#define ECHO_TIMx               TIM3
#define ECHO_TIMx_CHANNEL       TIM_Channel_2
#define ECHO_TIMx_CLOCK         RCC_APB1Periph_TIM3
#define ECHO_AF_TIMx            GPIO_AF_TIM3
#define ECHO_CLOCK_PRESCALAR    84
#define ECHO_CLOCK_PERIOD       65535
#define ECHO_TIMx_IRQ           TIM3_IRQn
#define ECHO_TIM_IT_CCx         TIM_IT_CC2

extern uint32_t distance_CM;

void SR4_Config(void);
void SR4_TriggerConfig(void);
void SR4_EchoConfig(void);
uint16_t GetDistance(void);

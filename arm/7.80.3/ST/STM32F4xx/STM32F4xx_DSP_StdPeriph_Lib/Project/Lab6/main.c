#include "main.h"

#define SIG_PIN         GPIO_Pin_15
#define DATA_PINS       0xFF00

GPIO_InitTypeDef        GPIO_InitStructure;
NVIC_InitTypeDef        NVIC_InitStructureMain;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_OCInitTypeDef       TIM_OCInitStructure;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
  this is done through SystemInit() function which is called from startup
  files (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s)
  before to branch to application main. 
  To reconfigure the default setting of SystemInit() function, refer to
  system_stm32f4xx.c file
  */  
  
  uint16_t ticks = ((SystemCoreClock / 2) / (2500)) - 1;
  
  
  /* Time base default values configuration */
//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  /* Output compare default values configuration */
//  TIM_OCStructInit(&TIM_OCInitStructure);
    
  // Set up clocks for all peripherals
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  
  // Set up GPIOC port for SIG_PIN
  GPIO_InitStructure.GPIO_Pin = SIG_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  // Set up GPIOD port for DATA_PINS
  GPIO_InitStructure.GPIO_Pin = DATA_PINS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  // Set up TIM5 base configuration
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
  // Output Compare Timing Mode configuaration: Channel 1
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = ticks;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    
  // Set up NVIC
  NVIC_InitStructureMain.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructureMain.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructureMain.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructureMain.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructureMain);
  
  // Enable TIM5 interrupts
  TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);
  
  // Enable TIM5 counter
  TIM_Cmd(TIM5, ENABLE);
  
  // Infinite loop
  while (1)
  {
    
  }
}

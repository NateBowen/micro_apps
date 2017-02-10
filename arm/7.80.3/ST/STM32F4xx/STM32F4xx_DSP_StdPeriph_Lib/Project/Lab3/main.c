/* Includes */
#include "main.h"

/* Defines */
#define DATA_PINS       0x00FF
#define SIGNAL_PIN      GPIO_Pin_14
#define INITIAL_VALUE   0xA5A5

GPIO_InitTypeDef   GPIO_InitStructure;
EXTI_InitTypeDef   EXTI_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure_Main;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s)
       before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */  

  /* GPIOC and GPIOE Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PA0:PA7 output */
  GPIO_InitStructure.GPIO_Pin = DATA_PINS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PD14 input */
  GPIO_InitStructure.GPIO_Pin = SIGNAL_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);


  /* Connect EXTI Line 14 to PD14 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource14);

  /* Configure EXTI Line14 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line 14 Interrupt to the lowest priority */
  NVIC_InitStructure_Main.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure_Main.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure_Main.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure_Main.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure_Main);

  /* Put Initial Value on GPIOA */
  GPIOA->ODR = INITIAL_VALUE; 
  
  /* Infinite loop */
  while (1)
  {
    
  }
}

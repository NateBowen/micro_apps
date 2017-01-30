/* Includes */
#include "main.h"
#include "stm32f4xx.h"

/* Defines */
#define START_PIN       GPIO_Pin_0
#define ACK_PIN         GPIO_Pin_2
#define SIGNAL_PORT     GPIOC->ODR


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
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PC0 input ~START */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  
  /* Configure PC2 output ~ACK */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  
  /* Configure PE8-PE15 output push-pull mode */
  GPIO_InitStructure.GPIO_Pin = 0xFF00;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure); 
  
  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure_Main.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure_Main.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure_Main.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure_Main.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure_Main);  

  GPIOC->BSRRL = GPIO_Pin_2;

  while (1)
  {  
    /* Check if START line is high and ACK is low */
    if (SIGNAL_PORT == 0) {
      /* Pull up on ACK line */
      GPIOC->BSRRL = GPIO_Pin_2;
    }
    
  }
}
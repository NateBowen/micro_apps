#include "main.h"

void Delay(__IO uint32_t nTime);
extern __IO uint32_t TimingDelay;

signed int portA = 0;
signed int portE = 0;
signed int portD = 0;

GPIO_InitTypeDef   GPIO_InitStructure;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s)
       before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */  
    

  /* The clock generation has been set up to run 100MHz */


  /* Setup SysTick Reload Counter for 100MHz / 1000 = 1ms*/
  SysTick_Config(SystemCoreClock/1000);
  
  /* GPIOA, GPIOD, and GPIOE Peripheral Clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  
  /* Configure PA0:PA7 input */
  GPIO_InitStructure.GPIO_Pin = 0x00FF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure PE8:PE15 input */
  GPIO_InitStructure.GPIO_Pin = 0xFF00;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  /* Confiugure PD0:PD8 output */
  GPIO_InitStructure.GPIO_Pin = 0x01FF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
   
  /* Infinite loop */
  while (1)
  {
    /* Sample every 20ms */
    Delay(20);
    
    /* Read input ports, make sure 8 bits are least significant bytes  */
    portA = GPIOA->IDR;
    portE = GPIOE->IDR >> 8;
    portD = portA + portE;
    
    /* Check for 9th bit after addition (overflow) */
    if(portD & 0x0100)
    {
      /* Extra logic can be used to signal arithmetic overflow */
      /* We just use the 9th bit of output port, so no extra logic is needed */
    }
    
    /* Write sum to output ports*/
    GPIOD->ODR = portD;
  }
}

/* Delay function holds in while loop for duration of SysTick clock (1ms) */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;
  while(TimingDelay != 0);
}
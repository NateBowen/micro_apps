/* ECE 4510 Lab 1 Code-2 */
#include "stm32f4xx.h"
#include "main.h"

#include "extra.h"


/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

void delay(int max_cnt);
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s)
       before to branch to application main. 
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */  

  /* GPIOD Peripheral clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PD12, PD13, PD14, and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  while (1)
  {
    /* Set PD12-15 */
    GPIOD->BSRRL = GPIO_Pin_12; 
    GPIOD->BSRRL = GPIO_Pin_13; 
    GPIOD->BSRRL = GPIO_Pin_14; 
    GPIOD->BSRRL = GPIO_Pin_15; 
    delay(10000000);
    
    /* Reset PD12-15*/
    GPIOD->BSRRH = GPIO_Pin_12;
    GPIOD->BSRRH = GPIO_Pin_13;    
    GPIOD->BSRRH = GPIO_Pin_14;
    GPIOD->BSRRH = GPIO_Pin_15;
    delay(10000000);
  }
}
void delay(int max_cnt)
{
  int cnt = 0;
  while (cnt < max_cnt)
    cnt++;
}

#include "switch.h"

void Switch_Config(void){

  //  Dip Switch PB0 AND PB1
  //  Dip switch START/STOP config
  //  GPIOB

  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(SWITCH_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = STOP_SWITCH | START_SWITCH;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(SWITCH_PORT, &GPIO_InitStructure);                    
}
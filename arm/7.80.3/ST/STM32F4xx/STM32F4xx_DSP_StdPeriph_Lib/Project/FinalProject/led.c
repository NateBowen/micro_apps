#include "led.h"
#include "delay.h"

void LED_Config(void) {

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(LED_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = INDICATOR_LED_PIN | IR_EMITTER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void IndicatorLEDOn(void){
  LED_PORT->ODR |= INDICATOR_LED_PIN;
}

void IndicatorLEDOff(void){
  LED_PORT->ODR &= ~INDICATOR_LED_PIN;
}

void IREmitterOn(void){
  LED_PORT->ODR |= IR_EMITTER_PIN;
}

void IREmitterOff(void){
  LED_PORT->ODR &= ~IR_EMITTER_PIN;
}

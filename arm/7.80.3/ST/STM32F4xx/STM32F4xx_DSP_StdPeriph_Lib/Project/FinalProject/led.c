#include "led.h"
#include "delay.h"

void LED_Config(void) {
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  if((GPIOB->IDR & 0X0001) == 0X0001){   
    
    GPIOB->BSRRL = GPIO_Pin_3;     // IR EMITTER LED OFF   
    
    // CHECK TO SEE IF START DIP SWITCH IS ON
    for(uint8_t i = 0 ; i<=5 ; i++){
      
      GPIOB->BSRRL = GPIO_Pin_2;   // INDICATOR LED ON
      Delay(500);                  // 1/2 SECOND DELAY
      
      GPIOB->BSRRH = GPIO_Pin_2;   // INDICATOR LED OFF
      Delay(500);                  // 1/2 SECOND DELAY
      
      
      // 1 SECOND TOTAL AS SPECIFIED REPEATED FIVE TIMES 
      // 1 BLINK PER SECOND
    }
  }
  
  else if(((GPIOB->IDR & 0X0001) == 0X0001) && ((GPIOB->IDR & 0X0002) == 0X0002)){
    
    GPIOB->BSRRH = GPIO_Pin_3;     // IR EMITTER LED OFF
    // CHECK TO SEE IF START DIP SWITCH IS ON    
    for(uint8_t i = 0; i<=8 ; i++){
      
      GPIOB->BSRRL = GPIO_Pin_2;   // INDICATOR LED ON
      Delay(250);                  // 1/4 SECOND DELAY
      
      GPIOB->BSRRH = GPIO_Pin_2;   // INDICATOR LED OFF
      Delay(250);                  // 1/4 SECOND DELAY
      
      GPIOB->BSRRL = GPIO_Pin_2;   // INDICATOR LED ON
      Delay(250);                  // 1/4 SECOND DELAY
      
      GPIOB->BSRRH = GPIO_Pin_2;   // INDICATOR LED OFF
      Delay(250);                  // 1/4 SECOND DELAY
      
      
      // 1 SECOND TOTAL AS SPECIFIED REPEATED FIVE TIMES 
      // 2 BLINKS PER SECOND
    }
  }
}


void IndicatorLEDOn(void){

}

void IndicatorLEDOff(void){
  
}

void IREmitterOn(void){

}

void IREmitterOff(void){

}

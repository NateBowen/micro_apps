#include "main.h"
#include "adc_config.h"
#include "gpio_config.h"
#include "systick_config.h"


int main(void)
{
  
  GPIO_Config();
  ADC_Config();
  SYSTICK_Config();
  
  TurnOff(Pump1);
  TurnOff(Pump2);
  TurnOff(Filter);
  
  /* Infinite loop */
  while (1)
  {
    
    TurnOn(Pump1);
    while(!SD1){
      //Wait for vat to fill or time to expire
      if(timeOn >= 20){
        TurnOff(Pump1);
      }
    }
    TurnOff(Pump1);
    
    TurnOn(Filter);
    //Wait for saValue to be in range or time to expire
    while(saLevel < (2.7 * 4095)){
      if(timeOn >= 40){
        TurnOff(Filter);
      }
    }
    TurnOff(Filter);
    
    TurnOn(Pump2);
    while(!SD1){
      //Wait for vat to fill or time to expire
      if(timeOn >= 30){
        TurnOff(Pump2);
      }
    }
    TurnOff(Pump2);
    
    Wait50Seconds();
  }
}

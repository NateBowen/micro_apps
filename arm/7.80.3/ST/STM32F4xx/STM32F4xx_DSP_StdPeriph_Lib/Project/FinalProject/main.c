#include "main.h"
#include "delay.h"
#include "buzzer.h"
#include "led.h"
#include "motor.h"
#include "lcd.h"
#include "switch.h"
#include "encoder.h"

int main(void)
{
  Delay_Config();
  LED_Config();
  LCD_Config();
  Buzzer_Config();
  Switch_Config();
  Encoder_Config();
  Motor_Config();
  
  uint16_t frequency;
  uint8_t calculatedDutyCycle;
  
  while (1)
  {  
//    if (!START_SWITCH_HIGH) {
    if (1) {      
      BuzzerOnHigh();
      
      for (uint8_t i = 0; i < NUM_START_BLINKS; i++) {
        IndicatorLEDOn();
        Delay(500);
        IndicatorLEDOff();
        Delay(500);
      }
      
      BuzzerOff();    
      IREmitterOn();
      SetMotorDutyCycle(50);
      
//      while (STOP_SWITCH_HIGH) {
      for(uint8_t i = 0; i < 8; i++){
        frequency = GetEncoderFrequency();
        calculatedDutyCycle = CalculateDutyCycle(frequency);
        SetMotorDutyCycle(calculatedDutyCycle); 
      }
      
      SetMotorDutyCycle(0);
      BuzzerOnLow();
      
      for(uint8_t i = 0; i < NUM_STOP_BLINKS; i++) {
        IndicatorLEDOn();
        Delay(250);
        IndicatorLEDOff();
        Delay(250);
      }
      
      BuzzerOff();
      IREmitterOff();     
    }
  }
}

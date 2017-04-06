#include "main.h"

#define LED_PORT          GPIOB
#define LED_PORT_CLOCK    RCC_AHB1Periph_GPIOB
#define INDICATOR_LED_PIN GPIO_Pin_2
#define IR_EMITTER_PIN    GPIO_Pin_3


#define NUM_START_BLINKS  5
#define NUM_STOP_BLINKS   8

void LED_Config(void);
void IndicatorLEDOn(void);
void IndicatorLEDOff(void);
void IREmitterOn(void);
void IREmitterOff(void);

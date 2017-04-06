#include "main.h"


#define SWITCH_PORT             GPIOB
#define STOP_SWITCH             GPIO_Pin_0
#define START_SWITCH            GPIO_Pin_1
#define SWITCH_PORT_CLOCK       RCC_AHB1Periph_GPIOB

#define STOP_SWITCH_HIGH        (SWITCH_PORT->IDR & STOP_SWITCH)
#define START_SWITCH_HIGH       (SWITCH_PORT->IDR & START_SWITCH)


void Switch_Config(void);

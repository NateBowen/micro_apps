#include "task2.h"
#include "delay.h"
#include "lcd.h"

unsigned int temp = 0;
unsigned int f_temp = 0;
unsigned int updateDisplay = 0;

void task2() {
  gpioSetup();
  TIM2_Config();
  ADC_Config();
  ADC_SoftwareStartConv(ADC1);
  
  char count, ones, tens, hundreds;
  while(1) {
    display(temp);
  };
  
  while (1) {
    if ( updateDisplay ) {
      display(temp);
      updateDisplay = 0;
    }
  }
}

void gpioSetup() {
  GPIO_InitTypeDef GPIO_InitStructure;
  
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//  GPIO_InitStructure.GPIO_Pin = 0x07FF; //pins 0-10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = 0x0001;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIOD->ODR = 0x0000;
}

void display(unsigned int x) {
  char ones, tens, hundreds;
  LCD_Command(0x01); //Clear line, reset cursor
    
  ones = x % 10;
  tens = ((x % 100) - ones) / 10;
  hundreds = (x - tens - ones) / 100;
  
  LCD_WriteDigit(7);  //Write tens digit
  LCD_WriteDigit(1);  //Write ones digit
//  LCD_Write(0x43);  //Write ones digit
  LCD_Write(0x46);
     
  
  Delay(1000); //Wait 1 second
  
}

void TIM2_Config() {
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  TIM_TimeBaseStructure.TIM_Period = SystemCoreClock / 1000 / 2 / 1000 * 25;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 200;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
  
  TIM_Cmd(TIM2, ENABLE);
  
  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
}

static void ADC_Config(void) {
  GPIO_InitTypeDef       GPIO_InitStructure;
  ADC_InitTypeDef        ADC_InitStructure;
  ADC_CommonInitTypeDef  ADC_CommonInitStructure;
  NVIC_InitTypeDef      NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable peripheral clocks *************************************************/
  //  RCC_AHB1PeriphClockCmd( ADC1_2_CHANNEL_GPIO_CLK , ENABLE);
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 , ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* Configure ADC Channel 12 pin as analog input *****************************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* ADC Common configuration *************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  /* ADC1 regular channel 12 configuration ************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_3Cycles);
  
  /* Enable ADC1 **************************************************************/
  ADC_Cmd(ADC1, ENABLE);
  
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
}

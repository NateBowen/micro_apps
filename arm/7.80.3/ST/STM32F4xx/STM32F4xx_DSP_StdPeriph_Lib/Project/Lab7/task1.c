#include "task1.h"
#include "main.h"


/* Private function prototypes -----------------------------------------------*/
static void TIM2_Config(void);
static void DAC_Ch1_Config(void);

//uint16_t SawtoothValue = 0;

int task1(void)
{  
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* GPIOA clock enable (to be used with DAC) */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                         
  
  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  
  /* DAC channel 1 (DAC_OUT1 = PA.4) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  TIM2_Config();  
//  DAC_Ch1_Config();
   
  while (1)
  {  
//    DAC_SetChannel1Data(DAC_Align_12b_R, SawtoothValue);
  }
}

static void TIM2_Config(void)
{
  
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
  
//  /* Time base configuration */
//  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
//  TIM_TimeBaseStructure.TIM_Period = 0xFF;          
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;       
//  TIM_TimeBaseStructure.TIM_ClockDivision = 0;    
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
//  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//  
  /* TIM2 TRGO selection */
//  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
  
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
    /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
  
    /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
  
}

static void DAC_Ch1_Config(void)
{
  DAC_InitTypeDef  DAC_InitStructure;
  
  /* DAC channel1 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  
  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);   
}



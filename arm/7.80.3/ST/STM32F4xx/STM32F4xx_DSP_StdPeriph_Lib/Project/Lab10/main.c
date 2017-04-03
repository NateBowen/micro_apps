#include "main.h"


uint16_t recieved = 0x12;
  
int main(void){
  SysTick_Config(SystemCoreClock / 1000);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  if ( GPIOA->IDR & GPIO_Pin_8 ) { //IS_MASTER ) {
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  } else {
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  }
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  //  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  //  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  //  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  //  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  //  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  // SPI1_NSS CHIP SELECT
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_SPI1);
  // SPI1_SCK
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  // SPI1_MISO
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
  // SPI1_MOSI
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
  
  //  GPIOA->ODR &= ~GPIO_Pin_4;
  
  SPI_Cmd(SPI1, ENABLE);
  
  uint16_t count;
  uint16_t dumbDelay = 0;

  while (1) {  
    if ( GPIOA->IDR & GPIO_Pin_8 ) { //IS_MASTER ) {
        for(count = 0; count < 256; count++){
          while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
          SPI_I2S_SendData(SPI1, count);
          for(dumbDelay = 0; dumbDelay < 0xFFF0; dumbDelay++);     
        }
    } else {
      while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
      recieved = SPI_I2S_ReceiveData(SPI1);
    }
    }
}

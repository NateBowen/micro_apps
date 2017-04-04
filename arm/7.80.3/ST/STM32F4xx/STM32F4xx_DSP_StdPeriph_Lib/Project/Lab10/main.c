#include "main.h"

void writeInstruction(uint16_t data);
void writeData(uint16_t data);
void writeRegs(uint16_t data);
void sendSpi(uint16_t data);
  
int main(void){
  SysTick_Config(SystemCoreClock / 1000);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
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
  
  writeInstruction(0x30);
  writeInstruction(0x30);
  writeInstruction(0x0F);
  writeInstruction(0x01);
  writeInstruction(0x07);
  
  //set extened instruction mode
//  writeInstruction(0x36);
  writeInstruction(0x34);
  writeInstruction(0x36);
  
  writeInstruction(0x80);
  writeInstruction(0x80);
  writeData(0xFF);
  
  for(uint16_t wait = 0; wait < 0xFFF0; wait++);
  writeInstruction(0x01);
  writeData(0xFF);
  
  
  // x=64 y=256 
  //draw BOX
  uint16_t verticalAddress, horizontalAddress;
  for(int x = 1; x <= 14; x++ ) {
    //TOP OF BOX
    verticalAddress = 12;
    horizontalAddress = x;
    //set GRAM address
    writeInstruction(0x80 | verticalAddress);
    writeInstruction(0x80 | horizontalAddress);
    writeData(0xFF);
    
    //BOTTOM BORDER
    verticalAddress = 48;
    horizontalAddress = x;
    writeInstruction(0x80 | verticalAddress);
    writeInstruction(0x80 | horizontalAddress);
    writeData(0xFF);
  }
  for(int y = 12; y < 48; y++ ) {
    verticalAddress = y;
    horizontalAddress = 1;
    writeInstruction(0x80 | verticalAddress);
    writeInstruction(0x80 | horizontalAddress);
    writeData(0x0F);
    
    verticalAddress = y;
    horizontalAddress = 14;
    writeInstruction(0x80 | verticalAddress);
    writeInstruction(0x80 | horizontalAddress);
    writeData(0xF0);
  }
  
  
  //draw 8 chars
  while (1) { 
  }
}


void writeInstruction(uint16_t data) {
  sendSpi(0xF8 | 0x00);
  writeRegs(data);
}

void writeData(uint16_t data) {
  sendSpi(0xF8 | 0x02);
  writeRegs(data);
}

void writeRegs(uint16_t data) {
  sendSpi(data & 0xF0);
  sendSpi((data & 0x0F) << 4);
}

/**
void writeInstruction(uint16_t data) {
  sendSpi(0x1F);
  writeRegs(data);
}

void writeData(uint16_t data) {
  sendSpi(0x1F | 0x50);
  writeRegs(data);
}

void writeRegs(uint16_t data) {
  sendSpi(data & 0x0F);
  sendSpi( (data >> 4) & 0x0F);
}
*/
void sendSpi(uint16_t data) {
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, data);
  for(uint16_t dumbDelay = 0; dumbDelay < 0x0FF0; dumbDelay++);     
}
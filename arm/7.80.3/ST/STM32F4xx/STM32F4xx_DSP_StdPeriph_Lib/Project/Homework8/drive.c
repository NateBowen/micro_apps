#include "drive.h"

void Drive_Config(void){
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(DRIVE_PORT_CLOCK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = DRIVE_LEFT_PIN | DRIVE_RIGHT_PIN | DRIVE_STRAIGHT_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(DRIVE_PORT, &GPIO_InitStructure);
}

void DriveLeft(void){
  DRIVE_PORT->ODR = DRIVE_LEFT_PIN;
}

void DriveRight(void){
  DRIVE_PORT->ODR = DRIVE_RIGHT_PIN;
}

void DriveStraight(void){
  DRIVE_PORT->ODR = DRIVE_STRAIGHT_PIN;
}

void DriveOff(void){
  DRIVE_PORT->ODR = 0;
}

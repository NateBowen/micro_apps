#include "main.h"

#define DRIVE_PORT          GPIOC
#define DRIVE_LEFT_PIN      GPIO_Pin_0
#define DRIVE_RIGHT_PIN     GPIO_Pin_1
#define DRIVE_STRAIGHT_PIN  GPIO_Pin_2
#define DRIVE_PORT_CLOCK    RCC_AHB1Periph_GPIOC

void Drive_Config(void);
void DriveLeft(void);
void DriveRight(void);
void DriveStraight(void);
void DriveOff(void);

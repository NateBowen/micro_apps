#include "main.h"
#include "stm32f4xx_it.h"

/***************************************************************************
The SysTick_Hander takes care of decrementing the global TimingDelay variable
that is used in the Delay() function.
****************************************************************************/

uint32_t TimingDelay;

void SysTick_Handler(void)
{
  TimingDelay--;
}
//
///***************************************************************************
//The CAN1_RX0_IRQHandler 
//****************************************************************************/
//
//void CAN1_RX0_IRQHandler(void)
//{
//  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
//  
//  if ((RxMessage.StdId == 0x321)&&(RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 1))
//  {
//    LED_Display(RxMessage.Data[0]);
//    ubKeyNumber = RxMessage.Data[0];
//  }
//}
#include "stm32f4xx_it.h"
#include "main.h"

extern CanTxMsg TxMessage;
extern CanRxMsg RxMessage;
extern char recievedMsg[8];

int recieveIndex = 0, transmitIndex = 0;

void CAN1_RX0_IRQHandler(void) {
  CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
  
  if ((RxMessage.StdId == 0x321)&&(RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 8)) {
    for(int i = 0; i < 8; i++) {
      recievedMsg[i] = RxMessage.Data[i];
    }
  }
  // trigger transmit... me wants morez
  CAN_Transmit(CANx, &TxMessage);
}

void CAN1_TX_IRQHandler(void) {
  //clear flag
  CAN_ClearFlag(CANx, CAN_FLAG_RQCP0);
}

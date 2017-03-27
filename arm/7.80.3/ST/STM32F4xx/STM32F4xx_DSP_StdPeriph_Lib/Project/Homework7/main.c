#include "main.h"

#define SYN     0x16
#define NAK     0x15
#define ACK     0x06


static void USART_Config(void);

int main(void)
{
  /* USART configuration */
  USART_Config();
  
  uint16_t message;
  uint16_t synErrorCount = 0;
  
  while (1)
  {
    //Read data
    message = USART_ReceiveData(EVAL_COM1);
    //Check data
    if(message == SYN){
      //Check error flags
      if(ERROR_FLAGS){
        //Send NAK and increment/check error count
        USART_SendData(EVAL_COM1, NAK);
        synErrorCount++;
        if(synErrorCount >= 5){
          while(1){
            //End program with a return 1
            return(1);
          }
        }
      }
      else{
        //Send ACK and clear error count
        USART_SendData(EVAL_COM1, ACK);
        synErrorCount = 0;
        //Read data
        message = USART_ReceiveData(EVAL_COM1);
        if (message = VALID_ASCII_CHAR){
          //Check error flags
          if(ERROR_FLAGS){
            //Send NAK and increment/check error count
            USART_SendData(EVAL_COM1, NAK);
            synErrorCount++;
            if(synErrorCount >= 5){
              while(1){
                //End program with a return 1
                return(1);
              }
            }
          }
          else {
            //Send ACK and clear error count
            USART_SendData(EVAL_COM1, ACK);
            synErrorCount = 0;
            //Write message to memory
            MEMORY_LOCATION = message;
            while(1){
              //End program with a return 0
              return(0);
            }
          }
        }
      }
    }
  }
} 

static void USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  
  /* USARTx configured as follow:
  - BaudRate = 50000 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - Even parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 50000;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_Even;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  STM_EVAL_COMInit(COM1, &USART_InitStructure);
}

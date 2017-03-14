#include "main.h"

//#include "prelab_task1.h"
//#include "prelab_task2.h"
//#include "prelab_task3.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"

//uint16_t ADCInputValue;
//uint16_t SawtoothValue = 0;


uint16_t ADCInputValue;  

int main(void)
{
  //  Uncomment only one of these
  //  prelab_task1();
  //  prelab_task2();
  //  prelab_task3();
  //  task1();
//    task2();
    task3();
  /* Infinite loop */
  while (1)
  {   
    //Catch the processor in case the task() functions exit.
  }
}

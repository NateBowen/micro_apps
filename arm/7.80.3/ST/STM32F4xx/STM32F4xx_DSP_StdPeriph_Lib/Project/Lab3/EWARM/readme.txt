 - project .ewd/.eww/.ewp: A pre-configured project file with the provided library 
                           structure that produces an executable image with IAR 
                           Embedded Workbench.
                
 - stm32f4xx_flash.icf : This file is the IAR Linker configuration file used to 
                         place program code (readonly) in internal FLASH and data
                         (readwrite, Stack and Heap)in internal SRAM. 
                         You can customize this file to your need.                                                                                

 - stm32f4xx_flash_extsram.icf: This file is the IAR Linker configuration file 
                                used to place program code (readonly) in internal 
                                FLASH and data (readwrite, Stack and Heap)in 
                                external SRAM. You can customize this file to your need.  
  
 - stm32f4xx_flash_extsdram.icf: This file is the IAR Linker configuration file 
                                 used to place program code (readonly) in internal 
                                 FLASH and data (readwrite, Stack and Heap)in 
                                 external SDRAM. You can customize this file to your need.  
                                                              
 - stm32f4xx_ram.icf:  This file is the IAR Linker configuration file used to 
                       place program code (readonly) and data (readwrite, Stack 
                       and Heap)in internal SRAM. 
                       You can customize this file to your need.                    


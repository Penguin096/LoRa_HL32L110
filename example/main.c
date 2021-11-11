#include "clk.h"
#include "gpio.h"
#include "ddl.h"
#include "uart.h"
#include "bt.h"
//#include "lpm.h"
#include "LoRa.h"

#define TX_OUTPUT_POWER                             20        // dBm
#define LORA_BANDWIDTH                              2         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]

#define BufferSize                                  64


uint8_t Buffer[BufferSize] = "1234567890";
int ledState = FALSE;

int32_t main(void)
{
    stc_clk_config_t stcClkCfg;
    
    // <Before the clock initialization, you can set the clock source to use: set the RCH 24MHz here (the default is 4MHz)
    Clk_SetRCHFreq(ClkFreq4Mhz);
        
    stcClkCfg.enClkSrc  = ClkRCH; // <Select internal RCH as an HCLK clock source;
    stcClkCfg.enHClkDiv = ClkDiv1;
    stcClkCfg.enPClkDiv = ClkDiv1;
    
    Clk_Init(&stcClkCfg);

////////////////////////////////////////////////////////
    Gpio_InitIOExt(0, 3, GpioDirOut, TRUE, FALSE, FALSE, FALSE); //AUX  
    Gpio_InitIO(3, 5, GpioDirIn); //M0
    Gpio_InitIO(3, 6, GpioDirIn); //M1
////////////////////////////////////////////////////////
    
    if (!LoRabegin(868E6)) {
      while (1);
    }
    
    while (1)
    {
              
        if (ledState == FALSE)
          ledState = TRUE;
        else
          ledState = FALSE;   
        
        Gpio_SetIO(0, 3, ledState);
     
        
        LoRabeginPacket(FALSE);
        LoRawrite(Buffer, BufferSize);
        LoRaendPacket(FALSE);
        LoRaidle();
		
		delay1ms(1000);  
    }
}
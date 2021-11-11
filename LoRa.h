// Copyright (c) Penguin096. All rights reserved.

#ifndef LORA_H
#define LORA_H
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "spi.h"
   
#ifdef __DEBUG   
#include "uart.h"
#endif
   
#ifdef __cplusplus
extern "C"
{
#endif
 
#define LORA_CTRL_PORT                  3
#define LORA_NCTRL_PIN                  3
#define LORA_CTRL_PIN                   4
  
#define LORA_RESET_PORT                 3
#define LORA_RESET_PIN                  2


#define PA_OUTPUT_RFO_PIN          0
#define PA_OUTPUT_PA_BOOST_PIN     1

    int LoRabegin(long frequency);
    void LoRaend();

    int LoRabeginPacket(int implicitHeader);
    int LoRaendPacket(boolean_t async);

    int LoRaparsePacket(int size);
    int LoRapacketRssi();
    float LoRapacketSnr();
    long LoRapacketFrequencyError();

    int LoRarssi();

    // from Print
    size_t LoRawrite(const uint8_t *buffer, size_t size);

    // from Stream
    int LoRaavailable();
    int LoRaread();
    int LoRapeek();

    void LoRaonReceive(void(*callback)(int));
    void LoRaonTxDone(void(*callback)());

    void LoRareceive(int size);

    void LoRaidle();
    void LoRasleep();

    void LoRasetTxPower(int level, int outputPin);
    void LoRasetFrequency(long frequency);
    void LoRasetSpreadingFactor(int sf);
    void LoRasetSignalBandwidth(long sbw);
    void LoRasetCodingRate4(int denominator);
    void LoRasetPreambleLength(long length);
    void LoRasetSyncWord(int sw);
    void LoRaenableCrc();
    void LoRadisableCrc();
    void LoRaenableInvertIQ();
    void LoRadisableInvertIQ();
    
    void LoRasetOCP(uint8_t mA); // Over Current Protection control
    
    void LoRasetGain(uint8_t gain); // Set LNA gain

    // deprecated
    void LoRaenableCrc();
    void LoRadisableCrc();

    int LoRarandom();
   
    void LoRaSetOpMode( uint8_t opMode );

//extern LoRaClass LoRa;

#ifdef __cplusplus
#endif

#endif /* __UART_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
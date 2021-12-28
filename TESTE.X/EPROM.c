#include <xc.h>
#include "EPROM.h"
#include "./mcc_generated_files/EEPROM2_app.h"

uint32_t operADDR(uint8_t operation){
    uint32_t dataAddr;
    switch (operation){
        case OPER_MIN_TEMP:     //NOTE Temperature minimum
            dataAddr = 0x10AB01;
            break;

        case OPER_MAX_TEMP:     //NOTE Temperature maximum
            dataAddr = 0x10AB07;
            break;

        case OPER_MIN_LUM:     //NOTE Luminosity minimum
            dataAddr = 0x10AB0D;
            break;

        case OPER_MAX_LUM:     //NOTE Luminosity maximum
            dataAddr = 0x10AB13;
            break;

        default:
            dataAddr = 0x10BB13;
            break;

    }
    return dataAddr;
}

void initializeEPROM(){
    uint8_t writeBuffer[] = {MAGIC_WORD,NREG_EPROM, NR_EPROM, WI_EPROM, RI_EPROM,PMON_EPROM,TALA_EPROM,ALAT_EPROM,ALAL_EPROM,ALAF_EPROM,CLKH_EPROM,CLKM_EPROM,CHECKSUM};

    EEPROM2_WriteBlock(writeBuffer,13,INITIALIZATION_ADDRESS);
}

void storeEPROMBuild(uint8_t hours,uint8_t minutes,uint8_t seconds,uint8_t temperature,uint8_t luminosity,uint8_t operation){
    uint32_t dataAddr;

    dataAddr = operADDR(operation);
    uint8_t writeBuffer[] = {hours, minutes, seconds, temperature,luminosity};

    EEPROM2_WriteBlock(writeBuffer,5,dataAddr);
}

void storeEPROMFeed(uint8_t data,uint8_t operation){
    uint32_t dataAddr;

    dataAddr = operADDR(operation);
    //EEPROM2_WriteBlock(data,5,dataAddr);
}

uint8_t *fetchEPROM(uint8_t operation){
    uint32_t dataAddr;
    uint8_t readBuffer[5];

    dataAddr = operADDR(operation);
    EEPROM2_ReadBlock(readBuffer,5,dataAddr);
    return readBuffer;
}

uint8_t *fetchEPROMInitialization(){
    uint8_t readBuffer[13];

    EEPROM2_ReadBlock(readBuffer,13,INITIALIZATION_ADDRESS);
    return readBuffer;
}
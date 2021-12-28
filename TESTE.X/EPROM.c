#include <xc.h>
#include "EPROM.h"
#include "EEPROM2_app.h"

uint8_t operADDR(int operation){
    uint8_t dataAddr;
    switch (operation){
        case MIN_TEMP:     //NOTE Temperature minimum
            dataAddr = 0x10AB01;
            break;

        case MAX_TEMP:     //NOTE Temperature maximum
            dataAddr = 0x10AB07;
            break;

        case MIN_LUM:     //NOTE Luminosity minimum
            dataAddr = 0x10AB0D;
            break;

        case MAX_LUM:     //NOTE Luminosity maximum
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

void storeEPROMBuild(int hours,int minutes,int seconds,int temperature,int luminosity,int operation){
    uint8_t dataAddr;

    dataAddr = operADDR(operation);
    uint8_t writeBuffer[] = {hours, minutes, seconds, temperature,luminosity};

    EEPROM2_WriteBlock(writeBuffer,5,dataAddr);
}

void storeEPROMFeed(uint8_t data,int operation){
    uint8_t dataAddr;

    dataAddr = operADDR(operation);
    EEPROM2_WriteBlock(data,5,dataAddr);
}

uint8_t fetchEPROM(int operation){
    uint8_t readBuffer[5];

    dataAddr = operADDR(operation);
    EEPROM2_ReadBlock(readBuffer,5,dataAddr);
    return readBuffer;
}

uint8_t fetchEPROMInitialization(){
    uint8_t readBuffer[13];

    EEPROM2_ReadBlock(readBuffer,13,INITIALIZATION_ADDRESS);
    return readBuffer;
}
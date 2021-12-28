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

void fetchEPROM(uint8_t operation,uint8_t* readBuffer){
    uint32_t dataAddr;
    dataAddr = operADDR(operation);
    EEPROM2_ReadBlock(readBuffer,5,dataAddr);
}

void fetchEPROMInitialization(uint8_t* readBuffer){
    EEPROM2_ReadBlock(readBuffer,13,INITIALIZATION_ADDRESS);
}

void parseEPROMReading(uint8_t* hours,uint8_t* minutes,uint8_t* seconds,uint8_t* temperature,uint8_t* luminosity,uint8_t operation){
    uint8_t readBuffer[5];
    fetchEPROM(operation,readBuffer);
    *hours = readBuffer[0];
    *minutes = readBuffer[1];
    *seconds = readBuffer[2];
    *temperature = readBuffer[3];
    *luminosity = readBuffer[4];
}

void parseEPROMInitialization(uint8_t* magic_word,uint8_t* NREG,uint8_t* NR,uint8_t* WI,uint8_t* RI,uint8_t* PMON,uint8_t* TALA,uint8_t* ALAT,uint8_t* ALAL,uint8_t* ALAF,uint8_t* CLKH,uint8_t* CLKM,uint8_t* checksum){
    uint8_t readBuffer[13];
    fetchEPROMInitialization(readBuffer);
    *magic_word = readBuffer[0];
    *NREG = readBuffer[1];
    *NR = readBuffer[2];
    *WI = readBuffer[3];
    *RI = readBuffer[4];
    *PMON = readBuffer[5];
    *TALA = readBuffer[6];
    *ALAT = readBuffer[7];
    *ALAL = readBuffer[8];
    *ALAF = readBuffer[9];
    *CLKH = readBuffer[10];
    *CLKM = readBuffer[11];
    *checksum = readBuffer[12];
}
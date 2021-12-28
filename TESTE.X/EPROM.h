#ifndef __EPROM_H
#define __EPROM_H

#define INITIALIZATION_ADDRESS 0x10AA01

#define MAGIC_WORD 0xAA 
#define CHECKSUM 0XE3
#define OPER_MIN_TEMP 100
#define OPER_MAX_TEMP 101
#define OPER_MIN_LUM 102
#define OPER_MAX_LUM 103

#define NREG_EPROM 10   
#define NR_EPROM 0    
#define WI_EPROM 0 
#define RI_EPROM 0 
#define PMON_EPROM 5  
#define TALA_EPROM 3
#define ALAT_EPROM 25    
#define ALAL_EPROM 2    
#define ALAF_EPROM 0
#define CLKH_EPROM 12    
#define CLKM_EPROM 0    

uint32_t operADDR(uint8_t operation);
void initializeEPROM();
void storeEPROMBuild(uint8_t hours,uint8_t minutes,uint8_t seconds,uint8_t temperature,uint8_t luminosity,uint8_t operation);
void storeEPROMFeed(uint8_t data,uint8_t operation);
uint8_t *fetchEPROM(uint8_t operation);
uint8_t *fetchEPROMInitialization();

#endif
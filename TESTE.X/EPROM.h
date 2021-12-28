#ifndef __EPROM_H
#define __EPROM_H

#define INITIALIZATION_ADDRESS 0x10AA01

#define MAGIC_WORD 0xAA 
#define CHECKSUM 0XE3
#define OPER_MIN_TEMP 90016
#define OPER_MAX_TEMP 90068
#define OPER_MIN_LUM 90021
#define OPER_MAX_LUM 90111

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

uint8_t operADDR(int operation);
void initializeEPROM();
void storeEPROMBuild(int hours,int minutes,int seconds,int temperature,int luminosity,int operation);
void storeEPROMFeed(uint8_t data,int operation);
uint8_t fetchEPROM(int operation);
uint8_t fetchEPROMInitialization();

#endif
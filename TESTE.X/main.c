/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18875
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "I2C/i2c.h"
#include "LCD/lcd.h"
#include "stdio.h"
#include "EPROMlib.h"

/*
                         Main application
*/

#define LUM_LVL_01  0xFF
#define LUM_LVL_12  0x1FE
#define LUM_LVL_23  0x2FD
#define START_RING_BUFFER_ADDR 0x7000
#define COUNTER_ADDR 0x7050
#define LAST_TEMP 0x7051
#define LAST_LUX 0x7052
#define HIGH_TEMP_REG 0x7053
#define LOW_TEMP_REG 0x7054
#define HIGH_LUX_REG 0x7055
#define LOW_LUX_REG 0x7056



void S1(void){
    if(IO_RB4_GetValue()==LOW && IO_RA6_GetValue()==HIGH){
        IO_RA6_SetLow();
    }
}

void timerInterrupt(void){
    
    uint8_t counter = DATAEE_ReadByte(COUNTER_ADDR);
    
    //os ints nao sao necessarios mas ja nao tava a percerber nada do que estava a ver
    uint8_t last_temperature = DATAEE_ReadByte(LAST_TEMP);
    uint8_t last_luminosity = DATAEE_ReadByte(LAST_LUX);
    uint8_t max_temperature = DATAEE_ReadByte(HIGH_TEMP_REG);
    uint8_t min_temperature = DATAEE_ReadByte(LOW_TEMP_REG);
    uint8_t max_luminosity = DATAEE_ReadByte(HIGH_LUX_REG);
    uint8_t min_luminosity = DATAEE_ReadByte(LOW_LUX_REG);
   
    if(counter == 5){
    
        if(last_temperature > max_temperature){
            
            DATAEE_WriteByte(HIGH_TEMP_REG, last_temperature);
            //alarme
            
        }else if(last_temperature < min_temperature){
        
            DATAEE_WriteByte(LOW_TEMP_REG, last_temperature); 
            //alarme
        }
        if(last_luminosity > max_luminosity){
            
            DATAEE_WriteByte(HIGH_LUX_REG, last_luminosity);
            //alarme
            
        }else if(last_luminosity < min_luminosity){
        
            DATAEE_WriteByte(LOW_LUX_REG, last_luminosity);
            //alarme
        } 
    }
 
    if(counter == 5){
    
        counter == 1;
    }else{      
        counter ++;
    }
    
    DATAEE_WriteByte(COUNTER_ADDR, counter);
    
    if(IO_RA7_GetValue()==LOW){
        IO_RA7_SetHigh();
    }else{
        IO_RA7_SetLow();
    }
    adc_result_t value = ADCC_GetSingleConversion(channel_ANA0);
    if(value > LUM_LVL_23 || value < LUM_LVL_01){
        IO_RA4_SetHigh();
    }else{
        IO_RA4_SetLow();
    }
}

unsigned char readTC74 (void)
{
	unsigned char value;
do{
	IdleI2C();
	StartI2C(); IdleI2C();
    
	WriteI2C(0x9a | 0x00); IdleI2C();
	WriteI2C(0x01); IdleI2C();
	RestartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x01); IdleI2C();
	value = ReadI2C(); IdleI2C();
	NotAckI2C(); IdleI2C();
	StopI2C();
} while (!(value & 0x40));

	IdleI2C();
	StartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x00); IdleI2C();
	WriteI2C(0x00); IdleI2C();
	RestartI2C(); IdleI2C();
	WriteI2C(0x9a | 0x01); IdleI2C();
	value = ReadI2C(); IdleI2C();
	NotAckI2C(); IdleI2C();
	StopI2C();

	return value;
}

//iniciar os 4 registos com máximos e minimos
//not sure com que valores inicializar os registos
void initializeREG(){
    
        uint8_t aux = 1;
    
    DATAEE_WriteByte(COUNTER_ADDR, aux);
    DATAEE_WriteByte(HIGH_TEMP_REG,(uint8_t) OPER_MAX_TEMP);
    DATAEE_WriteByte(LOW_TEMP_REG,(uint8_t) OPER_MIN_TEMP);
    DATAEE_WriteByte(HIGH_LUX_REG + 2,(uint8_t) OPER_MAX_LUM);
    DATAEE_WriteByte(LOW_LUX_REG + 3,(uint8_t) OPER_MIN_LUM);

}

//retorna o writeRingBufferAddr atualizado para a proxima escrita
//ordem de escrita é: horas -> minutos -> segundos -> temperatura -> luminosidade -> horas -> (...)
//writeRingBufferAddr = writeRingBuffer(...)
uint16_t writeRingBuffer(uint16_t writeRingBufferAddr,uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t temperature, uint8_t luminosity){
    
    
    uint8_t prev_temperature;
    uint8_t prev_luminosity;
    
    if(writeRingBufferAddr == (START_RING_BUFFER_ADDR)){
        
        prev_temperature = DATAEE_ReadByte(writeRingBufferAddr + 23);
        prev_luminosity = DATAEE_ReadByte(writeRingBufferAddr + 24);
        
    }else{
        
        prev_temperature = DATAEE_ReadByte(writeRingBufferAddr -2);
        prev_luminosity = DATAEE_ReadByte(writeRingBufferAddr -1);
    }
    
    if(prev_temperature != temperature || prev_luminosity != luminosity){
        
        DATAEE_WriteByte(writeRingBufferAddr, hours);
        DATAEE_WriteByte(writeRingBufferAddr + 1, minutes);
        DATAEE_WriteByte(writeRingBufferAddr + 2, seconds);
        DATAEE_WriteByte(writeRingBufferAddr + 3, temperature);
        DATAEE_WriteByte(writeRingBufferAddr + 4, luminosity);   
        
        DATAEE_WriteByte(LAST_TEMP, temperature);
        DATAEE_WriteByte(LAST_LUX, luminosity);
    }
    
    if(writeRingBufferAddr == (START_RING_BUFFER_ADDR + 20)){
        
        writeRingBufferAddr = START_RING_BUFFER_ADDR;
        
    }else{
        
        writeRingBufferAddr =  writeRingBufferAddr* + 5;
    }
    return writeRingBufferAddr;
}

void main(void)
{
    unsigned char c;
    char buf[17];

    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    TMR1_SetInterruptHandler(timerInterrupt);
    
    IO_RA6_SetHigh();
     
    OpenI2C();
    //I2C_SCL = 1;
    //I2C_SDA = 1;
    //WPUC3 = 1;
    //WPUC4 = 1;
    //LCDinit();

    initializeEPROM();
    
    initializeREG();

    storeEPROMBuild(0x55,0x50,0x45,0x40,0x35,OPER_MAX_TEMP);
    

            
    uint16_t writeRingBufferAddr = START_RING_BUFFER_ADDR; 
    uint16_t readRingBufferAddr = START_RING_BUFFER_ADDR; 
    
    uint8_t hours,minutes,seconds,temperature,luminosity;
    uint8_t magic_word,NREG,NR,WI,RI,PMON,TALA,ALAT,ALAL,ALAF,CLKH,CLKM,checksum;
    uint8_t correct_EPROM;
    while (1)
    {   
        S1();
        parseEPROMReading(&hours,&minutes,&seconds,&temperature,&luminosity,OPER_MAX_TEMP);
        correct_EPROM = parseEPROMInitialization(&magic_word,&NREG,&NR,&WI,&RI,&PMON,&TALA,&ALAT,&ALAL,&ALAF,&CLKH,&CLKM,&checksum);
        
        /*c = readTC74();
        LCDcmd(0x80);       //first line, first column
        while (LCDbusy());
        LCDstr("Temp");
        LCDpos(0,8);
        while (LCDbusy());
        LCDstr("STR-RTS");
        LCDcmd(0xc0);       // second line, first column
        sprintf(buf, "%02d C", c);
        while (LCDbusy());
        LCDstr(buf);*/
        __delay_ms(2000);
    }
}
/**
 End of File
*/
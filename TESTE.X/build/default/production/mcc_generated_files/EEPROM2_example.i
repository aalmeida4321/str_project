# 1 "mcc_generated_files/EEPROM2_example.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC16F1xxxx_DFP/1.7.146/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "mcc_generated_files/EEPROM2_example.c" 2
# 23 "mcc_generated_files/EEPROM2_example.c"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdint.h" 2 3
# 23 "mcc_generated_files/EEPROM2_example.c" 2

# 1 "mcc_generated_files/delay.h" 1
# 34 "mcc_generated_files/delay.h"
void DELAY_milliseconds(uint16_t milliseconds);
void DELAY_microseconds(uint16_t microseconds);
# 24 "mcc_generated_files/EEPROM2_example.c" 2

# 1 "mcc_generated_files/EEPROM2_app.h" 1
# 28 "mcc_generated_files/EEPROM2_app.h"
void EEPROM2_WriteByte (uint8_t byteData, uint32_t byteAddr);
uint8_t EEPROM2_ReadByte (uint32_t address);
void EEPROM2_WriteBlock(uint8_t *writeBuffer, uint8_t buflen, uint32_t startAddr);
void EEPROM2_ReadBlock(uint8_t *readBuffer, uint8_t buflen, uint32_t startAddr);
uint8_t EEPROM2_WritePoll(void);
# 25 "mcc_generated_files/EEPROM2_example.c" 2


uint8_t writeBuffer[] = {0x1A, 0x2A, 0x4A, 0x8A};
uint8_t readBuffer[10];
uint8_t addressBuffer[] = {0xAB,0x00,0x10};
uint8_t readByte;

void EEPROM2_example(void)
{

    EEPROM2_WriteByte(0xA5,0x10AB01);


    EEPROM2_WritePoll();


    readByte = EEPROM2_ReadByte(0x10AB01);


    DELAY_milliseconds(10);


    EEPROM2_WriteBlock(writeBuffer,4,0x10AB02);


    EEPROM2_WritePoll();


    EEPROM2_ReadBlock(readBuffer,4,0x10AB02);
}

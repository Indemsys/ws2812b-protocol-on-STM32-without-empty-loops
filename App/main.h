#ifndef __MAIN
  #define __MAIN

  #define COMC_NUM                3      // Количество коммуникационных каналов
  #define COMC_IN_BUF_SZ          0x100  // Должно быть целой степенью 2
  #define COMC_OUT_BUF_SZ         0x100  // Должно быть целой степенью 2

  #define LEDS_NUM    80
  #define COLRS       3


  #define ASIZE  18000 // Настройка для  задержки копирования массива = 250 мкс

  #ifdef __GLOBAL__

char comc_input_buf[COMC_NUM][COMC_IN_BUF_SZ];
char comc_output_buf[COMC_NUM][COMC_OUT_BUF_SZ];

INT16U DMA_buf[LEDS_NUM+2][COLRS][8];

volatile INT8U buf1[ASIZE];
volatile INT8U buf2[ASIZE];

INT32U LEDS_buf[LEDS_NUM]; 

  #else

extern char comc_input_buf[COMC_NUM][COMC_IN_BUF_SZ];
extern char comc_output_buf[COMC_NUM][COMC_OUT_BUF_SZ];

extern INT16U DMA_buf[LEDS_NUM+2][COLRS][8];
extern volatile INT8U buf1[ASIZE];
extern volatile INT8U buf2[ASIZE];

extern INT32U LEDS_buf[LEDS_NUM]; 

  #endif

void Delay_ms(INT32U n);

#endif

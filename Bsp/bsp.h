#ifndef __APP_BSP
  #define __APP_BSP

  #define  PCLK2 72e6f
  #define  PCLK1 36e6f



  #define  LEDS_PATTERM_MAX_SIZE  64


  #define  BYTE_FROM_UART_EVNT     0x0001  // Флаг для многих задач



  #include <RTL.h>
  #include <math.h>
  #include <string.h>
  #include <stdarg.h>
  #include <stdio.h>
  #include <math.h>
  #include <time.h>
  #include <stdlib.h>
  #include <ctype.h>

  #include "app_types.h"
  #include "stm32f4xx.h" 
  #include "..\app\main.h"
  #include "..\app\IO_funcs.h"
  #include "stm32f4xx_VIC.h" 
  #include "stm32f4xx_timers.h" 
  #include "stm32f4xx_DMA.h" 
  #include "stm32f4xx_UART.h" 

  #include "..\app\LEDs_strip.h"



extern void Delay_m8(int cnt); // Задержка на (cnt+1)*8 тактов . Передача нуля недопускается

// Настройка для тактовой частоты ядра 144 МГц
  #define  DELAY_1us Delay_m8(18)
  #define  DELAY_2us Delay_m8(2*18)
  #define  DELAY_4us Delay_m8(4*18)
  #define  DELAY_8us Delay_m8(8*18)

  #define  DELAY_MS(x) Delay_m8(x*1000ul*18)
#endif

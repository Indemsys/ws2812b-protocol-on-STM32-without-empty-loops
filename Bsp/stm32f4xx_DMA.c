#include "bsp.h"


/*------------------------------------------------------------------------------

 ------------------------------------------------------------------------------*/
void Clear_DMA(void)
{
  DMA_TypeDef *dma = DMA1;
  dma->HIFCR = 0x0FFFFFFF;  // Очитить флаги во всех каналах DMA
}

/*------------------------------------------------------------------------------
  Инициализация канала 2 DMA1 Stream 7
  Используется для пересылки шаблоной битов потока управления светодиодной лентой на WS2812B в таймер TMR4 работающий в режиме генерации PWM 
 ------------------------------------------------------------------------------*/
void DMA1_Stream7_Mem_to_TMR4_init(void)
{
  DMA_Stream_TypeDef *dma_ch = DMA1_Stream7;
//  NVIC_InitTypeDef istruct;
  RCC_TypeDef *rcc = RCC;

  rcc->AHB1ENR |= BIT(21);               // Разрешаем DMA1

  dma_ch->CR = 0;    // Выключаем стрим
  dma_ch->PAR = (unsigned int)&(TIM4->CCR3) + 1;  // Назначаем адрес регистра данных ADC
  dma_ch->M0AR = (unsigned long)&DMA_buf;
//  dma_ch->M1AR = (unsigned long)&ledbits;
  dma_ch->NDTR = (LEDS_NUM + 2) * COLRS * 8;
  dma_ch->CR =
               LSHIFT(2, 25) + // CHSEL[2:0]: Channel selection |    010: channel 2 selected
               LSHIFT(0, 23) + // MBURST: Memory burst transfer configuration | 00: single transfer
               LSHIFT(0, 21) + // PBURST[1:0]: Peripheral burst transfer configuration | 00: single transfer
               LSHIFT(0, 19) + // CT: Current target (only in double buffer mode) | 0: The current target memory is Memory 0 (addressed by the DMA_SxM0AR pointer)
               LSHIFT(0, 18) + // DBM: Double buffer mode | 0: No buffer switching at the end of transfer
               LSHIFT(3, 16) + // PL[1:0]: Priority level | 11: Very high.  PL[1:0]: Priority level
               LSHIFT(0, 15) + // PINCOS: Peripheral increment offset size | 0: The offset size for the peripheral address calculation is linked to the PSIZE
               LSHIFT(1, 13) + // MSIZE[1:0]: Memory data size | 00: 8-bit. Memory data size
               LSHIFT(1, 11) + // PSIZE[1:0]: Peripheral data size | 00: 8-bit. Peripheral data size
               LSHIFT(1, 10) + // MINC: Memory increment mode | 1: Memory address pointer is incremented after each data transfer (increment is done according to MSIZE)
               LSHIFT(0, 9) +  // PINC: Peripheral increment mode | 0: Peripheral address pointer is fixed
               LSHIFT(1, 8) +  // CIRC: Circular mode | 1: Circular mode enabled
               LSHIFT(1, 6) +  // DIR[1:0]: Data transfer direction | 01: Memory-to-peripheral
               LSHIFT(0, 5) +  // PFCTRL: Peripheral flow controller | 1: The peripheral is the flow controller
               LSHIFT(1, 4) +  // TCIE: Transfer complete interrupt enable | 1: TC interrupt enabled
               LSHIFT(0, 3) +  // HTIE: Half transfer interrupt enable | 0: HT interrupt disabled
               LSHIFT(0, 2) +  // TEIE: Transfer error interrupt enable | 0 : TE interrupt disabled
               LSHIFT(0, 1) +  // DMEIE: Direct mode error interrupt enable | 0: Direct mode error interrupt disabled
               LSHIFT(0, 0) +  // EN: Stream enable | 1: Stream enabled
               0;

  dma_ch->FCR =
                LSHIFT(0, 7) + // FEIE: FIFO error interrupt enable
                LSHIFT(1, 2) + // DMDIS: Direct mode disable | 1: Direct mode disabled. Разрешаем чтобы была возможность пересылки из байт в двухбайтовый регистр 
                LSHIFT(1, 0) + // FTH[1:0]: FIFO threshold selection | 01: 1/2 full FIFO
                0;

//  istruct.NVIC_IRQChannel = DMA1_Stream7_IRQn; // Enable the DMAChannel1 Interrupt
//  istruct.NVIC_IRQChannelPreemptionPriority = 2;
//  istruct.NVIC_IRQChannelSubPriority = 0;
//  istruct.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&istruct);

  dma_ch->CR |= BIT(0); //  1: Stream enabled
}

/*------------------------------------------------------------------------------
  Прерывание после пересылки из памяти в LED ленту
 ------------------------------------------------------------------------------*/
void DMA1_Stream7_IRQHandler(void)
{
  DMA_TypeDef *dma = DMA1;

  dma->HIFCR = BIT(27); // CTCIF7: Stream 7 clear transfer complete interrupt flag. Сброс флага прерывания

}




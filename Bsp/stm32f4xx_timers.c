#include "bsp.h"


/*------------------------------------------------------------------------------
  Timer4 генерирует импульсы на светодиодную полосу
  Тактирование таймера идет от PCLK1 72 MHz

  Канал 3 таймера используется в режиме Compare с загрузкой по DMA регистра CCR3 для формирования битовых сигналов
 ------------------------------------------------------------------------------*/
void Timer4_init(void)
{
  TIM_TypeDef *tim = TIM4;
  RCC_TypeDef *rcc = RCC;

  rcc->APB1RSTR |= BIT(2);    // Сброс таймера 4
  rcc->APB1RSTR &= ~BIT(2);   
  rcc->APB1ENR |= BIT(2);     // Разрешаем тактирование таймера 4
  tim->CR1 = BIT(7);          //  1: TIMx_ARR register is buffered.
  tim->CR2 = 0;               
  tim->PSC = 0;               // Предделитель генерирует частоту 72 МГц
  tim->ARR = 90 - 1;          // Перегрузка таймера каждые 1.25 мкс
  tim->CCMR2 = 0
               + LSHIFT(6, 4) // OC3M: Output compare 3 mode | 110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
               + LSHIFT(1, 3) // OC3PE: Output compare 3 preload enable
               + LSHIFT(0, 0) // CC3S: Capture/Compare 3 selection | 00: CC3 channel is configured as output
  ; 
  tim->CNT = 0;
  tim->CCR3 = 0;
  tim->DIER = BIT(11);        // Bit 11 CC3DE: Capture/Compare 3 DMA request enable. Разрешаем запросы DMA
  tim->CR1 |= BIT(0);         // Запускаем таймер
  tim->CCER = BIT(8);         // Разрешаем работы выхода, чтобы возникали сигналы для DMA
}








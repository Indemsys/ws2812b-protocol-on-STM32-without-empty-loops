#include "bsp.h"


/*------------------------------------------------------------------------------
  Timer4 ���������� �������� �� ������������ ������
  ������������ ������� ���� �� PCLK1 72 MHz

  ����� 3 ������� ������������ � ������ Compare � ��������� �� DMA �������� CCR3 ��� ������������ ������� ��������
 ------------------------------------------------------------------------------*/
void Timer4_init(void)
{
  TIM_TypeDef *tim = TIM4;
  RCC_TypeDef *rcc = RCC;

  rcc->APB1RSTR |= BIT(2);    // ����� ������� 4
  rcc->APB1RSTR &= ~BIT(2);   
  rcc->APB1ENR |= BIT(2);     // ��������� ������������ ������� 4
  tim->CR1 = BIT(7);          //  1: TIMx_ARR register is buffered.
  tim->CR2 = 0;               
  tim->PSC = 0;               // ������������ ���������� ������� 72 ���
  tim->ARR = 90 - 1;          // ���������� ������� ������ 1.25 ���
  tim->CCMR2 = 0
               + LSHIFT(6, 4) // OC3M: Output compare 3 mode | 110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
               + LSHIFT(1, 3) // OC3PE: Output compare 3 preload enable
               + LSHIFT(0, 0) // CC3S: Capture/Compare 3 selection | 00: CC3 channel is configured as output
  ; 
  tim->CNT = 0;
  tim->CCR3 = 0;
  tim->DIER = BIT(11);        // Bit 11 CC3DE: Capture/Compare 3 DMA request enable. ��������� ������� DMA
  tim->CR1 |= BIT(0);         // ��������� ������
  tim->CCER = BIT(8);         // ��������� ������ ������, ����� ��������� ������� ��� DMA
}








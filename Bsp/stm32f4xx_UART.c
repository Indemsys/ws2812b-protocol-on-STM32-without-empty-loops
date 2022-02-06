#include "bsp.h"


static volatile unsigned int comc_in_buf_head[COMC_NUM];
static volatile unsigned int comc_in_buf_tail[COMC_NUM];

static volatile unsigned int comc_out_buf_head[COMC_NUM];
static volatile unsigned int comc_out_buf_tail[COMC_NUM];



static volatile unsigned char dummy;

int comc_send_cont;
/*-------------------------------------------------------------------------------------------------------------
  Сброс UART c номером n
-------------------------------------------------------------------------------------------------------------*/
void UART_reset(INT8U n)
{
  RCC_TypeDef *rcc;

  rcc = RCC;

  switch( n )
  {
    case SD_UART1:
      rcc->APB2ENR  = rcc->APB2ENR  |  BIT(4);
      rcc->APB2RSTR = rcc->APB2RSTR |  BIT(4);
      rcc->APB2RSTR = rcc->APB2RSTR & ~BIT(4);
      break;
    case SD_UART2:
      rcc->APB1ENR  = rcc->APB1ENR  |  BIT(17);
      rcc->APB1RSTR = rcc->APB1RSTR |  BIT(17);
      rcc->APB1RSTR = rcc->APB1RSTR & ~BIT(17);
      break;
    case SD_UART3:
      rcc->APB1ENR  = rcc->APB1ENR  |  BIT(18);
      rcc->APB1RSTR = rcc->APB1RSTR |  BIT(18);
      rcc->APB1RSTR = rcc->APB1RSTR & ~BIT(18);
      break;
  }
}


/*-------------------------------------------------------------------------------------------------------------
  Инициализация UART

  PCLK2 = 72 MHz - тактирует USART1
  PCLK1 = 36 MHz - тактирует USART2, USART3
-------------------------------------------------------------------------------------------------------------*/
void Init_UART(INT8U n,INT32U baudrate,INT8U sb,INT8U pb,INT8U db)
{
  USART_TypeDef *puart;
  switch( n )
  {
    case SD_UART1:
      puart = USART1;
      break;
    case SD_UART2:
      puart = USART2;
      break;
    case SD_UART3:
      puart = USART3;
      break;
    default: return;
  }
  UART_reset(n);
  UART_disable(puart);
  UART_set_baude_rate(n,baudrate);
  UART_set_stop_bits(puart,sb);
  UART_set_data_bits(puart,db);
  UART_set_parity_bits(puart,pb);
  UART_enable(puart);

}

/*-------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------*/
void Init_UART_interrupt(INT8U n)
{
  NVIC_InitTypeDef istruct;
  USART_TypeDef    *puart;

  switch( n )
  {
    case SD_UART1:
      istruct.NVIC_IRQChannel                   = USART1_IRQn; 
      istruct.NVIC_IRQChannelPreemptionPriority = 1;
      istruct.NVIC_IRQChannelSubPriority        = 0;
      puart = USART1;
      break;
    case SD_UART2:
      istruct.NVIC_IRQChannel                   = USART2_IRQn; 
      istruct.NVIC_IRQChannelPreemptionPriority = 1;
      istruct.NVIC_IRQChannelSubPriority        = 0;
      puart = USART2;
      break;
    case SD_UART3:
      istruct.NVIC_IRQChannel                   = USART3_IRQn; 
      istruct.NVIC_IRQChannelPreemptionPriority = 1;
      istruct.NVIC_IRQChannelSubPriority        = 0;
      puart = USART3;
      break;
    default: return;
  }
  istruct.NVIC_IRQChannelCmd  = ENABLE;
  NVIC_Init(&istruct);
  puart->CR1 = puart->CR1  | USART_CR1_RXNEIE;

}
/*-------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------*/
void DeInit_UART_interrupt(INT8U n)
{
  NVIC_InitTypeDef istruct;
  USART_TypeDef    *puart;

  switch( n )
  {
    case SD_UART1:
      istruct.NVIC_IRQChannel                   = USART1_IRQn; 
      istruct.NVIC_IRQChannelPreemptionPriority = 1;
      istruct.NVIC_IRQChannelSubPriority        = 0;
      puart = USART1;
      break;
    case SD_UART2:
      istruct.NVIC_IRQChannel                   = USART2_IRQn; 
      istruct.NVIC_IRQChannelPreemptionPriority = 1;
      istruct.NVIC_IRQChannelSubPriority        = 0;
      puart = USART2;
      break;
    case SD_UART3:
      istruct.NVIC_IRQChannel                   = USART3_IRQn; 
      istruct.NVIC_IRQChannelPreemptionPriority = 1;
      istruct.NVIC_IRQChannelSubPriority        = 0;
      puart = USART3;
      break;
    default: return;
  }
  istruct.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&istruct);
  puart->CR1 = puart->CR1  & ~USART_CR1_RXNEIE;
  puart->CR1 = puart->CR1  & ~USART_CR1_TXEIE;

}

/*-------------------------------------------------------------------------------------------------------------
  Запрещение работы UART
-------------------------------------------------------------------------------------------------------------*/
void UART_disable(USART_TypeDef *puart)
{
  puart->CR1 = puart->CR1 & ~USART_CR1_UE;
}


/*-------------------------------------------------------------------------------------------------------------
  Разрешение работы UART
-------------------------------------------------------------------------------------------------------------*/
void UART_enable(USART_TypeDef *puart)
{
  puart->CR1 = puart->CR1 | USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

/*-------------------------------------------------------------------------------------------------------------
  Установка скорости UART
-------------------------------------------------------------------------------------------------------------*/
void UART_set_baude_rate(INT8U n,INT32U baudrate)
{
  float divider, integ, fract;
  USART_TypeDef *puart;

  switch( n )
  {
    case SD_UART1:
      divider =  PCLK2/(16.0f*(float)baudrate);
      fract =  modff(divider, &integ);
      fract = rint(fract*16);
      puart = USART1;
      puart->BRR = LSHIFT((int)integ,4)  +  (int)fract;
      break;
    case SD_UART2:
      divider =  PCLK1/(16.0f*(float)baudrate);
      fract =  modff(divider, &integ);
      fract = rint(fract*16);
      puart = USART2;
      puart->BRR = LSHIFT((int)integ,4)  +  (int)fract;
      break;
    case SD_UART3:
      divider =  PCLK1/(16.0f*(float)baudrate);
      fract =  modff(divider, &integ);
      fract = rint(fract*16);
      puart = USART3;
      puart->BRR = LSHIFT((int)integ,4)  +  (int)fract;
      break;
    default: return;
  }

}

/*-------------------------------------------------------------------------------------------------------------
  Установка числа стоп битов
-------------------------------------------------------------------------------------------------------------*/
void UART_set_stop_bits(USART_TypeDef *puart,INT8U sb)
{
  switch( sb )
  {
    case UART_STOP_BITS_1:
      puart->CR2 = (puart->CR2 & ~USART_CR2_STOP_x(3)) | USART_CR2_STOP_x(0);
      return;
    case UART_STOP_BITS_2:
      puart->CR2 = (puart->CR2 & ~USART_CR2_STOP_x(3)) | USART_CR2_STOP_x(2);
      return;
  }
}

/*-------------------------------------------------------------------------------------------------------------
  Установка числа битов данных
-------------------------------------------------------------------------------------------------------------*/
void UART_set_data_bits(USART_TypeDef *puart,INT8U db)
{
  switch( db )
  {
    case UART_DATA_BITS_8:
      puart->CR1 = puart->CR1 & ~USART_CR1_M;
      return;
    case UART_DATA_BITS_9:
      puart->CR1 = puart->CR1 | USART_CR1_M;
      return;
  }
}

/*-------------------------------------------------------------------------------------------------------------
  Установка проверки контроля четности
-------------------------------------------------------------------------------------------------------------*/
void UART_set_parity_bits(USART_TypeDef *puart,INT8U pb)
{
  switch( pb )
  {
    case UART_PARITY_NONE:
      puart->CR1 = puart->CR1 & ~USART_CR1_PCE;
      return;
    case UART_PARITY_EVEN:
      puart->CR1 = puart->CR1 | USART_CR1_PCE;
      puart->CR1 = puart->CR1 | USART_CR1_PCE;
      return;
    case UART_PARITY_ODD:
      puart->CR1 = puart->CR1 | USART_CR1_PCE;
      puart->CR1 = puart->CR1 & ~USART_CR1_PCE;
      return;
  }
}

/*-------------------------------------------------------------------------------------------------------------
  Разрешение прерывания после высвобождения места для следующег передаваемого байта
-------------------------------------------------------------------------------------------------------------*/
void UART_enable_TX_int(USART_TypeDef *puart)
{
  puart->CR1 = puart->CR1 | USART_CR1_TXEIE;
}

/*-------------------------------------------------------------------------------------------------------------
  Разрешение прерывания после приема символа
-------------------------------------------------------------------------------------------------------------*/
void UART_enable_RX_int(USART_TypeDef *puart)
{
  puart->CR1 = puart->CR1 | USART_CR1_RXNEIE;
}

/*-------------------------------------------------------------------------------------------------------------
  Запрещение прерывания после высвобождения места для следующег передаваемого байта
-------------------------------------------------------------------------------------------------------------*/
void UART_disable_TX_int(USART_TypeDef *puart)
{
  puart->CR1 = puart->CR1 & ~USART_CR1_TXEIE;
}


/*-------------------------------------------------------------------------------------------------------------
  Ожидать возможности записать байт в UART
-------------------------------------------------------------------------------------------------------------*/
void UART_wait_TX_occasion(USART_TypeDef *puart)
{
  while (( puart->SR & USART_SR_TXE )==0);
}


/*-------------------------------------------------------------------------------------------------------------
  Запись байта b в pdefuart
-------------------------------------------------------------------------------------------------------------*/
void UART_TX_byte(USART_TypeDef *puart,INT8U b)
{
  if( puart==0 ) return;
  UART_wait_TX_occasion(puart);
  puart->DR = b;
}


/*-------------------------------------------------------------------------------------------------------------
  Чтение байта b из pdefuart
-------------------------------------------------------------------------------------------------------------*/
INT8U UART_RX_byte(USART_TypeDef *puart)
{
  while( puart->SR & USART_SR_RXNE );
  return(puart->DR);
}


/*-------------------------------------------------------------------------------------------------------------
  Взять байт из UART без ожидания
-------------------------------------------------------------------------------------------------------------*/
INT32U UART_peek_byte(USART_TypeDef *puart,INT8U *b)
{
  if( puart->SR & USART_SR_RXNE )
  {
    *b = (INT8U)puart->DR;
    return(1);
  }
  else
  {
    return(0);
  }
}

/*-------------------------------------------------------------------------------------------------------------
 Ожидание приема символа UART-ом

 Параметры:     c - принятый символ
                timeout - время ожидания с дискретностью 10 мкс
 Возвращает:    0 - Если байт принят
               -1 - в случае таймаута
-------------------------------------------------------------------------------------------------------------*/
INT32S UART_wait_byte (USART_TypeDef *puart,INT8U *c, INT32U timeout)
{
  while( timeout-- > 0 )
  {
    if( UART_peek_byte(puart,c) == 1 )
    {
      return(0);
    }
    DELAY_1us;
  }
  return(-1);
}


/*-------------------------------------------------------------------------------------------------------------
  Запись строки в pdefuart
-------------------------------------------------------------------------------------------------------------*/
void UART_TX_str(USART_TypeDef *puart,INT8U* str)
{
  while( *str!=0 ) UART_TX_byte(puart, *str++);
}


/*-------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------*/
void Comc_init_channel(char ch)
{
  if( ch < COMC_NUM )
  {
    comc_in_buf_head[ch]  = 0;
    comc_in_buf_tail[ch]  = 0;
    comc_out_buf_head[ch] = 0;
    comc_out_buf_tail[ch] =0;
  }
}


/*-------------------------------------------------------------------------------------------------------------
  Если буффер пуст ERROR
-------------------------------------------------------------------------------------------------------------*/
int Comc_peek_byte(char ch, unsigned char *b)
{
  if( ch < COMC_NUM )
  {
    if( Comc_check_data(ch)!=SUCCESS ) return(ERROR);
    __disable_irq();
    *b = comc_input_buf[ch][comc_in_buf_tail[ch]];
    comc_in_buf_tail[ch]++ ;
    if (comc_in_buf_tail[ch] >= COMC_IN_BUF_SZ) comc_in_buf_tail[ch] = 0;
    __enable_irq();
    return(SUCCESS);
  }
  return(ERROR);
}


/*-------------------------------------------------------------------------------------------------------------
  Если буффер пуст то возвращает ERROR
-------------------------------------------------------------------------------------------------------------*/
int Comc_check_data(char ch)
{
  if( comc_in_buf_head[ch]==comc_in_buf_tail[ch] )
    return(ERROR);
  else
    return(SUCCESS);
}

/*------------------------------------------------------------------------------
  Послать буфер в коммуникационный канал
  Строка отправляется в кольцевой буффер
  Если в буфере недостаточно места, то возвращается ошибка
 ------------------------------------------------------------------------------*/
int Comc_send_buffer(char ch,unsigned char *buf, int len)
{
  int free_sz;

  do
  {

    do
    {
      if( comc_out_buf_head[ch]>=comc_out_buf_tail[ch] )
      {
        free_sz = (COMC_OUT_BUF_SZ - (comc_out_buf_head[ch] - comc_out_buf_tail[ch]))-1;
      }
      else
      {
        free_sz = comc_out_buf_tail[ch] - comc_out_buf_head[ch] - 1;
        if( free_sz > 0 ) free_sz -= 1;
      }
      if(( free_sz>=len ) || (free_sz>128))break;
    } 
    while( 1 );

    // Перенести данные в кольцевой буффер
    while(( free_sz>0 ) && (len>0))
    {
      __disable_irq();
      comc_output_buf[ch][comc_out_buf_head[ch]] = *buf++;
      comc_out_buf_head[ch]++;
      comc_out_buf_head[ch] &= (COMC_OUT_BUF_SZ - 1); 
      __enable_irq();
      len--;
      free_sz--;
    }

    switch( ch )
    {
      case 0:
        if( (USART1->CR1 & USART_CR1_TXEIE)==0 )
        {
          USART1->CR1 |= USART_CR1_TXEIE;
        }
        break;
      case 1:
        if( (USART2->CR1 & USART_CR1_TXEIE)==0 )
        {
          USART2->CR1 |= USART_CR1_TXEIE;
        }
        break;
      case 2:
        if( (USART3->CR1 & USART_CR1_TXEIE)==0 )
        {
          USART3->CR1 |= USART_CR1_TXEIE;
        }
        break;
    }
  } while( len>0 );

  return(SUCCESS);
}

/*-------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------*/
int Comc_send_str(char ch, char *str)
{
  return Comc_send_buffer(ch,(unsigned char*)str, strlen(str));
}


/*-----------------------------------------------------------------------------------------------------
  Вывод форматированной строки в коммуникационный канал модема
-----------------------------------------------------------------------------------------------------*/
#define MAX_STR_LEN  512
INT32S  UART1_printf(char* fmtstr,...)
{
  va_list            argptr;
  int                status;
  static char        str[MAX_STR_LEN+1];

  va_start(argptr, fmtstr);

  vsnprintf(str, MAX_STR_LEN, fmtstr, argptr);
  status = Comc_send_str(SD_UART1, str);
  va_end(argptr);

  return(status);
}


/*-------------------------------------------------------------------------------------------------------------
  Обработчик прерываний по UART1
-------------------------------------------------------------------------------------------------------------*/
void USART1_IRQHandler(void)
{
  unsigned short sr;
  unsigned int   tmp;

  sr  = USART1->SR;
  if( sr & USART_SR_RXNE )
  {
    // Получили байт, сохраняем в кольцевом буфере 
    tmp = comc_in_buf_head[0];
    comc_input_buf[0][comc_in_buf_head[0]++] = USART1->DR;
    comc_in_buf_head[0] &= (COMC_IN_BUF_SZ - 1); 
    if( comc_in_buf_head[0]==comc_in_buf_tail[0] ) comc_in_buf_head[0] = tmp; // Если происходит переполнение то не сдвигать указатель буфера
  }

  if( sr & USART_SR_ORE )
  {
    dummy = USART1->DR;
  }
  if( ( sr & USART_SR_TXE) && (USART1->CR1 & USART_CR1_TXEIE) )
  {
    USART1->DR =  comc_output_buf[0][comc_out_buf_tail[0]++];
    comc_out_buf_tail[0] &= (COMC_OUT_BUF_SZ - 1); 
    if( comc_out_buf_head[0] == comc_out_buf_tail[0] )
    {
      USART1->CR1 &= ~USART_CR1_TXEIE; // Запретим прерывания если нечего передавать
    }
  }
}


/*-------------------------------------------------------------------------------------------------------------
  Обработчик прерываний по UART2 
-------------------------------------------------------------------------------------------------------------*/
void USART2_IRQHandler(void)
{
  unsigned short sr;
  unsigned int   tmp;

  sr  = USART2->SR;
  if( sr & USART_SR_RXNE )
  {
    // Получили байт, сохраняем в кольцевом буфере 
    tmp = comc_in_buf_head[1];
    comc_input_buf[1][comc_in_buf_head[1]++] = USART2->DR;
    comc_in_buf_head[1] &= (COMC_IN_BUF_SZ - 1); 
    if( comc_in_buf_head[1]==comc_in_buf_tail[1] ) comc_in_buf_head[1] = tmp; // Если происходит переполнение то не сдвигать указатель буфера
  }
  if( sr & USART_SR_ORE )
  {
    dummy = USART2->DR;
  }
  if( ( sr & USART_SR_TXE) && (USART2->CR1 & USART_CR1_TXEIE) )
  {
    USART2->DR =  comc_output_buf[1][comc_out_buf_tail[1]++];
    comc_out_buf_tail[1] &= (COMC_OUT_BUF_SZ - 1); 
    if( comc_out_buf_head[1] == comc_out_buf_tail[1] )
    {
      USART2->CR1 &= ~USART_CR1_TXEIE; // Запретим прерывания если нечего передавать
    }
  }
}


/*-------------------------------------------------------------------------------------------------------------
  Обработчик прерываний по UART3 
-------------------------------------------------------------------------------------------------------------*/
void USART3_IRQHandler(void)
{
  unsigned short sr;
  unsigned int   tmp;

  sr  = USART3->SR;
  if( sr & USART_SR_RXNE )
  {
    // Получили байт, сохраняем в кольцевом буфере 
    tmp = comc_in_buf_head[2];
    comc_input_buf[2][comc_in_buf_head[2]++] = USART3->DR;
    comc_in_buf_head[2] &= (COMC_IN_BUF_SZ - 1); 
    if( comc_in_buf_head[2]==comc_in_buf_tail[2] ) comc_in_buf_head[2] = tmp; // Если происходит переполнение то не сдвигать указатель буфера
  }
  if( sr & USART_SR_ORE )
  {
    dummy = USART3->DR;
  }
  if( ( sr & USART_SR_TXE) && (USART3->CR1 & USART_CR1_TXEIE) )
  {
    USART3->DR =  comc_output_buf[2][comc_out_buf_tail[2]++];
    comc_out_buf_tail[2] &= (COMC_OUT_BUF_SZ - 1); 
    if( comc_out_buf_head[2] == comc_out_buf_tail[2] )
    {
      USART3->CR1 &= ~USART_CR1_TXEIE; // Запретим прерывания если нечего передавать
    }
  }
}


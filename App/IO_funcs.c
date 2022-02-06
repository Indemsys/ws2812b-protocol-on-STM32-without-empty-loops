#include "..\bsp\bsp.h"

#define   INPUT__       0
#define   OUTPUT_       1
#define   ALTFUNC       2
#define   ANALOG_       3

#define   PUSH_PULL     0
#define   OPEN_DRAIN    1

#define   S_002MHZ      0
#define   S_025MHZ      1
#define   S_050MHZ      2
#define   S_100MHZ      3

#define   NOPUPD___     0
#define   PULL_UP__     1
#define   PULL_DOWN     2


typedef struct
{
  GPIO_TypeDef *port;
  int pin_num;
  int mode;
  int type;
  int speed;
  int pupd;
  int alt_func_id;
  int initv;

} T_IO_pins_configuration;


const T_IO_pins_configuration pins_conf[] =
{
  { GPIOA, 0, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 1, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 2, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 3, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 4, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 5, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 6, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 7, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOA, 8, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOA, 9, ALTFUNC, PUSH_PULL, S_050MHZ, NOPUPD___, 7, 0 },  //
  { GPIOA, 10, ALTFUNC, PUSH_PULL, S_050MHZ, NOPUPD___, 7, 0 },  //
  { GPIOA, 11, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOA, 12, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //

  { GPIOB, 0, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOB, 1, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOB, 5, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOB, 6, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 7, 0 },  //
  { GPIOB, 7, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 7, 0 },  //
  { GPIOB, 8, ALTFUNC, PUSH_PULL, S_002MHZ, PULL_DOWN, 2, 0 },  // TP4  TIM4_CH3 (DMA1: Channel 2, Stream 7)
  { GPIOB, 9, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 9, 0 },  //
  { GPIOB, 10, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 5, 0 },  //
  { GPIOB, 11, INPUT__, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOB, 12, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 5, 0 },  //
  { GPIOB, 13, ALTFUNC, PUSH_PULL, S_050MHZ, PULL_DOWN, 5, 0 },  //
  { GPIOB, 14, ALTFUNC, PUSH_PULL, S_050MHZ, PULL_DOWN, 6, 0 },  //
  { GPIOB, 15, ALTFUNC, PUSH_PULL, S_050MHZ, PULL_DOWN, 5, 0 },  //

  { GPIOC, 0, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOC, 1, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 2, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 3, ANALOG_, PUSH_PULL, S_050MHZ, NOPUPD___, 5, 0 },  //
  { GPIOC, 4, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 5, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 6, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 7, ALTFUNC, PUSH_PULL, S_050MHZ, NOPUPD___, 2, 0 },  //
  { GPIOC, 8, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOC, 9, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOC, 10, OUTPUT_, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 11, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 12, OUTPUT_, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOC, 13, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //

  { GPIOD, 0, ALTFUNC, PUSH_PULL, S_050MHZ, NOPUPD___, 9, 0 },  //
  { GPIOD, 1, ALTFUNC, PUSH_PULL, S_050MHZ, NOPUPD___, 9, 0 },  //
  { GPIOD, 2, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOD, 3, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOD, 4, INPUT__, PUSH_PULL, S_050MHZ, PULL_UP__, 0, 0 },  //
  { GPIOD, 5, INPUT__, PUSH_PULL, S_050MHZ, PULL_UP__, 0, 0 },  //
  { GPIOD, 6, INPUT__, PUSH_PULL, S_050MHZ, PULL_UP__, 0, 0 },  //
  { GPIOD, 7, INPUT__, PUSH_PULL, S_050MHZ, PULL_UP__, 0, 0 },  //
  { GPIOD, 8, INPUT__, PUSH_PULL, S_050MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOD, 9, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOD, 10, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOD, 11, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOD, 12, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOD, 13, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOD, 14, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //
  { GPIOD, 15, OUTPUT_, PUSH_PULL, S_050MHZ, NOPUPD___, 0, 0 },  //

  { GPIOE, 0, OUTPUT_, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 1, OUTPUT_, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 2, OUTPUT_, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 3, OUTPUT_, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 4, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 5, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 6, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 7, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 8, INPUT__, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 9, INPUT__, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 10, INPUT__, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 11, INPUT__, PUSH_PULL, S_100MHZ, NOPUPD___, 0, 0 },  //
  { GPIOE, 12, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 13, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 14, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //
  { GPIOE, 15, INPUT__, PUSH_PULL, S_100MHZ, PULL_DOWN, 0, 0 },  //

};


/*------------------------------------------------------------------------------
  Иницализация портов ввода-вывода
 ------------------------------------------------------------------------------*/
void IO_pins_init(void)
{
  int i;

  RCC->AHB1ENR |= 0
                  | BIT(8)   // PORT I
                  | BIT(7)   // PORT H
                  | BIT(6)   // PORT G
                  | BIT(5)   // PORT F
                  | BIT(4)   // PORT E
                  | BIT(3)   // PORT D
                  | BIT(2)   // PORT C
                  | BIT(1)   // PORT B
                  | BIT(0)   // PORT A
  ;

  for (i = 0; i < (sizeof(pins_conf) / sizeof(pins_conf[0])); i++)
  {
    if ( pins_conf[i].mode == ALTFUNC )
    {
      int n;
      if ( pins_conf[i].pin_num < 8 )
      {
        n = pins_conf[i].pin_num;
        pins_conf[i].port->AFR[0] = (pins_conf[i].port->AFR[0] & ~(0x0F << (n * 4))) | (pins_conf[i].alt_func_id << (n * 4));
      }
      else
      {
        n = pins_conf[i].pin_num - 8;
        pins_conf[i].port->AFR[1] = (pins_conf[i].port->AFR[1] & ~(0x0F << (n * 4))) | (pins_conf[i].alt_func_id << (n * 4));
      }
    }
    pins_conf[i].port->OSPEEDR = (pins_conf[i].port->OSPEEDR & ~(0x03 << (pins_conf[i].pin_num * 2))) | (pins_conf[i].speed << (pins_conf[i].pin_num * 2));
    pins_conf[i].port->OTYPER = (pins_conf[i].port->OTYPER & ~(0x01 << (pins_conf[i].pin_num))) | (pins_conf[i].type << (pins_conf[i].pin_num));
    pins_conf[i].port->PUPDR = (pins_conf[i].port->PUPDR & ~(0x03 << (pins_conf[i].pin_num * 2))) | (pins_conf[i].pupd << (pins_conf[i].pin_num * 2));
    pins_conf[i].port->ODR = (pins_conf[i].port->ODR & ~(0x01 << (pins_conf[i].pin_num))) | (pins_conf[i].initv << (pins_conf[i].pin_num));
    pins_conf[i].port->MODER = (pins_conf[i].port->MODER & ~(0x03 << (pins_conf[i].pin_num * 2))) | (pins_conf[i].mode << (pins_conf[i].pin_num * 2));
  }
}



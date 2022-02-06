#ifndef __IO_FUNCS
  #define __IO_FUNCS

#define STATE_INPUT(gpio,bit) ((gpio##->IDR >> bit) & 1) 
#define STATE_PIN(gpio,bit) ((gpio##->ODR >> bit) & 1) 
#define SET_PIN(gpio,bit, val)   {if ( val != 0 ) gpio##->BSRRL = (1 << bit); else gpio##->BSRRH = (1 << bit);}
#define TOGGLE_PIN(gpio,bit) {if ( ((gpio##->ODR >> bit) & 1) == 0 ) gpio##->BSRRL = (1 << bit); else gpio##->BSRRH = (1 << bit);}


void IO_pins_init(void);





#endif

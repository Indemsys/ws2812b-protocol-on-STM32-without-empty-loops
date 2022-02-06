#ifndef __LEDS_STRIP
  #define __LEDS_STRIP



#define LED_LEV0  (29)
#define LED_LEV1  (29*2)


// цвета в формате RGB (00000000 RRRRRRRR GGGGGGGG BBBBBBBB)
#define COLOR_NONE       0x00000000
#define COLOR_RED        0x00FF0000
#define COLOR_RED_HALF   0x00800000
#define COLOR_GREEN      0x0000FF00
#define COLOR_GREEN_HALF 0x00008000
#define COLOR_BLUE       0x000000FF
#define COLOR_WHITE      0x00FFFFFF



void LEDstrip_init(void);
void LEDstrip_set_led_state(INT16U ledn, INT32U color);

void Running_LEDs_1(void);


#endif

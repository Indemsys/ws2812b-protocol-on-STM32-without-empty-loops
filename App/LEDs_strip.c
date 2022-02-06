#include "..\bsp\bsp.h"


const INT8U dim_curve[256] = {
  0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
  3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6,
  6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
  8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
  11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
  15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
  20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
  27, 27, 28, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35,
  36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 47,
  48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
  63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 81, 82,
  83, 85, 86, 88, 90, 91, 93, 94, 96, 98, 99, 101, 103, 105, 107, 109,
  110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
  146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
  193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

/*------------------------------------------------------------------------------
   Инициализируем начальное состояние светодиодов
   в полосе выполненой на светодиодах WS2812B 
 ------------------------------------------------------------------------------*/
void LEDstrip_init(void)
{
  INT32U i, j, k;

  for (i = 0; i < LEDS_NUM; i++)
  {
    for (j = 0; j < COLRS; j++)
    {
      for (k = 0; k < 8; k++)
      {
        DMA_buf[i][j][k] = LED_LEV0;
      }
    }
  }
  // Сигнал сброса
  for (i = LEDS_NUM; i < LEDS_NUM + 2; i++)
  {
    for (j = 0; j < COLRS; j++)
    {
      for (k = 0; k < 8; k++)
      {
        DMA_buf[i][j][k] = 0;
      }
    }
  }
}

/*------------------------------------------------------------------------------
   Устанавливаем цвет светодиода
   color - цвет в формате RGB (00000000 RRRRRRRR GGGGGGGG BBBBBBBB)
 ------------------------------------------------------------------------------*/
void LEDstrip_set_led_state(INT16U ledn, INT32U color)
{
  INT32U i;
  if ( ledn >= LEDS_NUM ) return;
  for (i = 0; i < 8; i++)
  {
    // Зеленый
    if ( ((color >> 8) >> (7 - i)) & 1 ) DMA_buf[ledn][0][i] = LED_LEV1;
    else DMA_buf[ledn][0][i] = LED_LEV0;
    // Красный
    if ( ((color >> 16) >> (7 - i)) & 1 ) DMA_buf[ledn][1][i] = LED_LEV1;
    else DMA_buf[ledn][1][i] = LED_LEV0;
    // Синий
    if ( ((color >> 0) >> (7 - i)) & 1 ) DMA_buf[ledn][2][i] = LED_LEV1;
    else DMA_buf[ledn][2][i] = LED_LEV0;
  }
}


/*------------------------------------------------------------------------------
   Конвертируем RGB буффер в DMA буффер
 ------------------------------------------------------------------------------*/
static void Convert_RGB_to_DMA_buf(void)
{
  INT32U i;
  for (i = 0; i < LEDS_NUM; i++)
  {
    LEDstrip_set_led_state(i, LEDS_buf[i]);
  }
}


/*------------------------------------------------------------------------------
  Корнвертер из HSV в RGB в целочисленной арифмерите
 
  hue        : 0..360
  saturation : 0..255
  value      : 0..255
 ------------------------------------------------------------------------------*/
INT32U HSV_to_RGB(int hue, int sat, int val) 
{
  int    r;
  int    g;
  int    b;
  int    base;
  INT32U rgb;

  val = dim_curve[val];
  sat = 255 - dim_curve[255 - sat];


  if ( sat == 0 ) // Acromatic color (gray). Hue doesn't mind.
  {
    rgb = val | (val<<8) | (val <<16);
  }
  else
  {
    base = ((255 - sat) * val) >> 8;
    switch (hue / 60)
    {
    case 0:
      r = val;
      g = (((val - base) * hue) / 60) + base;
      b = base;
      break;
    case 1:
      r = (((val - base) * (60 - (hue % 60))) / 60) + base;
      g = val;
      b = base;
      break;
    case 2:
      r = base;
      g = val;
      b = (((val - base) * (hue % 60)) / 60) + base;
      break;
    case 3:
      r = base;
      g = (((val - base) * (60 - (hue % 60))) / 60) + base;
      b = val;
      break;
    case 4:
      r = (((val - base) * (hue % 60)) / 60) + base;
      g = base;
      b = val;
      break;
    case 5:
      r = val;
      g = base;
      b = (((val - base) * (60 - (hue % 60))) / 60) + base;
      break;
    }
    rgb = ((r & 0xFF)<<16) | ((g & 0xFF)<<8) | (b & 0xFF);
  }
  return rgb;
}

/*------------------------------------------------------------------------------
  Корнвертер из HSV в RGB с плавающей точкой
 
  hue        : 0..360
  saturation : 0..255
  value      : 0..255
------------------------------------------------------------------------------*/
INT32U HSV_to_RGB_double(INT32U hue, INT32U saturation, INT32U value) 
{
    INT8U rgb[3]; 
  	double r, g, b;
	
    double h =  (double)hue/360.0;
	double s = (double)saturation/255.0;
  	double v = (double)value/255.0;
	
    int i = (int)(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    rgb[0] = r * 255;
    rgb[1] = g * 255;
    rgb[2] = b * 255;
		return ((rgb[0] & 0xFF)<<16) | ((rgb[1] & 0xFF)<<8) | (rgb[2] & 0xFF);
}

/*------------------------------------------------------------------------------
  Перемещение светодиодов в заданную сторону с заданной задержкой и заданное количество шагов
------------------------------------------------------------------------------*/
static void Moving_leds(INT32U n, INT32U dir, INT32U del)
{
  INT32U i, k;
  INT32U tmpLED;

  for (k = 0; k < n; k++)
  {
    Convert_RGB_to_DMA_buf();

    if ( dir == 0 )
    {
      // Перемещаем огни
      tmpLED = LEDS_buf[0];
      for (i = 0; i < LEDS_NUM; i++)
      {
        if ( i != (LEDS_NUM - 1) )
        {
          LEDS_buf[i] = LEDS_buf[i + 1];
        }
        else
        {
          LEDS_buf[i] = tmpLED;
        }
      }
    }
    else
    {
      // Перемещаем огни
      tmpLED = LEDS_buf[LEDS_NUM - 1];
      for (i = 0; i < LEDS_NUM; i++)
      {
        if ( i != 0 )
        {
          LEDS_buf[LEDS_NUM - i] = LEDS_buf[LEDS_NUM - i - 1];
        }
        else
        {
          LEDS_buf[0] = tmpLED;
        }
      }
    }
    Delay_ms(del);
  }
}


/*------------------------------------------------------------------------------
  Заполняем радугой 
 ------------------------------------------------------------------------------*/
static void Fill_rainbow(INT32U sat, INT32U val, INT8U mode )
{
  INT32U i;
  INT32U hue;

    // Записываем в буфер начальную последовательность
    for (i = 0; i < LEDS_NUM; i++)
    {
      hue = ((360 * i) / LEDS_NUM);
			if (mode==0)
			{
        LEDS_buf[i] = HSV_to_RGB(hue, sat, val);
			}
			else
			{
	      LEDS_buf[i] = HSV_to_RGB_double(hue, sat, val);		
			}				
    }
}

/*------------------------------------------------------------------------------
  Бегущая радуга 
 ------------------------------------------------------------------------------*/
void Running_LEDs_1(void)
{
  while (1)
  {
    Fill_rainbow(255, 255, 0);
    Moving_leds(LEDS_NUM * 2, 0, 20);
    Fill_rainbow(255, 255, 1);
    Moving_leds(LEDS_NUM * 2, 0, 20);
		
		
  }
}





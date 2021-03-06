#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"

void delay( void )
{
  for (int i = 0; i < 600000; i++);
}

void delay10( void )
{
  for (int i = 0; i < 6000; i++);
}

void gpio_config( void )
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);

  // GPIOB init
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT);
}

uint16_t show_digit( uint32_t digit )
{
  uint16_t s[] = {
  0x0400, // segment A - 0
  0x0040, // segment B - 1
  0x0008, // segment C - 2
  0x0002, // segment D - 3
  0x0001, // segment E - 4
  0x0200, // segment F - 5
  0x0010, // segment G - 6
  };

  switch (digit)
  {
  case 0:
    return s[0] | s[1] | s[2] | s[3] | s[4] | s[5];
  case 1:
    return s[1] | s[2];
  case 2:
    return s[0] | s[1] | s[6] | s[4] | s[3];
  case 3:
    return s[0] | s[1] | s[2] | s[3] | s[6];
  case 4:
    return s[1] | s[2] | s[5] | s[6];
  case 5:
    return s[0] | s[2] | s[3] | s[5] | s[6];
  case 6:
    return s[0] | s[2] | s[3] | s[4] | s[5] | s[6];
  case 7:
    return s[0] | s[1] | s[2];
  case 8:
    return s[0] | s[1] | s[2] | s[3] | s[4] | s[5] | s[6];
  case 9:
    return s[0] | s[1] | s[2] | s[3] | s[5] | s[6];
  default:
    return 0;
  }
}

/* HELLO PEOPLE. */
uint16_t get_hell_sym( uint8_t sym )
{
  uint16_t s[] = {
  0x0400, // segment A - 0
  0x0040, // segment B - 1
  0x0008, // segment C - 2
  0x0002, // segment D - 3
  0x0001, // segment E - 4
  0x0200, // segment F - 5
  0x0010, // segment G - 6
  };

  switch (sym)
  {
  case 'H':
    return s[1] | s[2] | s[4] | s[5] | s[6];
  case 'E':
    return s[0] | s[5] | s[6] | s[4] | s[3];
  case 'L':
    return s[3] | s[4] | s[5];
  case 'O':
    return s[0] | s[1] | s[2] | s[3] | s[4] | s[5];
  case 'P':
    return s[0] | s[1] | s[4] | s[5] | s[6];
  case '.':
    return 0x0004;
  case 'A':
    return s[0] | s[1] | s[2] | s[6] | s[4] | s[5];
  case 'U':
    return s[2] | s[3] | s[4] | s[1] | s[5];
  case 'C':
    return s[0] | s[3] | s[4] | s[5];
  case 'S':
    return s[0] | s[6] | s[2] | s[6] | s[5] | s[3];
  case 'I':
    return s[4] | s[5];
  case ' ':
    return 0x0000;
  }
  return 0;
}

void show_hell( uint32_t cnt )
{
  uint8_t string[] = "HELP US PLEASE.";
  uint16_t size = sizeof(string) / sizeof(char) - 1;
  uint16_t pos[] = {
    0x01A0, 0x08A0, 0x0920, 0x0980
  };

  static int i = 0;
  uint16_t dot_flag = 0;

  uint8_t sym_pos = (cnt + i) % size;

  /* Check if the first symbol is a dot */
  if (string[sym_pos] == '.' && i == 0)
  {
    cnt = (cnt + 1) % size;
    sym_pos = (cnt + i) % size;
    i = (i + 1) % 4;
  }

  uint16_t pos_mask = pos[i];
  /* skip dot symbol if it is next */
  /* but not skip if the pre dot symbol on the right edge panel */
  if (string[(sym_pos + 1) % size] == '.')
  {
    if (i != 3)
      i = (i + 1) % 4;
    dot_flag = 0x0004;
  }

  LL_GPIO_WriteOutputPort(GPIOB, get_hell_sym(string[sym_pos]) | dot_flag | pos_mask);

  dot_flag = 0;

  i = (i + 1) % 4;
}

void show_number( uint32_t num )
{
  uint16_t res[4] =
  {
    [0] = show_digit(num % 10) | 0x0980,
    [1] = show_digit(num / 10 % 10) | 0x0920,
    [2] = show_digit(num / 100 % 10) | 0x08A0,
    [3] = show_digit(num / 1000 % 10) | 0x01A0,
  };

  static int i = 0;

  LL_GPIO_WriteOutputPort(GPIOB, res[i]);

  i = (i + 1) % 4;
}

#define NO_NOISE

#define CLICKER

int main( void )
{
  gpio_config();
  uint32_t counter = 0, is_pressed = 0, is_on = 0;
  uint32_t n = 0;

  while (1)
  {
#ifdef NO_NOISE
    // 1 - on, 0 - off
    /* Check if button pressed */
    if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
    {
      is_pressed = 1;
      counter = 0; /* reset counter */
    }

    if (is_pressed)
    {
      counter++;
      delay10();
    }

    if (counter >= 5)
    {
      if (is_on)
      {
        LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_9);
        LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);
      }
      else
      {
        LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_9);
        LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_8);
      }
      // change state
      is_on = 1 - is_on;

      //LL_GPIO_WriteOutputPort(GPIOB, 0x0000);
      ++n;

      is_pressed = 0;
      counter = 0;
    }
#else
     if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0))
     {
       if (is_on)
        {
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_9);
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);
        }
        else
        {
          LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_9);
          LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_8);
        }
        // change state
        is_on = 1 - is_on;
#ifdef CLICKER
        LL_GPIO_WriteOutputPort(GPIOB, 0x0000);
        ++n;
#endif
     }
#endif

#ifdef CLICKER
    show_number(n);
#else
    for (int i = 0; i < 20000; ++i)
      show_hell(n);
    n++;

#endif
  }
}

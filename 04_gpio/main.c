#include "libs/stm32f0xx_ll_rcc.h"
#include "libs/stm32f0xx_ll_system.h"
#include "libs/stm32f0xx_ll_bus.h"
#include "libs/stm32f0xx_ll_gpio.h"


void delay()
{
  for (int i = 0; i < 60000; ++i)
  {}
  return;
}

void delay_10ms()
{
    for (int i = 0; i < 6000; ++i)
    {}
    return;
}



void gpio_config()
{  
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // enable tact port
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT); //enable digital port
  
  return;
}

int main()
{
  uint32_t status = 0;
  gpio_config();
  uint32_t counter = 0;
  uint32_t buf[1] = {0};
  
  while (1)
  {
    status = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0); // check register IDR cond
 
    if (status)
    {
      counter++; 
      delay_10ms();
        
      if (counter >= 5)
        LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_8);
    }
    else
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);
  } 
  
  return 0;
}







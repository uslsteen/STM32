#include "libs/stm32f0xx_ll_rcc.h"
#include "libs/stm32f0xx_ll_system.h"
#include "libs/stm32f0xx_ll_bus.h"
#include "libs/stm32f0xx_ll_gpio.h"


void delay()
{
  for (int i = 0; i < 600000; ++i)
  {}
  return;
}

void delay_10ms()
{
    for (int i = 0; i < 6000; ++i)
    {}
    return;
}


uint16_t sgmnts[7] =
{ 
  LL_GPIO_PIN_0, // E - segment 0
  LL_GPIO_PIN_2, // D - segment 1
  LL_GPIO_PIN_3, // C - segment 2
  LL_GPIO_PIN_4, // G - segment 3
  LL_GPIO_PIN_6, // B - segment 4
  LL_GPIO_PIN_9, // F - segment 5 
  LL_GPIO_PIN_10, // A - segment 6
};

uint16_t Show_digit(uint32_t digit)
{
     switch (digit)
     {
     case 0: return (sgmnts[0] | sgmnts[1] | sgmnts[2] |
                     sgmnts[4] | sgmnts[6] | sgmnts[5]);
             
     case 1: return (sgmnts[4] | sgmnts[2]);
     
     case 2: return (sgmnts[6] | sgmnts[4] | sgmnts[3] |
                     sgmnts[0] | sgmnts[1]);
             
     case 3: return (sgmnts[4] | sgmnts[2] | sgmnts[6] | 
                     sgmnts[3] | sgmnts[1]);
                     
     
  
     case 4: return (sgmnts[4] | sgmnts[2] | sgmnts[5] | 
                     sgmnts[3]);
             
             
     case 5: return (sgmnts[6] | sgmnts[2] | sgmnts[5] | 
                     sgmnts[3] | sgmnts[1]);
             
     case 6: return (sgmnts[6] | sgmnts[5] | sgmnts[0] |
                     sgmnts[3] | sgmnts[2] | sgmnts[1]);
             
     case 7: return (sgmnts[4] | sgmnts[2] | sgmnts[6]);
                     
             
     case 8: return (sgmnts[1] | sgmnts[2] | sgmnts[3] |
                     sgmnts[4] | sgmnts[5] | sgmnts[6] |
                     sgmnts[0]);
       
     case 9: return (sgmnts[1] | sgmnts[2] | sgmnts[3] |
                     sgmnts[4] | sgmnts[5] | sgmnts[6]);
             
     default: return 0; //disable all segments 
          
     }
}


void dyn_display(uint16_t num)
{
  while(1)
  {
  
    uint16_t result[4] = 
    {
      [0] = Show_digit(num % 10) | 0x0980,                         
      [1] = Show_digit((num / 10) % 10) |  0x0920,         
      [2] = Show_digit((num / 100) % 10) |  0x08A0,     
      [3] = Show_digit((num / 1000) % 10) |  0x01A0,        
  
    };
    
    static int digit_num = 0;
   
 
    LL_GPIO_WriteOutputPort(GPIOB, result[digit_num]); 
    delay();
    
    digit_num = (digit_num + 1) % 4;
  }
    return;
}



uint16_t Hello_people(uint8_t symbol)
{
  switch(symbol)
  {
  case 'H': return sgmnts[5] | sgmnts[0] | sgmnts[3] | sgmnts[4] | sgmnts[2];
  
  case 'E': return sgmnts[6] |  sgmnts[3] | sgmnts[1] | sgmnts[0] | sgmnts[5];
  
  case 'L': return sgmnts[0] | sgmnts[1] | sgmnts[5];
  
  case 'O': return (sgmnts[0] | sgmnts[1] | sgmnts[2] |
                     sgmnts[4] | sgmnts[6] | sgmnts[5]);
            
  case ',': return LL_GPIO_PIN_2; 
  
  case 'P': return sgmnts[6] |  sgmnts[3] | sgmnts[4] | sgmnts[0] | sgmnts[5];
  
  case ' ': return 0x0000;
  }
}


/*
void Show_str(uint32_t counter)
{
    uint8_t str[] = "HELLO PEOPLE";
    static int i = 0;
    
    uint16_t scr_pos[4] = { 0x01A0, 0x08A0, 0x0920, 0x0980 };
    uint16_t str_size = (sizeof(str)/sizeof(uint8_t)) - 1;
    
    uint8_t sym_pos = (counter + i) % str_size;
    
    uint16_t pos_mask = scr_pos[i];
    
    LL_GPIO_WriteOutputPort(GPIOB, str[sym_pos] | pos_mask); 
    delay();
      
    i = (i + 1) % 4;
 }
*/

void Show_str( uint32_t cnt )
{
  static int i = 0;

  uint8_t str[] = "HELLO PEOPLE ";
  
  uint16_t scr_pos[] = { 0x01A0, 0x08A0, 0x0920, 0x0980};
  uint16_t size = sizeof(str) / sizeof(char) - 1;

  uint8_t sym_pos = (cnt + i) % size;
 
  uint16_t pos_mask = scr_pos[i];

  LL_GPIO_WriteOutputPort(GPIOB, Hello_people(string[sym_pos]) | pos_mask);
  
  i = (i + 1) % 4;
}


void gpio_config()
{  
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA); // enable tact port
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_INPUT); //enable digital port

  
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

  
  return;
}

void Show()
{
  static uint32_t n = 0;
  
  for (int i = 0; i < 20000; ++i)
    Show_str(n);
  
  n++;
}

 int main()
{
  uint32_t status = 0, on_ = 0;
  uint32_t counter = 0;
  uint32_t buf[1] = {0};

  
  gpio_config();

  
  while (1)
  {
    status = LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0); // check register IDR cond
 
    if (status)
    {
      counter++; 
      delay_10ms();
        
      if (counter >= 5)
      {
        LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_8);
        
#if 0
        LL_GPIO_WriteOutputPort(GPIOB, Hello_people('L'));
#endif
        
        while(1)
          Show();
      }
    }
    else
      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_8);
  } 
  
  return 0;

}



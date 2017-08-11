#ifndef __LCD_H
#define __LCD_H

#include "stm32f0xx_hal.h"

#define rs GPIO_PIN_1
#define rw GPIO_PIN_2
#define en GPIO_PIN_3
#define d4 GPIO_PIN_4
#define d5 GPIO_PIN_5
#define d6 GPIO_PIN_6
#define d7 GPIO_PIN_7

int s2=0;
int c,x;
uint16_t a[8]={d4, d5, d6, d7, d4, d5, d6, d7};
char l[8]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
uint8_t h[2] = {0x32, 0x33};
void cmd (unsigned int i);
void data (unsigned int i,int x,int y);
void initialize(int x,int y);
void lcd(uint8_t *p,int x, int y);
void LCD_Init(void);

void LCD_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = rs | rw | en | d4 | d5 | d6 | d7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void cmd(unsigned int i)
{
  /**************************/
  for(c=7; c>=4; c--)
    {
      x= i&l[c];
      if(x!=0)
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_SET);
        }
      else
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_RESET);
        }
     }
  /**************************/
  HAL_GPIO_WritePin(GPIOA, rs, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, en, GPIO_PIN_SET);
  HAL_Delay(20);
  /**************************/
  HAL_GPIO_WritePin(GPIOA, en, GPIO_PIN_RESET);
  HAL_Delay(20);
  /**************************/
  for(c=3; c>=0; c--)
    {
      x= i&l[c];
      if(x!=0)
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_SET);
        }
      else
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_RESET);
        }
    }
  /**************************/
  HAL_GPIO_WritePin(GPIOA, rs, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, en, GPIO_PIN_SET);
  HAL_Delay(20);
  /**************************/
  HAL_GPIO_WritePin(GPIOA, en, GPIO_PIN_RESET);
  HAL_Delay(20);
  /**************************/
}
/***************************************************************************/

void data(unsigned int i,int x,int y)
{
  initialize(x,y);
  /**************************/
  for(c=7; c>=4; c--)
    {
      x= i&l[c];
      if(x!=0)
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_SET);
        }
      else
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_RESET);
        }
    }
  /**************************/
  HAL_GPIO_WritePin(GPIOA, rs | en, GPIO_PIN_SET);
  HAL_Delay(20);
  /**************************/
  HAL_GPIO_WritePin(GPIOA, en, GPIO_PIN_RESET);
  HAL_Delay(20);
  /**************************/
  for(c=3; c>=0; c--)
    {
      x= i&l[c];
      if(x!=0)
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_SET);
        }
    else
        {
          HAL_GPIO_WritePin(GPIOA, a[c], GPIO_PIN_RESET);
        }
    }
  /**************************/
  HAL_GPIO_WritePin(GPIOA, rs | en, GPIO_PIN_SET);
  HAL_Delay(20);
  /**************************/
  HAL_GPIO_WritePin(GPIOA, en, GPIO_PIN_RESET);
  HAL_Delay(20);
  /**************************/
}
/***************************************************************************/

void initialize(int x,int y)
{
  if(s2==0)
    {
      /**************************/
      cmd(0x32);
      HAL_Delay(10);
      /**************************/
      cmd(0x28);
      HAL_Delay(10);
      /**************************/
      cmd(0x06);
      HAL_Delay(10);
      /**************************/
      cmd(0x01);
      HAL_Delay(10);
      /**************************/
      cmd(0x0C);
      HAL_Delay(10);
      /**************************/
      s2++;
    }
  if(y%2==0)
    cmd(0x80+(x-1)+(64*(y-1)));
  else
    cmd(0x80+(x-1)+(16*(y-1)));
}

void lcd(uint8_t *p,int x, int y)
{
  while(*p!='\0')
    {
      data(*p,x++,y);
      p++;
    }
}

#endif
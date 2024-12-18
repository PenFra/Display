/**
 *
 * Display_2x16.c
 *
 *  Created on: 30 gen 2024
 *      Author: penfra
 */
//#include "Include.h"

#include "main.h"
#include "Driver/Display_2x16.h"
#include "Global.h"


HAL_StatusTypeDef TW_Status;



// ------------------------------------------------------------------

uint8_t special1[8] = {
        0b00000,
        0b11001,
        0b11011,
        0b00110,
        0b01100,
        0b11011,
        0b10011,
        0b00000
};

uint8_t special2[8] = {
        0b11000,
        0b11000,
        0b00110,
        0b01001,
        0b01000,
        0b01001,
        0b00110,
        0b00000
};




uint8_t dp_function;

uint8_t dpControl;
uint8_t dpMode;
uint8_t dpRows;
uint8_t dpBacklight;

//void test_display(void)
//{
//	  HD44780_NoCursor();
//	  HAL_Delay(2);
//
//	  HD44780_NoBlink();
//	  HAL_Delay(1);
//
//	  HD44780_SetCursor(1, 0);
//	  HAL_Delay(1);
//
//	  HD44780_PrintStr("No cursor   ");
//	  HAL_Delay(1);
//
//	  HD44780_NoCursor();
//	  HAL_Delay(1);
//
//	  HAL_Delay(3000);
//
//	  //lcd_put_cur(0, 7);
//	  HD44780_SetCursor(0, 7);
//	  HAL_Delay(1);
//
//
//	  HD44780_PrintStr("100.6");
//
//
//	  HD44780_SetCursor(1, 0);
//	  HAL_Delay(1);
//
//
//	  HD44780_PrintStr("Cursor      ");
//	  HAL_Delay(1);
//
//	  HD44780_SetCursor(0, 7);
//	  HAL_Delay(1);
//
//	  HD44780_Cursor();
//	  HAL_Delay(3000);
//
//
//	  HD44780_NoCursor();
//	  HAL_Delay(1);
//
//
//	  //lcd_put_cur(0, 7);
//	  HD44780_SetCursor(0, 7);
//	  HAL_Delay(1);
//
//	  HD44780_PrintStr("234.7");
//
//	  HD44780_SetCursor(1, 0);
//	  HAL_Delay(1);
//
//	  HD44780_NoCursor();
//	  HAL_Delay(1);
//
//	  HD44780_PrintStr("Blink   ");
//	  HAL_Delay(1);
//
//	  //lcd_cursor_blink();
//	  HD44780_Blink();
//	  HAL_Delay(1);
//
//	  HD44780_SetCursor(1, 0);
//	  HAL_Delay(1);
//
//
//	  HD44780_PrintStr("Modify  ");
//	  HAL_Delay(1);
//
//	  //lcd_put_cur(0, 7);
//	  HD44780_SetCursor(0, 7);
//	  HAL_Delay(1);
//	  HAL_Delay(3000);
//	  HD44780_PrintStr("5");
//
//	  //lcd_put_cur(0, 9);
//	  HD44780_SetCursor(0, 7);
//	  HAL_Delay(3000);
//
////    HD44780_NoCursor();
////    HAL_Delay(1);
//
//    HD44780_NoBlink();
//    HAL_Delay(1);
//
//
//
//}
//
//


void HD44780_Init(uint8_t rows)
{

  //Antirip1 = 0;

  dpRows = rows;

  dpBacklight = LCD_BACKLIGHT;

  dp_function = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

  if (dpRows > 1)
  {
    dp_function |= LCD_2LINE;
  }
  else
  {
    dp_function |= LCD_5x10DOTS;
  }

  /* Wait for initialization */
  DelayInit();
  HAL_Delay(2);

//  ExpanderWrite(dpBacklight);

  /* 4bit Mode */
  Write4Bits(0x03 << 4);
  DelayUS(100);

  Write4Bits(0x03 << 4);
  DelayUS(100);

  Write4Bits(0x03 << 4);
  DelayUS(100);

  Write4Bits(0x02 << 4);
  DelayUS(100);

  /* Display Control */
  SendCommand(LCD_FUNCTIONSET | dp_function);

  dpControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  HD44780_Display();
  HD44780_Clear();

  /* Display Mode */
  dpMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  SendCommand(LCD_ENTRYMODESET | dpMode);
  DelayUS(100);

  HD44780_CreateSpecialChar(0, special1);
  HD44780_CreateSpecialChar(1, special2);

  HD44780_Home();


  HD44780_SetCursor(0, 3);
  HAL_Delay(2);

  HD44780_PrintStr("DISPLAY PRJ");

  HD44780_SetCursor(1, 3);
  HAL_Delay(2);

  HD44780_PrintStr("REL.  0.0.1");

  HAL_Delay(3000);


  HD44780_Clear();
  HAL_Delay(2);

}


void HD44780_CreateSpecialChar(uint8_t location, uint8_t charmap[])
{
  location &= 0x7;
  SendCommand(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++)
  {
    SendChar(charmap[i]);
  }
}

void HD44780_Home()
{
  SendCommand(LCD_RETURNHOME);
  DelayUS(2000);
}

void HD44780_SetCursor(uint8_t row, uint8_t col)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if (row >= dpRows)
  {
    row = dpRows-1;
  }
  SendCommand(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void HD44780_NoCursor()
{
  dpControl &= ~LCD_CURSORON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void HD44780_Cursor()
{
  dpControl |= LCD_CURSORON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void HD44780_NoBlink()
{
  dpControl &= ~LCD_BLINKON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void HD44780_Blink()
{
  dpControl |= LCD_BLINKON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}


void SendCommand(uint8_t cmd)
{
  Send(cmd, 0);
}

void SendChar(uint8_t ch)
{
  Send(ch, RS);
}

void Send(uint8_t value, uint8_t mode)
{
  uint8_t highnib = value & 0xF0;
  uint8_t lownib = (value<<4) & 0xF0;
  Write4Bits((highnib)|mode);
  Write4Bits((lownib)|mode);
}

void Write4Bits(uint8_t value)
{
  ExpanderWrite(value);
  PulseEnable(value);
}


void PulseEnable(uint8_t _data)
{
  ExpanderWrite(_data | ENABLE);
  DelayUS(20);

  ExpanderWrite(_data & ~ENABLE);
  DelayUS(20);
}

void ExpanderWrite(uint8_t _data)
{
  uint8_t data = _data | dpBacklight;
  TW_Status = HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, (uint8_t*)&data, 1, 10);
}


void HD44780_PrintSpecialChar(uint8_t index)
{
  SendChar(index);
}

void HD44780_LoadCustomCharacter(uint8_t char_num, uint8_t *rows)
{
  HD44780_CreateSpecialChar(char_num, rows);
}

void HD44780_PrintStr(const char c[])
{
  while(*c) SendChar(*c++);
}


void HD44780_Display()
{
  dpControl |= LCD_DISPLAYON;
  SendCommand(LCD_DISPLAYCONTROL | dpControl);
}

void HD44780_Clear()
{
  SendCommand(LCD_CLEARDISPLAY);
  DelayUS(2000);
}

void DelayInit(void)
{
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
  CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk;

  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

  DWT->CYCCNT = 0;

  /* 3 NO OPERATION instructions */
  asm volatile ("NOP");
  asm volatile ("NOP");
  asm volatile ("NOP");
}

void DelayUS(uint32_t us) {
  uint32_t cycles = (SystemCoreClock/1000000L)*us;
  uint32_t start = DWT->CYCCNT;
  volatile uint32_t cnt;

  do
  {
    cnt = DWT->CYCCNT - start;
  } while(cnt < cycles);
}
// -----------------------------------------------------------------------------------







/*
 * Display_2x16.h
 *
 *  Created on: 30 gen 2024
 *      Author: penfra
 */

#ifndef INC_DISPLAY_2X16_H_
#define INC_DISPLAY_2X16_H_


//#include "main.h"
#include "i2c.h"
#include "Global.h"


#define MAX_COL_DISPLAY         16            // Numero massimo di colonne del display

#define MAX_ROWS_DISPLAY        2             // Numero massimo di righe del display

#define SLAVE_ADDRESS_LCD       0x4E          // (78 decimale) Indirizzo modulo display lcd I2C


struct MenuStaz
{
	uint8_t row;
	uint8_t col;
	uint16_t tempo;
	char *PtrStazione1;
};




// ----------------------------------------------------------------------------
/* Display On/Off */
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00



/* Entry Mode */
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Function Set */
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

/* Command */
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

/* Backlight */
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

/* Enable Bit */
#define ENABLE 0x04

/* Read Write Bit */
#define RW 0x0

/* Register Select Bit */
#define RS 0x01

void SendCommand(uint8_t);
void SendChar(uint8_t);
void Send(uint8_t, uint8_t);
void Write4Bits(uint8_t);
void ExpanderWrite(uint8_t);
void PulseEnable(uint8_t);
void DelayInit(void);
void DelayUS(uint32_t);

void HD44780_NoDisplay();
void HD44780_Display();
void HD44780_NoBlink();
void HD44780_Blink();
void HD44780_NoCursor();
void HD44780_Cursor();

void HD44780_Init(uint8_t rows);

void HD44780_CreateSpecialChar(uint8_t, uint8_t[]);
void HD44780_PrintSpecialChar(uint8_t);
void HD44780_Home();
void HD44780_Display();

void HD44780_Clear();

void HD44780_CreateSpecialChar(uint8_t, uint8_t[]);
void HD44780_PrintSpecialChar(uint8_t);

void HD44780_SetCursor(uint8_t, uint8_t);

void HD44780_SetBacklight(uint8_t new_val);
void HD44780_LoadCustomCharacter(uint8_t char_num, uint8_t *rows);
void HD44780_PrintStr(const char[]);


//uint8_t dpFunction;

//uint8_t dp_f;
extern uint16_t ind_display;
//static char * ptr_string;
//---------------------------------------------------------------------

//extern I2C_HandleTypeDef hi2c1;

#endif /* INC_DISPLAY_2X16_H_ */

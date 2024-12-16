/*
 * Global.h
 *
 *  Created on: 23 gen 2024
 *      Author: penfra
 *
 * Dichiarazioni globali.
 * @copyright 2024 Francesco Penocchio
 * @licenza
 * @autore Francesco Penocchio <francesco.penocchio@gmail.com>
 * @versione 0.0.1 del 23-01-2024
 * @file
 */

#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

// Inclusioni di sistema
#include <stdio.h>
#include <stdbool.h>

// Inclusioni specifiche
#include "Include.h"



// Funzioni globali

// Handler_IO
extern void FncGlbl_InitGPIO(void);
extern void FncGlbl_Cycle(void);



// Lingua dei testi visualizzati sul display
typedef enum Lingua_display_def{
  ITALIANO = 0,
  INGLESE,
  TEDESCO,
  FRANCESE,
  SPAGNOLO
  }lingua ;


// Codice del tasto premuto
typedef enum key_def{
  UP = 1,
  DOWN,
  ENTER,
  ESC,
  }key_hit ;



// Variabili globali
extern uint16_t Antirip1;
extern uint16_t Antirip2;
extern uint16_t Antirip3;
extern uint16_t Antirip4;
extern uint8_t  key_code;                       // Codice del tasto premuto

extern uint16_t dp_f1;



extern uint16_t cpu_tick_1;
extern uint16_t cpu_tick_2;
//extern TIME_Handle Rtc_Now;

extern uint8_t lingua_display;

extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;


extern uint8_t data_rx_complete;

extern uint8_t rx_buff_uart1[10];
extern uint8_t rx_buff_uart2[10];

extern uint8_t tx_buff_uart1[10];

extern uint16_t crc_val;

extern uint8_t attiva_risposta;


#endif /* SRC_GLOBAL_H_ */



/*
 * GlobalInit.c
 *
 *  Created on: 25 gen 2024
 *      Author: penfra
 *
 * Definizioni globali.
 * @copyright 2024 Francesco Penocchio
 * @licenza
 * @autore Francesco Penocchio <francesco.penocchio@gmail.com>
 * @versione 0.0.1 del 25-01-2024
 * @file
 */

#ifndef SRC_GLOBALINIT_C_
#define SRC_GLOBALINIT_C_

#include <stdio.h>
#include <stdbool.h>
//#include "Driver/Rtc_DS1307.h"
#include "Include.h"


// Inizializzare qu� tutte le variabili globali
uint16_t Antirip1 = 0;
uint16_t Antirip2 = 0;
uint16_t Antirip3 = 0;
uint16_t Antirip4 = 0;

uint16_t dp_f1 = 0;

uint16_t cpu_tick_1;
uint16_t cpu_tick_2;


uint8_t lingua_display;

//UART_HandleTypeDef huart1;
//UART_HandleTypeDef huart2;

uint8_t rx_buff_uart1[10];
uint8_t rx_buff_uart2[10];

uint16_t crc_val = 0;

uint8_t data_rx_complete = 0;


uint8_t attiva_risposta;

#endif /* SRC_GLOBAL_H_ */

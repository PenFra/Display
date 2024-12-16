/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    EEprom_24c32.h
  * @brief   This file provides code for the driver eeprom 24c32 via
  *          I2C instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Francesco Penocchio.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef EEprom_24c32_H
#define EEprom_24c32_H


/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "main.h"





/* End Includes --------------------------------------------------------------*/

/* AT24Cxx Register ----------------------------------------------------------*/
#define AT24Cxx_ADDRESS          0x50     // AT24C32 default address (Pin A0-A1-A2 = 0)
#define AT24Cxx_EEPROM_SIZE      0x1000   // EEPROM Size 4096 byte
#define AT24Cxx_PAGE_SIZE        0x20     // Page size 32 byte
#define AT24Cxx_PAGE_NUM         0x80     // Number of page 128



/* AT24Cxx External Function -------------------------------------------------*/
uint8_t AT24Cxx_EraseChip(void);
uint8_t AT24Cxx_FillPage(uint16_t Page, uint8_t Val);
uint8_t AT24Cxx_ReadByte(uint16_t MemAddr, uint8_t *pData, uint16_t Len);
uint8_t AT24Cxx_WriteByte(uint16_t MemAddr, uint8_t *value, uint16_t Len);




/* End define to prevent recursive inclusion -------------------------------------*/
#endif

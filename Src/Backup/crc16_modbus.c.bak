/*
 * crc16_modbus.c
 *
 *  Created on: May 9, 2024
 *      Author: penfra
 */


// CRC16 implementation according to CCITT standards
//

#include "crc16_modbus.h"


uint16_t CRC_MODBUS16Fast(uint16_t Crc, uint8_t Data)
{
   Crc = Crc ^ Data;

   Crc = (Crc >> 8) ^ CrcTable[Crc & 0xFF]; // Process 8-bits at a time

   return(Crc);
 }

 //******************************************************************************

 uint16_t CRC_MODBUS16FastBlock(uint16_t Crc, uint16_t Size, uint8_t *Buffer)
 {
   while(Size--)
     Crc = CRC_MODBUS16Fast(Crc, *Buffer++);

   return(Crc);
 }

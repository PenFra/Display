/*
 * Rtc_DS1307.c
 *
 *  Created on: Apr 20, 2024
 *      Author: penfra
 */


#include "Driver/Rtc_DS1307.h"
#include "Global.h"



/**
  * Global function (not necessary define here. But here for cleary)
  *********************************************************************************/
extern uint8_t DS1307_init(void);
extern void    get_clock(Clock_Handle *clock_now);
extern void    get_calendar( Calendar_Handle *calendar_now);



/**
  * Private variable
  *********************************************************************************/

static uint8_t Buffer[7];



/**
  * Private function
  ************************************************************************************************/
static uint8_t DS1307_Bus_Read(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData, uint16_t Len);
static uint8_t DS1307_Bus_Write(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData, uint16_t Len);



/* ********************************************************************************************************
 *    Interfaces
 *
 * ********************************************************************************************************/

/**
  * @brief  Initialize the RTC
  *
  */
uint8_t DS1307_init(void)
{

   uint8_t ret_val = FAILED;
   uint8_t status;

   ret_val = DS1307_GetClockHalt(DS1307_ADDRESS, &status);                    /* ret_val 0 = SUCCESS, 1 = FAILED */

   if ( ( DS1307_Enabled == status ) && ( SUCCESS == ret_val ) ) {            /* Check if year is = 0 then rtc is the first time on. */
      DS1307_OscillatorEOSC( DS1307_REG_CLOCK_HALT, DS1307_Disable);          /* RTC Disable Oscillator. = Diasable (= 0) rtc running, = Eenable (= 1) rtc stopped */
   }

   return ret_val;
}



/**
  * @brief  Get three field of clock
  *
  * @param  - clock_now - The parameter passed at the end contains: seconds, minutes, hours. type (uint8_t)
  *
  */
void get_clock( Clock_Handle *clock_now )
{

   uint8_t nr_byte = 3;                                                    /* Number byte to receive */
   uint8_t start_reg_address = DS1307_REG_SECONDS;                         /* Start register address. */
   uint8_t buffer[nr_byte];                                                /* Buffer conteins number byte to received */
   uint8_t mask_ch_bit = DS1307_MASK_CLOCK_HALT;                           /* Mask to getting a correct value of seconds */
   uint8_t ret_val = SUCCESS;                                              /* Return value bus_read function. 0 = Success, 1 = Failed */

   ret_val = DS1307_Bus_Read(DS1307_ADDRESS, start_reg_address, buffer, nr_byte);

   if ( SUCCESS == ret_val ){
      clock_now->seconds = BcdToDec( ( buffer[0] & mask_ch_bit ) );               /* Mask bit 7 (CH - clock halt) */
      clock_now->minutes = BcdToDec( buffer[1] );
      clock_now->hour    = BcdToDec( buffer[2] );
   }
}


/**
  * @brief  Get three field of calendar
  *
  * @param  - calendar_now - The parameter passed at the end contains: dayofmonth, month, year (0-99). type (uint8_t)
  *
  */
void get_calendar( Calendar_Handle *calendar_now )
{
   uint8_t nr_byte = 3;                                                    /* Number byte to receive */
   uint8_t start_reg_address = 0x04;                                       /* Start register address. */
   uint8_t buffer[nr_byte];                                                /* Buffer conteins number byte to received */
   uint8_t ret_val = SUCCESS;                                              /* Return value bus_read function. 0 = Success, 1 = Failed */

   ret_val = DS1307_Bus_Read(DS1307_ADDRESS, start_reg_address, buffer, nr_byte);

   if ( 0 == ret_val ){
      calendar_now->dayofmonth = BcdToDec( buffer[0] );
      calendar_now->month      = BcdToDec( buffer[1] );
      calendar_now->year       = BcdToDec( buffer[2] );
   }
}

/* End Interfaces **************************************************************************************************/



/**
  * @brief  I2C Bus Write
  * @retval Success = 0, Failed = 1
  * @param  DevAddr     Target device address
  * @param  MemAddr     Internal memory address
  * @param  pData       Pointer to data buffer
  * @param  Len      Amount of data to be Write
  */
static uint8_t DS1307_Bus_Write(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData, uint16_t Len)
{

   if (HAL_I2C_Mem_Write(&hi2c1, DevAddr, MemAddr, I2C_MEMADD_SIZE_8BIT, pData,
         Len, HAL_MAX_DELAY) != 0)
   {
      return 1;
   }

   return 0;
}



/**
  * @brief  I2C Bus Read
  *
  * @param  DevAddr     Target device address
  * @param  MemAddr     Internal memory address
  * @param  pData       Pointer to data buffer
  * @param  Len         Amount of data to be read
  *
  * @retval Success     = 0, Failed = 1
  */
static uint8_t DS1307_Bus_Read(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData, uint16_t Len)
{
   if ( SUCCESS != HAL_I2C_Mem_Read(&hi2c1, DevAddr, MemAddr, I2C_MEMADD_SIZE_8BIT, pData, Len, HAL_MAX_DELAY) )
   {
      return FAILED;
   }

   return SUCCESS;
}



// Register -------------------------------------------------------------

/**
  * @brief  Enable Oscillator
  * @param  mode  DS1307_Enabled | DS1307_Disable
  */
void DS1307_OscillatorEOSC(uint8_t reg_addr, uint8_t mode)
{
   uint8_t register_clock_halt= DS1307_REG_CLOCK_HALT;
   uint8_t nr_byte = 1;                                                    /* Number byte to receive */

   DS1307_Bus_Read(DS1307_ADDRESS, reg_addr, &register_clock_halt, nr_byte);


   if (DS1307_Disable == mode ){
      register_clock_halt &= ~(1 << DS1307_BIT_CLOCK_HALT);                /* Clearing bit */
   }
   else{
      register_clock_halt |= (mode << DS1307_BIT_CLOCK_HALT);              /* Setting bit */
   }

   DS1307_Bus_Write(DS1307_ADDRESS, reg_addr, &register_clock_halt, 1);

}

/**
 * @brief Sets the byte in the designated DS1307 register to value.
 *
 * @param regAddr   - Register address to write.
 * @param val Value - to set, 0 to 255.
 */
void DS1307_SetRegByte(uint8_t regAddr, uint8_t val) {

   uint8_t bytes[2] = { regAddr, val };

   HAL_I2C_Master_Transmit(&hi2c1, DS1307_ADDRESS << 1, bytes, 2, DS1307_TIMEOUT);
}


/**
 * @brief    Gets clock halt bit.
 *
 * @reg_addr - Address of bit clock start/stop (DS1307 = 0x00)
 * @return   - Clock halt bit, 0 or 1.
 *
 */
uint8_t DS1307_GetClockHalt(uint8_t reg_addr, uint8_t *status) {

   uint8_t nr_byte = 1;                                                    /* Number byte to receive */
   uint8_t start_reg_address = 0x00;                                       /* Start register address. */
   uint8_t bus_read_result = SUCCESS;                                      /* Return value bus_read result. 0 = Success, 1 = Failed */

   uint8_t buffer[nr_byte];

   bus_read_result = DS1307_Bus_Read(DS1307_ADDRESS, start_reg_address, buffer, nr_byte) ;

   if ( SUCCESS == bus_read_result ){
      buffer[0] >>= DS1307_BIT_CLOCK_HALT;
      *status = buffer[0];
   }


   return bus_read_result;
}



// End Register ----------------------------------------------------------


// GET -------------------------------------------------------------------


/**
  * @brief  Get Current time from RTC
  * @param  Now   Pointer to TIME_handler structure
  */
void DS1307_Time_Date_Get (TIME_Handle *Now)
{
   DS1307_Bus_Read(DS1307_ADDRESS, 0x00, Buffer, 7);
   Now->seconds      = BcdToDec( ( Buffer[0] & 0x7F ) );    // Elimina il bit 7 che ha la funzione di start
   Now->minutes      = BcdToDec( Buffer[1] );
   Now->hour         = BcdToDec( Buffer[2] );
   Now->dayofweek    = BcdToDec( Buffer[3] );
   Now->dayofmonth   = BcdToDec( Buffer[4] );
   Now->month        = BcdToDec( Buffer[5] );
   Now->year         = BcdToDec( Buffer[6] );
}


/**
  * @brief  Get Current clock from RTC
  * @param  Now   Pointer to Clock_Handle structure
  */
void DS1307_clock_get (Clock_Handle *Now)
{
   DS1307_Bus_Read(DS1307_ADDRESS, 0x00, Buffer, 3);
   Now->seconds      = BcdToDec( ( Buffer[0] & 0x7F ) );    // Elimina il bit 7 che ha la funzione di start
   Now->minutes      = BcdToDec( Buffer[1] );
   Now->hour         = BcdToDec( Buffer[2] );

}


/**
  * @brief  Get Current calendar from RTC
  * @param  Now   Pointer to Clock_Handle structure
  */
void DS1307_calendar_get (Calendar_Handle *Now)
{
   DS1307_Bus_Read(DS1307_ADDRESS, 0x04, Buffer, 4);

   Now->dayofmonth   = BcdToDec( Buffer[1] );
   Now->month        = BcdToDec( Buffer[2] );
   Now->year         = BcdToDec( Buffer[3] );
}







/**
 * @brief Gets the byte in the designated DS1307 register.
 * @param regAddr Register address to read.
 * @return Value stored in the register, 0 to 255.
 */
uint8_t DS1307_GetRegByte(uint8_t regAddr) {
   uint8_t val;
   HAL_I2C_Master_Transmit(&hi2c1, DS1307_ADDRESS << 1, &regAddr, 1, DS1307_TIMEOUT);
   HAL_I2C_Master_Receive(&hi2c1, DS1307_ADDRESS << 1, &val, 1, DS1307_TIMEOUT);
   return val;
}


/**
 * @brief Gets the current day of week.
 * @return Days from last Sunday, 0 to 6.
 */
uint8_t DS1307_GetDayOfWeek(void) {
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_DOW));
}

/**
 * @brief Gets the current day of month.
 * @return Day of month, 1 to 31.
 */
uint8_t DS1307_GetDate(void) {
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_DATE));
}

/**
 * @brief Gets the current month.
 * @return Month, 1 to 12.
 */
uint8_t DS1307_GetMonth(void) {
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_MONTH));
}

/**
 * @brief Gets the current year.
 * @return Year, 2000 to 2099.
 */
uint16_t DS1307_GetYear(void) {
   uint16_t cen = DS1307_GetRegByte(DS1307_REG_CENT) * 100;
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_YEAR)) + cen;
}

/**
 * @brief Gets the current hour in 24h format.
 * @return Hour in 24h format, 0 to 23.
 */
uint8_t DS1307_GetHour(void) {
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_HOURS) & 0x3f);
}

/**
 * @brief Gets the current minute.
 * @return Minute, 0 to 59.
 */
uint8_t DS1307_GetMinute(void) {
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_MINUTES));
}

/**
 * @brief Gets the current second. Clock halt bit not included.
 * @return Second, 0 to 59.
 */
uint8_t DS1307_GetSecond(void) {
   return DS1307_DecodeBCD(DS1307_GetRegByte(DS1307_REG_SECONDS) & 0x7f);
}

/**
 * @brief Gets the stored UTC hour offset.
 * @note  UTC offset is not updated automatically.
 * @return UTC hour offset, -12 to 12.
 */
int8_t DS1307_GetTimeZoneHour(void) {
   return DS1307_GetRegByte(DS1307_REG_UTC_HR);
}

/**
 * @brief Gets the stored UTC minute offset.
 * @note  UTC offset is not updated automatically.
 * @return UTC time zone, 0 to 59.
 */
uint8_t DS1307_GetTimeZoneMin(void) {
   return DS1307_GetRegByte(DS1307_REG_UTC_MIN);
}



// End GET ----------------------------------------------------------------





// SET --------------------------------------------------------------------

/**
  * @brief  Set Target time to RTC
  * @param  sec   Seconds, 0-60
  * @param  min   Minute, 0-60
  * @param  hour  Hours, 0-23
  */
void DS1307_clock_set ( uint8_t sec, uint8_t min, uint8_t hour )
{

   uint8_t Buffer[3];
   memset(Buffer, 0x00, sizeof(Buffer));
   Buffer[0] = DecToBcd(sec);
   Buffer[1] = DecToBcd(min);
   Buffer[2] = DecToBcd(hour);

   DS1307_Bus_Write(DS1307_ADDRESS, 0x00, Buffer, sizeof(Buffer));
}

/**
  * @brief  Set Target calendar to RTC
  * @param  dow   Days of the week, 1-7
  * @param  dom   Days of the month, 1-31
  * @param  month    Month, 1-12
  * @param  year     Year, 21, 22 ...
  */
void DS1307_calendar_set ( uint8_t dow, uint8_t dom, uint8_t month, uint8_t year )
{
   uint8_t Buffer[3];
   memset(Buffer, 0x00, sizeof(Buffer));
   Buffer[0] = DecToBcd(dom);
   Buffer[1] = DecToBcd(month);
   Buffer[2] = DecToBcd(year);

   DS1307_Bus_Write(DS1307_ADDRESS, DS1307_REG_DATE, Buffer, sizeof(Buffer));
}



/**
  * @brief  Set Target time and date to RTC
  * @param  sec   Seconds, 0-60
  * @param  min   Minute, 0-60
  * @param  hour  Hours, 0-23
  * @param  dow   Days of the week, 1-7
  * @param  dom   Days of the month, 1-31
  * @param  month    Month, 1-12
  * @param  year     Year, 21, 22 ...
  */
void DS1307_Time_Date_Set (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom,
      uint8_t month, uint8_t year)
{
   memset(Buffer, 0x00, sizeof(Buffer));
   Buffer[0] = DecToBcd(sec);
   Buffer[1] = DecToBcd(min);
   Buffer[2] = DecToBcd(hour);
   Buffer[3] = DecToBcd(dow);
   Buffer[4] = DecToBcd(dom);
   Buffer[5] = DecToBcd(month);
   Buffer[6] = DecToBcd(year);

   DS1307_Bus_Write(DS1307_ADDRESS, 0x00, Buffer, sizeof(Buffer));
}


/**
 * @brief Sets clock halt bit.
 * @param halt Clock halt bit to set, 0 or 1. 0 to start timing, 0 to stop.
 */
void DS1307_SetClockHalt(uint8_t halt) {
   uint8_t ch = (halt ? 1 << 7 : 0);
   DS1307_SetRegByte(DS1307_REG_SECONDS, ch | (DS1307_GetRegByte(DS1307_REG_SECONDS) & 0x7f));
}




/**
 * @brief Sets the current day of week.
 * @param dayOfWeek Days since last Sunday, 0 to 6.
 */
void DS1307_SetDayOfWeek(uint8_t dayOfWeek) {
   DS1307_SetRegByte(DS1307_REG_DOW, DS1307_EncodeBCD(dayOfWeek));
}

/**
 * @brief Sets the current day of month.
 * @param date Day of month, 1 to 31.
 */
void DS1307_SetDate(uint8_t date) {
   DS1307_SetRegByte(DS1307_REG_DATE, DS1307_EncodeBCD(date));
}

/**
 * @brief Sets the current month.
 * @param month Month, 1 to 12.
 */
void DS1307_SetMonth(uint8_t month) {
   DS1307_SetRegByte(DS1307_REG_MONTH, DS1307_EncodeBCD(month));
}

/**
 * @brief Sets the current year.
 * @param year Year, 2000 to 2099.
 */
void DS1307_SetYear(uint16_t year) {
   DS1307_SetRegByte(DS1307_REG_CENT, year / 100);
   DS1307_SetRegByte(DS1307_REG_YEAR, DS1307_EncodeBCD(year % 100));
}

/**
 * @brief Sets the current hour, in 24h format.
 * @param hour_24mode Hour in 24h format, 0 to 23.
 */
void DS1307_SetHour(uint8_t hour_24mode) {
   DS1307_SetRegByte(DS1307_REG_HOURS, DS1307_EncodeBCD(hour_24mode & 0x3f));
}

/**
 * @brief Sets the current minute.
 * @param minute Minute, 0 to 59.
 */
void DS1307_SetMinute(uint8_t minute) {
   DS1307_SetRegByte(DS1307_REG_MINUTES, DS1307_EncodeBCD(minute));
}

/**
 * @brief Sets the current second.
 * @param second Second, 0 to 59.
 */
void DS1307_SetSecond(uint8_t second) {

   uint8_t status_ch = 0;

   uint8_t ch = DS1307_GetClockHalt(DS1307_ADDRESS, &status_ch);

   DS1307_SetRegByte(DS1307_REG_SECONDS, DS1307_EncodeBCD(second | ch));
}

/**
 * @brief Sets UTC offset.
 * @note  UTC offset is not updated automatically.
 * @param hr UTC hour offset, -12 to 12.
 * @param min UTC minute offset, 0 to 59.
 */
void DS1307_SetTimeZone(int8_t hr, uint8_t min) {
   DS1307_SetRegByte(DS1307_REG_UTC_HR, hr);
   DS1307_SetRegByte(DS1307_REG_UTC_MIN, min);
}




/* *****************************************************************************************
 * UTILITY
 * *****************************************************************************************/

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal value retrieved from register, 0 to 255.
 * @return Decoded decimal value.
 */
uint8_t DS1307_DecodeBCD(uint8_t bin) {
   return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}

/**
 * @brief Encodes a decimal number to binaty-coded decimal for storage in registers.
 * @param dec Decimal number to encode.
 * @return Encoded binary-coded decimal value.
 */
uint8_t DS1307_EncodeBCD(uint8_t dec) {
   return (dec % 10 + ((dec / 10) << 4));
}





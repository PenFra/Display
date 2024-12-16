/*
 * Rtc_DS1307.h
 *
 *  Created on: Apr 20, 2024
 *      Author: penfra
 */

//#include "main.h"
#include "stm32l4xx_hal.h"

#ifndef INC_DRIVER_RTC_DS1307_H_
#define INC_DRIVER_RTC_DS1307_H_


#define SUCCESS               0x00
#define FAILED                0x01


#define DS1307_Disable        0x00
#define DS1307_Enabled        0x01

#define DS1307_ADDRESS        0xD0
#define DS1307_ALARM_1        0X07
#define DS1307_ALARM_2        0X0B
#define DS1307_TEMP_MSB       0X11
#define DS1307_CONTROL        0X0E
#define DS1307_STATUS         0X0F

#define DS1307_CTRL_A1IE      0x00  // Alarm 1 Interrupt Enable
#define DS1307_CTRL_A2IE      0x01  // Alarm 2 Interrupt Enable
#define DS1307_CTRL_INTCN     0x02  // Interrupt Control
#define DS1307_CTRL_RS1       0x03  // Rate Select 2
#define DS1307_CTRL_RS2       0x04  // Rate Select 2
#define DS1307_CTRL_CONV      0x05  // Convert Temperature
#define DS1307_CTRL_BBSQW     0x06  // Battery-Backed Square-Wave Enable
#define DS1307_CTRL_EOSC      0x07  // Enable Oscillator

#define DS1307_STAT_A1F       0x00  // Alarm 1 Flag
#define DS1307_STAT_A2F       0x01  // Alarm 2 Flag
#define DS1307_STAT_BSY       0x02  // Busy
#define DS1307_STAT_EN32K     0x03  // Enable 32kHz Output
#define DS1307_STAT_OSF       0x07  // Oscillator Stop Flag



//----------------------------------------------------------------------------
#define DS1307_REG_CLOCK_HALT    0x00  // Register containing the clock halt bit
#define DS1307_BIT_CLOCK_HALT    0x07  // Bit number clock halt
#define DS1307_MASK_CLOCK_HALT   0x7F  /* Mask bit to isolate clock halt in the register */


#define DS1307_REG_SECONDS    0x00
#define DS1307_REG_MINUTES    0x01
#define DS1307_REG_HOURS      0x02
#define DS1307_REG_DOW        0x03
#define DS1307_REG_DATE       0x04
#define DS1307_REG_MONTH      0x05
#define DS1307_REG_YEAR       0x06
#define DS1307_REG_CONTROL    0x07
#define DS1307_REG_UTC_HR     0x08
#define DS1307_REG_UTC_MIN    0x09
#define DS1307_REG_CENT       0x10
#define DS1307_REG_RAM        0x11
#define DS1307_TIMEOUT        1000


/* Struct --------------------------------------------------------------------*/
typedef struct RetValue{
   uint8_t error;
   uint8_t buffer[10];
}ret_value;


/* Custom Macro --------------------------------------------------------------*/
#define DecToBcd(val) ( (val/10*16) + (val % 10) )
#define BcdToDec(val) ( (val/16*10) + (val % 16) )

/* DS3231 Data Structure -----------------------------------------------------*/
typedef struct {
   uint8_t seconds;
   uint8_t minutes;
   uint8_t hour;
   uint8_t dayofweek;
   uint8_t dayofmonth;
   uint8_t month;
   uint8_t year;
} TIME_Handle;


typedef struct {
   uint8_t seconds;
   uint8_t minutes;
   uint8_t hour;
 } Clock_Handle;


 typedef struct {
    uint8_t dayofmonth;
    uint8_t month;
    uint8_t year;
 } Calendar_Handle;





typedef enum
{
  MODE_ALL,
  MODE_HOUR_MIN_SEC,
  MODE_HOUR_MIN,
  MODE_MIN_SEC,
  MODE_MIN,
  MODE_SEC,
  MODE_ONCE_PER_MIN,
  MODE_ONCE_PER_SEC
} AlarmMode;

typedef enum
{
   SQW_1HZ,
   SQW_1024HZ,
   SQW_4096HZ,
   SQW_8192HZ
}SQWRate;

typedef enum
{
   ALL,
   A1,
   A2
}Alarm;

/* Global variable  -------------------------------------------------------------*/



/* End Global variable  ---------------------------------------------------------*/



/* External Function (interface) ------------------------------------------------*/

extern uint8_t DS1307_init(void);
extern void    get_clock(Clock_Handle *clock_now);
extern void    get_calendar( Calendar_Handle *calendar_now);


/* End External Function (interface) --------------------------------------------*/




/* SET & GET Control Register ---------------------------------------------------*/

void     DS1307_OscillatorEOSC(uint8_t reg_addr, uint8_t mode);
uint8_t  DS1307_GetClockHalt(uint8_t reg_addr, uint8_t *status) ;
uint8_t  DS1307_GetRegByte(uint8_t regAddr);

/* END Register -----------------------------------------------------------------*/


void     DS1307_Time_Date_Get(TIME_Handle *Now);



/* INIT -------------------------------------------------------------------------*/
//void     DS1307_Init(I2C_HandleTypeDef *hi2c);

/* END INIT ---------------------------------------------------------------------*/



uint8_t  DS1307_GetFlag(uint8_t Reg);
void     DS1307_GetAlarm(void);



/* SET ---------------------------------------------------------------------------*/

void DS1307_Time_Date_Set(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);

void DS1307_clock_set ( uint8_t sec, uint8_t min, uint8_t hour );
void DS1307_calendar_set ( uint8_t dow, uint8_t dom, uint8_t month, uint8_t year );

void DS1307_SetClockHalt(uint8_t halt);

void DS1307_SetRegByte(uint8_t regAddr, uint8_t val);

void DS1307_SetDayOfWeek(uint8_t dow);
void DS1307_SetDate(uint8_t date);
void DS1307_SetMonth(uint8_t month);
void DS1307_SetYear(uint16_t year);

void DS1307_SetHour(uint8_t hour_24mode);
void DS1307_SetMinute(uint8_t minute);
void DS1307_SetSecond(uint8_t second);
void DS1307_SetTimeZone(int8_t hr, uint8_t min);

/* END SET -----------------------------------------------------------------------*/




/* GET LOCAL ---------------------------------------------------------------------*/



void DS1307_calendar_get (Calendar_Handle *Now);

uint8_t DS1307_GetDayOfWeek(void);
uint8_t DS1307_GetDate(void);
uint8_t DS1307_GetMonth(void);
uint16_t DS1307_GetYear(void);

uint8_t DS1307_GetHour(void);
uint8_t DS1307_GetMinute(void);
uint8_t DS1307_GetSecond(void);
int8_t DS1307_GetTimeZoneHour(void);
uint8_t DS1307_GetTimeZoneMin(void);


// ALARM ---------------------------------------------------------------------------------
void DS1307_EnableInterrupt(uint8_t mode);

void DS1307_Alarm1_Interrupt(uint8_t mode);
void DS1307_Alarm2_Interrupt(uint8_t mode);
void DS1307_SetAlarm1(uint8_t mode, uint8_t sec, uint8_t min, uint8_t hour, uint8_t dydt);
void DS1307_SetAlarm2(uint8_t mode, uint8_t min, uint8_t hour, uint8_t dydt);
// END ALARM -----------------------------------------------------------------------------


/* SQUARE OUT ---------------------------------------------------------------------------------*/
void DS1307_32kHzOutput(uint8_t mode);
/* END SQUARE OUT -----------------------------------------------------------------------------*/

/* UTILITY ------------------------------------------------------------------------------------*/
uint8_t DS1307_DecodeBCD(uint8_t bin);
uint8_t DS1307_EncodeBCD(uint8_t dec);

/* END SERVICE UTILITY ------------------------------------------------------------------------*/



#endif /* INC_DRIVER_RTC_DS1307_H_ */

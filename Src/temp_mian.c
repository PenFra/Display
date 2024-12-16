/*
 * temp_mian.c
 *
 *  Created on: 27 apr 2024
 *      Author: penfra
 */


/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "Driver/adc.h"
#include "dma.h"
//#include "i2c.h"


#include "gpio.h"

#include "Global.h"
#include "Init.h"

#include "Driver/Rtc_DS1307.h"


TIME_Handle       Rtc_Now;
Clock_Handle      clock_Now;
Calendar_Handle   calendar_Now;


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */


   HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */


  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */


  /* USER CODE BEGIN 2 */


  Antirip1 = 0;
  Antirip2 = 0;
  Antirip3 = 0;
  Antirip4 = 0;



  Init_micro();
  Init_sys();
  /* USER CODE END 2 */


  FncGlbl_InitGPIO();

//  leggi_rtc();

  init_main_menu();



  HAL_Delay(100);


  lingua_display = ITALIANO;
//  DS3231_TimeSet(Second, Minute, Hour, DayOfWeek, Day, Month, Year);


  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

//     if( ++cpu_tick_2 > 450 )
//       {
//           //DS1307_Time_Date_Get( &Rtc_Now );
//           DS1307_get_time_date();
//           cpu_tick_2 = 0;
//
//        }

    // Tasto down (tasto giallo)
    if ( 0 == HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_2 ) && 0 == Antirip1)
       {
           cpu_tick_1++;

         if ( cpu_tick_1 > 150 )
            {
               HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );

               handle_menu( DOWN );

               //next_down_menu();
               Antirip1 = 1;
            }
       }


    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1 && Antirip1 == 1)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      cpu_tick_1 = 0;
      Antirip1 = 0;
    }


    // Tasto up (tasto giallo)
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0 && Antirip2 == 0)
    {
      cpu_tick_1++;

      if(cpu_tick_1 > 150)
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

        handle_menu(UP);
        //next_up_menu();

        Antirip2 = 1;
      }
    }

    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1 && Antirip2 == 1)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      cpu_tick_1 = 0;
      Antirip2 = 0;
    }




    // Menu principale invio (tasto verde)
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 0 && Antirip3 == 0)
    {
      cpu_tick_1++;

      if(cpu_tick_1 > 350)
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        handle_menu(ENTER);
        Antirip3 = 1;
      }
    }

    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 1 && Antirip3 == 1)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      cpu_tick_1 = 0;
      Antirip3 = 0;
    }


    // Menu principale esci (tasto rosso)
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == 0 && Antirip4 == 0)
    {
      cpu_tick_1++;

      if(cpu_tick_1 > 350)
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        handle_menu(ESC);
        Antirip4 = 1;
      }
    }

    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == 1 && Antirip4 == 1)
    {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      cpu_tick_1 = 0;
      Antirip4 = 0;
    }




    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
******************************************************************************
* @file           : Menu.c
* @brief          : Handling menu navigation and data manages
******************************************************************************
*
*
*  Created on: 5 feb 2024
*      @Author: penfra
*
*
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
#include "Include.h"

#include "Global.h"
#include "Define.h"
#include "Menu.h"
#include <stdio.h>
#include <string.h>
#include "Driver/Display_2x16.h"
#include "Driver/Rtc_DS1307.h"


/**
  * Global function
  *********************************************************************************/
extern var_def parameters_data[MAX_DIM_ROW_SUB_MENU_1];


/**
  * Private variable
  *********************************************************************************/

static ts_menu_status menu_status;                          // Structure thet contain navigation menu state

//static TIME_Handle Rtc_Now;
static Clock_Handle clock_now;
static Calendar_Handle calendar_now;

uint16_t ind_display;
uint16_t nr_serie = 46890;



/**
  * Private function
  *********************************************************************************/




/**
  * @brief Inizializza le variabili e gli array e visualizza
  *        il menu principale all'accensione
  *
  *
  */
void init_main_menu(void)
{
  uint16_t dim_array = 0;

  dim_array = (ARRAY_SIZE(MainMenuDef) - 1);

  //last_item_display = 0;                                            // Imposta la posizione del prompt

  menu_status.max_row_display = MAX_ROWS_DISPLAY -1;
  menu_status.next_item_display = 0;
  menu_status.prompt = PROMPT;
  menu_status.clear_prompt = CLEAR_PROMPT;

  main_page_init_menu(&menu_status,dim_array);

  menu_status.next_item_display = 1;
  menu_status.current_pos_prompt_row = 0;
  menu_status.main_index = 0;
  menu_status.sub_menu_index = 0;
  menu_status.level = 0;
  menu_status.index_element = 0;


  char char_null[2];


  // new_menu.sub_menu[0].parameters_data = parameters_data;






  /* Riempie gli array con i testi nella lingua selezionata */
  for (uint8_t row = 0; row <= MAX_DIM_ROW_MAIN_MENU-1; row++)          // Loop per il numero di righe del display
  {

     /* Legge il primo carattere dall'array dei testi per capire se i testi sono terminati*/
     snprintf((char*) &char_null, 2,(char*) MainMenuDef[row][lingua_display]);
     if(char_null[0] != '\0')                                    // Se il contatore delle righe � minore o uguale al numero di elementi dell'array
    {
      snprintf((char*) &main_menu_display[row],15,(char*) MainMenuDef[row][lingua_display]);

 //     snprintf((char*) &new_menu.main_menu_display[row],15,(char*) MainMenuDef[row][lingua_display]);


    }else
    {
       break;
    }

  }


}

/**
  * @brief Display the main menu page
  *
  * @param - menu_status - menu navigator status
  * @param - nr_element  - number menu elements
  *
  */

uint8_t main_page_init_menu(ts_menu_status *menu_status, uint8_t nr_element)
{

  char * ptrstring;

  pos_init_prompt(menu_status);

  for (uint8_t row = 0; row <= (menu_status->max_row_display); row++)          // Loop per il numero di righe del display
  {
    if(row <= nr_element)                                    // Se il contatore delle righe � minore o uguale al numero di elementi dell'array
    {
       // Visualizza gli elementi del menu
       HD44780_SetCursor(row, 1);

       ptrstring = (char*) MainMenuDef[row][lingua_display];
       HD44780_PrintStr(ptrstring);

    }
    else
    {
      break;
    }
 }

  return menu_status->main_index;
}



/**
  * @brief   Init page sub-menu level-1
  *
  * @param - menu_status
  * @param - sub_menu
  * @param - nr_element
  *
  * @return - index menu element
  *
  */
uint8_t sub_menu_init_page(ts_menu_status *menu_status,char sub_menu[][MAX_LANGUAGES][MAX_COL_DISPLAY -1], uint8_t nr_element)
{

   char * ptrstring;

   pos_init_prompt(menu_status);

   for (uint8_t row = 0; row <= (menu_status->max_row_display); row++)          // Loop per il numero di righe del display
   {
     if(row <= nr_element)                                    // Se il contatore delle righe � minore o uguale al numero di elementi dell'array
     {
        // Visualizza gli elementi del menu
        HD44780_SetCursor(row, 1);

        ptrstring = sub_menu[row ][lingua_display];
        HD44780_PrintStr(ptrstring);
     }
     else
     {
       break;
     }
  }

   //print_prompt((char*)menu_status->prompt, menu_status->current_pos_prompt_row);              // Visualizza il prompt sulla posizione corrente del menu

   return menu_status->sub_menu_index;
}


/**
  * Posizione iniziale del prompt
  *
  * @Parameters: menu_status
  *
  */
void pos_init_prompt(ts_menu_status *menu_status)
{
  HD44780_SetCursor(1, menu_status->pos_column_prompt);
  HAL_Delay(2);
  HD44780_PrintStr((char *)menu_status->clear_prompt);
  HAL_Delay(2);
  HD44780_SetCursor(0, menu_status->pos_column_prompt);
  HD44780_PrintStr((char *)menu_status->prompt);
  HAL_Delay(2);
  menu_status->current_pos_prompt_row = 0;
}

/**
  * Inizializzazione dei menu
  *
  * @Parameters:
  *
  */
void init_var_menu(void)
{
  menu_status.next_item_display = 0;
  menu_status.current_pos_prompt_row = 0;
  menu_status.level = 0;

}


/**
  * Tasti navigazione dei menu
  *
  * @Parameters:
  *
  */

void button_navigation_handler(void)
{
   // Tasto down (tasto giallo)
   if ( 0 == HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_2 ) && 0 == Antirip1)
     {
         cpu_tick_1++;

       if ( cpu_tick_1 > 150 )
          {
             HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );

             handle_menu( DOWN );

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

            crc_val = 0;
            uint8_t tx_buff[8];

            tx_buff[0] = 0x01;
            tx_buff[1] = 0x01;
            tx_buff[2] = 0x00;
            tx_buff[3] = 0x00;

            crc_val = CRC_MODBUS16FastBlock(INIT_CRC, 4, tx_buff);

            tx_buff[4] = (uint8_t) crc_val & 0x00FF;
            tx_buff[5] = (uint8_t) (crc_val >> 8);
            tx_buff[6] = '\r';
            tx_buff[7] = '\n';

            HAL_UART_Transmit(&huart1, tx_buff, sizeof(tx_buff) , 100);


            Antirip2 = 1;
       }
   }

   if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1 && Antirip2 == 1)
      {
         /* tasto rilasciato */
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

}


/*
 * Gestione dei menu
 *
 * @Parameters: key - Tasto premuto della tastiera di navigazione
 *
 */
void handle_menu(uint8_t key)
{

   switch(key)
   {

       default:

       break;

    case UP:	// Tasto giallo "up"

      if ( menu_status.mode == NAVIGATION_MODE )                                                               //
         {

         menu_status.sub_menu_index = prompt_up_1(&menu_status,  ptr_main_menu, ( ARRAY_SIZE ( Parameters_Def) - 1 ));

            /* Se sono nella modalita di navigazione menu */
            if ( menu_status.level == NAVIGATION_MAIN_MENU )
              {
        	         /* Se sono nel livello di navigazione del menu principale*/
                  menu_status.main_index = prompt_up( &menu_status, MainMenuDef, ( ARRAY_SIZE ( MainMenuDef ) - 1 ) );
              }

           if ( menu_status.level == NAVIGATION_SUB_MENU )
           	  {
				  if ( menu_status.main_index == 0)
				   	 {





				         menu_status.sub_menu_index = prompt_up(&menu_status, Parameters_Def, ( ARRAY_SIZE ( Parameters_Def) - 1 ) );
				   	 }
				  if(menu_status.main_index == 1)
				    {
					  	  menu_status.sub_menu_index = prompt_up(&menu_status, ParStaz1_Def, (ARRAY_SIZE(ParStaz1_Def) - 1));
				    }
           	  }
         }

	  if ( menu_status.mode == EDIT_MODE )
		  {
			 if ( menu_status.level == NAVIGATION_SUB_MENU )
				 {
			         if( menu_status.index_element == 0 )
					     {
							  change_value( &menu_status, &parameters_data[0], key );
					     }
					 if ( menu_status.index_element == 1 )
					   {
							 change_value( &menu_status, &parameters_data[1], key );
					   }
				  }
		   }


	 break;



    case DOWN:	// Tasto giallo "down"
          if ( menu_status.mode == NAVIGATION_MODE )
             {

                 if ( menu_status.level == NAVIGATION_MAIN_MENU )
                    {
                       menu_status.main_index = prompt_down( &menu_status, MainMenuDef, ( ARRAY_SIZE( MainMenuDef )  - 1 ) );
                     }
                 if ( menu_status.level == NAVIGATION_SUB_MENU )
                    {
                       if ( menu_status.main_index == 0 )
                          {



                                menu_status.sub_menu_index = prompt_down( & menu_status, Parameters_Def, ( ARRAY_SIZE ( Parameters_Def ) - 1 ) );
                          }

                       if ( menu_status.main_index == NAVIGATION_SUB_MENU )
                          {
                                menu_status.sub_menu_index = prompt_down( &menu_status, ParStaz1_Def, ( ARRAY_SIZE ( ParStaz1_Def ) - 1 ) );
                           }
                    }
             }
          if ( menu_status.mode == EDIT_MODE )
             {
                 if ( menu_status.level == NAVIGATION_SUB_MENU )
                    {
                         if ( menu_status.index_element == 0 )
                            {
                                 change_value( &menu_status, &parameters_data[0], key );
                            }

                         if ( menu_status.index_element == 1 )
                            {
                                 change_value( &menu_status, &parameters_data[1], key );
                            }

                    }
             }

             break;



    case ENTER: // Tasto verde "enter"
          if ( menu_status.level == NAVIGATION_MAIN_MENU )
             {
                 if ( menu_status.main_index == 0 )
                    {
                       menu_status.level = NAVIGATION_SUB_MENU;
                       menu_status.index_element = 0;
                       menu_status.sub_menu_index = sub_menu_init_page(&menu_status, Parameters_Def, ( ARRAY_SIZE ( Parameters_Def) - 1 ) );
                    }

                    break;
             }

          if ( menu_status.level == NAVIGATION_SUB_MENU )
             {
                switch ( menu_status.main_index )
                {
                   default:

                   break;

                   case 0:                                               // First item main menu
                        switch ( menu_status.sub_menu_index )
                        {
                           default:
                           break;

                           case 0:  // First item sub-menu - ---- (calendar data) -----

                              if ( menu_status.mode == EDIT_MODE )                    // Edit mode
                                 {
                                    // Check field presence
                                    if ( parameters_data[0].nr_fields > 0 )
                                       {
                                          // Go to next field
                                          if ( ++menu_status.index_field >= parameters_data[0].nr_fields )
                                             {
                                                 menu_status.index_field = 0;
                                             }
                                       }
                                     select_field ( &menu_status, &parameters_data[0] );
                                 }
                              else
                                 {

                                    char name_par[MAX_COL_DISPLAY -1];

                                    strcpy(name_par, Parameters_Def[0][lingua_display]);

                                    display_data ( &menu_status, &parameters_data[0], name_par );
                                    menu_status.mode = EDIT_MODE;
                                 }

                           break;

                           case 1:   // Second item sub-menu - ----- (clock data) -----

                                if ( menu_status.mode == EDIT_MODE )
                                   {
                                      // Check field presence
                                      if ( parameters_data[1].nr_fields > 0 )
                                         {
                                             // Go to next field
                                             if ( ++menu_status.index_field >= parameters_data[1].nr_fields )
                                                {
                                                    menu_status.index_field = 0;
                                                }
                                         }
                                         select_field ( &menu_status, &parameters_data[1] );
                                    }
                                 else
                                    {

                                       char name_par[MAX_COL_DISPLAY -1];

                                       strcpy(name_par, Parameters_Def[1][lingua_display]);



                                       display_data ( &menu_status, &parameters_data[1], name_par );
                                       menu_status.mode = EDIT_MODE;
                                    }
                           break;

                           case 2:   // Third item sub-menu - (display TWI address)

                                 if ( menu_status.mode == EDIT_MODE )
                                    {
                                        // Check field presence
                                        if ( parameters_data[2].nr_fields > 0 )
                                           {
                                              // Go to next field
                                              if ( ++menu_status.index_field >= parameters_data[2].nr_fields )
                                                 {
                                                    menu_status.index_field = 0;
                                                 }
                                            }
                                        if ( parameters_data[2].write_var == READ_AND_WRITE )
                                           {
                                              select_field ( &menu_status, &parameters_data[2] );
                                           }
                                    }
                                 else
                                    {
                                       char name_par[MAX_COL_DISPLAY -1];

                                       strcpy(name_par, Parameters_Def[2][lingua_display]);

                                       display_data ( &menu_status, &parameters_data[2], name_par );

                                       if ( parameters_data[2].write_var == READ_AND_WRITE ) {
                                              menu_status.mode = EDIT_MODE;
                                          }
                                    }

                           break;

                        } // end switch ( menu_status.sub_menu_index )

                   break;

                } //  switch ( menu_status.main_index )
            }
    break;



    // Tasto rosso "esc"
    case ESC:
          if ( menu_status.level != NAVIGATION_MAIN_MENU )
             {
                  HD44780_NoBlink();
                  HD44780_NoCursor();
                  HD44780_Clear();
                  init_var_menu();

                  main_page_init_menu ( &menu_status, ( ARRAY_SIZE ( MainMenuDef ) - 1 ) );
             }


          if ( menu_status.mode == EDIT_MODE  )
             {
                if ( menu_status.sub_menu_index == 0 )
                   {

                      calendar_now.dayofmonth = parameters_data[0].par_calendar.edit_day;
                      calendar_now.month = parameters_data[0].par_calendar.edit_month;
                      calendar_now.year = (uint8_t) ( parameters_data[0].par_calendar.edit_year - 2000);

                      DS1307_calendar_set( 1, calendar_now.dayofmonth, calendar_now.month, calendar_now.year );
                   }


                if ( menu_status.sub_menu_index == 1 )
                   {

                      clock_now.seconds = parameters_data[1].par_clock.edit_seconds;
                      clock_now.minutes = parameters_data[1].par_clock.edit_minutes;
                      clock_now.hour =  parameters_data[1].par_clock.edit_hours;

                      DS1307_clock_set( clock_now.seconds, clock_now.minutes, clock_now.hour);
                   }
             }


          menu_status.level = NAVIGATION_MAIN_MENU;
          menu_status.sub_menu_index = 0;
          menu_status.main_index = 0;
          menu_status.mode = NAVIGATION_MODE;
          menu_status.index_field = 0;
    break;
  }
}



/*
 * Visualizza i dati inerenti la voce del menu o sub menu
 *
 *
 */
void display_data (ts_menu_status *menu_status, var_def *par_var_disp, char *name_par)
{

 // char *disp_string;
  char ptrstring[15] = "";


  HD44780_Clear();

  HD44780_SetCursor(1, 1);
  HAL_Delay(2);


  // Visualizza il nome del campo variabile
  //disp_string = menu[menu_status->index_element][lingua_display];
  HD44780_PrintStr(name_par);

//  if(menu_status->level == NAVIGATION_SUB_MENU && menu_status->sub_menu_index == 0 )
//  {
    // Primo elemento del sub-menu (Parametri)

    if(par_var_disp->type_var == CALENDAR_TYPE)
      {
          // data

          HD44780_SetCursor(par_var_disp->fields_position[menu_status->index_field].row, par_var_disp->fields_position[menu_status->index_field].column);

          get_calendar(&calendar_now);
          par_var_disp->par_calendar.edit_day = calendar_now.dayofmonth;
          par_var_disp->par_calendar.edit_month = calendar_now.month;
          par_var_disp->par_calendar.edit_year = calendar_now.year +2000;

          sprintf(ptrstring, par_var_disp->print_format, calendar_now.dayofmonth, calendar_now.month, calendar_now.year + 2000);

          HD44780_PrintStr(ptrstring);
      }
//  }

//  if(menu_status->level == NAVIGATION_SUB_MENU && menu_status->sub_menu_index == 1 )
//   {

    if(par_var_disp->type_var == TIME_TYPE)
      {
        // ora
        //HD44780_SetCursor(0, 1);



        uint8_t row = par_var_disp->fields_position[menu_status->index_field].row ; //var_display[menu_status.index_element].fields_position[menu_status.index_field].row;
        uint8_t col = par_var_disp->fields_position[menu_status->index_field].column;


        HD44780_SetCursor(row,col );

        get_clock(&clock_now);
        par_var_disp->par_clock.edit_hours = clock_now.hour;
        par_var_disp->par_clock.edit_minutes = clock_now.minutes;
        par_var_disp->par_clock.edit_seconds = clock_now.seconds;

        sprintf(ptrstring,par_var_disp->print_format ,clock_now.hour , clock_now.minutes, clock_now.seconds);


        HD44780_PrintStr(ptrstring);
      }
//   }

    if(par_var_disp->type_var == INT_TYPE)
      {
        uint8_t row = par_var_disp->fields_position[menu_status->index_field].row ;
        uint8_t col = par_var_disp->fields_position[menu_status->index_field].column;


        HD44780_SetCursor(row,col );



        sprintf(ptrstring, "%03d", *par_var_disp->var_data_union.s_int16_value);


        HD44780_PrintStr(ptrstring);

      }

  // Select field
  if(parameters_data[menu_status->index_element].nr_fields != 0)
   {
     select_field(menu_status, par_var_disp);
   }


}


/*
 * Cambia il valore alla variabile
 *
 *
 */


void change_value(ts_menu_status *menu_status, var_def *var_display, uint8_t key)
{

   if(menu_status->level == NAVIGATION_SUB_MENU && menu_status->sub_menu_index == 0 )
   {
     change_calendar(menu_status, var_display,  key);

   }

   if(menu_status->level == NAVIGATION_SUB_MENU && menu_status->sub_menu_index == 1 )
   {
     change_clock(menu_status, var_display,  key);

   }


}


/*
 * Cambia variabili del calendario
 *
 */

void change_calendar(ts_menu_status *menu_status, var_def *var_display, uint8_t key)
{
  char ptrstring[15];

  if(menu_status->index_field == 0)
  {
    if(key == UP)
    {
      if(var_display->par_calendar.edit_day++ >= var_display->par_calendar.max_day )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_calendar.edit_day = var_display->par_calendar.min_day;
      }
    }


    if(key == DOWN)
    {
      if(var_display->par_calendar.edit_day-- <= var_display->par_calendar.min_day )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_calendar.edit_day = var_display->par_calendar.max_day;
      }
    }


    HD44780_SetCursor(0, 1);
    sprintf(ptrstring, "%02d", var_display->par_calendar.edit_day);
    HD44780_PrintStr(ptrstring);
    HD44780_SetCursor(0, 1);

  }

  if(menu_status->index_field == 1)
  {

    if(key == UP)
    {
      if(var_display->par_calendar.edit_month++ >= var_display->par_calendar.max_month )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_calendar.edit_month = var_display->par_calendar.min_month;
      }
    }
    if(key == DOWN)
    {
      if(var_display->par_calendar.edit_month-- <= var_display->par_calendar.min_month )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_calendar.edit_month = var_display->par_calendar.max_month;
      }
    }


    HD44780_SetCursor(0, 4);
    sprintf(ptrstring, "%02d", var_display->par_calendar.edit_month);
    HD44780_PrintStr(ptrstring);
    HD44780_SetCursor(0, 4);
  }

  if(menu_status->index_field == 2)
   {
    if(key == UP)
    {
      if(var_display->par_calendar.edit_year++ >= var_display->par_calendar.max_year )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_calendar.edit_year = var_display->par_calendar.min_year;
      }
    }
    if(key == DOWN)
    {
      if(var_display->par_calendar.edit_year-- <= var_display->par_calendar.min_year )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_calendar.edit_year = var_display->par_calendar.max_year;
      }
    }



    HD44780_SetCursor(0, 7);
    sprintf(ptrstring, "%04d", var_display->par_calendar.edit_year) ;
    HD44780_PrintStr(ptrstring);
    HD44780_SetCursor(0, 7);
   }

//  if(menu_status->index_field == 0)
//  {
//    HD44780_SetCursor(0, 1);
//  }
//
//  if(menu_status->index_field == 1)
//  {
//    HD44780_SetCursor(0, 4);
//  }
//  if(menu_status->index_field == 2)
//  {
//    HD44780_SetCursor(0, 7);
//  }
//
//  HD44780_Blink();

}


/*
 * Cambia variabili dell'orologio
 *
 */

void change_clock(ts_menu_status *menu_status, var_def *var_display, uint8_t key)
{

  char ptrstring[15] = "";

  if(menu_status->index_field == 0)
  {
    if(key == UP)
    {
      if(var_display->par_clock.edit_hours >= var_display->par_clock.max_hours)
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_clock.edit_hours = var_display->par_clock.min_hours;
      }
      else
      {
        var_display->par_clock.edit_hours++;
      }

    }

    if(key == DOWN)
    {
      if(var_display->par_clock.edit_hours <= var_display->par_clock.min_hours)
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_clock.edit_hours = var_display->par_clock.max_hours;
      }
      else
      {
        var_display->par_clock.edit_hours--;
      }

    }

    HD44780_SetCursor(0, 1);
    sprintf(ptrstring, "%02d", var_display->par_clock.edit_hours);
    HD44780_PrintStr(ptrstring);
    HD44780_SetCursor(0, 1);

  }

  if(menu_status->index_field == 1)
  {

    if(key == UP)
    {
      if(var_display->par_clock.edit_minutes++ >= var_display->par_clock.max_minutes)
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_clock.edit_minutes = var_display->par_clock.min_minutes;
      }
    }
    if(key == DOWN)
    {
      if(var_display->par_clock.edit_minutes-- <= var_display->par_clock.min_minutes )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_clock.edit_minutes =var_display->par_clock.max_minutes;
      }
    }

     HD44780_SetCursor(0, 4);
     sprintf(ptrstring, "%02d", var_display->par_clock.edit_minutes);
     HD44780_PrintStr(ptrstring);
     HD44780_SetCursor(0, 4);
  }

  if(menu_status->index_field == 2)
   {
    if(key == UP)
    {
      if(var_display->par_clock.edit_seconds++ >= var_display->par_clock.max_seconds )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_clock.edit_seconds = var_display->par_clock.min_seconds;
      }
    }
    if(key == DOWN)
    {
      if(var_display->par_clock.edit_seconds-- <= var_display->par_clock.min_seconds )
      {
        // Primo elemento e primo campo del sub-menu (Parametri-data-giorno)
        var_display->par_clock.edit_seconds = var_display->par_clock.max_seconds;
      }
    }

    HD44780_SetCursor(0, 7);
    sprintf(ptrstring, "%02d", var_display->par_clock.edit_seconds) ;
    HD44780_PrintStr(ptrstring);
    HD44780_SetCursor(0, 7);
   }

}


/*
 * Select fields on the var display
 *
 */
void select_field(ts_menu_status *menu_status, var_def *var_display)
{

  HD44780_SetCursor(var_display->fields_position[menu_status->index_field].row, var_display->fields_position[menu_status->index_field].column);


//  if(menu_status->index_field == 0)
//   {
//     HD44780_SetCursor(0, 1);
//   }
//
//   if(menu_status->index_field == 1)
//   {
//     HD44780_SetCursor(0, 4);
//   }
//   if(menu_status->index_field == 2)
//   {
//     HD44780_SetCursor(0, 7);
//   }

      HD44780_Blink();
}





/*
 * Sposta verso il basso il prompt
 *
 *
 */
uint8_t prompt_down(ts_menu_status *menu_status,char menu[][MAX_LANGUAGES][MAX_COL_DISPLAY -1], uint8_t nr_element)
{

  char * ptrstring;

  if(menu_status->current_pos_prompt_row < menu_status->max_row_display)                        // Controlla se il cursore pu� andare alla riga successiva in base al tipo di display
  {
    if(menu_status->next_item_display <= nr_element)                                            // Controlla se il cursore pu� andare sull'elemento successivo dell'array menu
    {
      HD44780_SetCursor(menu_status->current_pos_prompt_row, menu_status->pos_column_prompt);
      HAL_Delay(2);
      HD44780_PrintStr((char *)menu_status->clear_prompt);
      HAL_Delay(10);
      HD44780_SetCursor(menu_status->current_pos_prompt_row + 1, menu_status->pos_column_prompt);
      HD44780_PrintStr((char *)menu_status->prompt);
      HAL_Delay(2);
      menu_status->current_pos_prompt_row++;
      ++menu_status->index_element;

    }
  }
  else
  {
    // Scorre gli elementi del menu verso l'alto finchè non incontra la fine dell'array

    if(menu_status->index_element < nr_element )
    {

      for (uint8_t row = 0; row <= ( menu_status->max_row_display); row++)          // Loop per il numero di righe del display
      {

        HD44780_SetCursor(row, 1);

        ptrstring = menu[menu_status->index_element + row ][lingua_display];

        HD44780_PrintStr(ptrstring);
        HAL_Delay(2);

      }

      menu_status->index_element++;
      menu_status->next_item_display++;  // all'ultimo elemento vale +1 rispetto alla fine.
    }
  }

  return menu_status->index_element;
}


/*
 * Sposta il prompt verso l'alto
 *
 *
 */
uint8_t prompt_up_1(ts_menu_status *menu_status, char (*ptr_main_menu)[MAX_DIM_ROW_MAIN_MENU][MAX_LANGUAGES][16 -1], uint8_t nr_element)
{

   char * ptrstring;

   //ptrstring = (char*) ptr_main_menu+1;
   ptrstring = (char*) ptr_main_menu[0][0][lingua_display + 1 ];
   HD44780_SetCursor(1, 1);
    HAL_Delay(2);
    HD44780_PrintStr(ptrstring);
    HAL_Delay(2);

    ptrstring = (char*) ptr_main_menu[0][1][lingua_display + 1];
    HD44780_SetCursor(1, 1);
     HAL_Delay(2);
     HD44780_PrintStr(ptrstring);
     HAL_Delay(2);

   for (uint8_t row = 0; row <= menu_status->max_row_display ; row++)          // Loop per il numero di righe del display
    {

      //ptrstring = (char*) ptr_main_menu[(menu_status->index_element - 1 )+ row][lingua_display];
         //ptrstring = menu[(menu_status->index_element - 1 )+ row ][lingua_display];
    }
   HD44780_SetCursor(1, 1);
   HAL_Delay(2);
   HD44780_PrintStr(ptrstring);
   HAL_Delay(2);

   return 1;
}


/*
 * Sposta il prompt verso l'alto
 *
 *
 */
uint8_t prompt_up(ts_menu_status *menu_status, char menu[][MAX_LANGUAGES][MAX_COL_DISPLAY -1], uint8_t nr_element)
{
  char * ptrstring;

  //uint8_t previus_menu_element = last_item_display - 1;


  if (menu_status->next_item_display > nr_element)
  {
    menu_status->next_item_display = nr_element;
  }

  if(menu_status->current_pos_prompt_row > 0)                                     // Controlla se il cursore pu� andare alla riga precedente in base al tipo di display
  {
    if(menu_status->index_element >= 0)                                              // Controlla se il cursore pu� andare sull'elemento precedente dell'array menu
    {
      HD44780_SetCursor(menu_status->current_pos_prompt_row, menu_status->pos_column_prompt);
      HAL_Delay(2);
      HD44780_PrintStr((char *)menu_status->clear_prompt);

      HAL_Delay(2);
      HD44780_SetCursor(menu_status->current_pos_prompt_row - 1, menu_status->pos_column_prompt);
      HD44780_PrintStr((char *)menu_status->prompt);
      HAL_Delay(2);

      menu_status->next_item_display--;
      menu_status->current_pos_prompt_row-- ;
      menu_status->index_element-- ;    //index_menu--;
    }
  }
  else
  {
    if(menu_status->index_element > 0)
    {
      //last_item_display = scroll_down_menu(last_item_display);
      //uint8_t index_item_menu = last_item_menu -2;


      for (uint8_t row = 0; row <= menu_status->max_row_display ; row++)          // Loop per il numero di righe del display
      {

        HD44780_SetCursor(row, 1);

        ptrstring = menu[(menu_status->index_element - 1 )+ row ][lingua_display];

        HD44780_PrintStr(ptrstring);
        HAL_Delay(2);

      }
      menu_status->index_element--;
      menu_status->next_item_display--;

      //return 1;

    }
  }

  return menu_status->index_element;

}











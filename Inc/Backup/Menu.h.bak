/*
 * Menu.h
 *
 *  Created on: 5 feb 2024
 *      Author: penfra
 */





#include "Driver/Display_2x16.h"
#include "Global.h"

//#include "main.h"

#ifndef INC_MENU_H_
#define INC_MENU_H_



#define PROMPT            ">"                       // Prompt character
#define CLEAR_PROMPT      " "                       // Clearing prompt character
#define POS_PROMPT_COL    0                         // Position prompt column

#define MAX_LANGUAGES     5                         // Max number of languages manage
#define MAX_DISP_CHAR     MAX_COL_DISPLAY -1        // Max number of display characters


#define EDIT_MODE         1
#define NAVIGATION_MODE   0

#define NAVIGATION_MAIN_MENU  0
#define NAVIGATION_SUB_MENU   1

#define MAX_ITEM_MENU         10
#define MAX_DEEP_SUB_MENU     4



#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))    //< Generic macro for obtaining number of elements of an array
/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)

/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])


// Type of data variable managed
enum enum_type_var
{
  BOOLEAN = 0,
  U_BYTE,
  BYTE,
  U_INTEGER_16,
  INTEGER_16,
  INTEGER_32,
  DYNAMIC_TEXT,
  LONG,

}type_var;


// **********************************************************************************************************
// Data struct construction
// **********************************************************************************************************


// **********************************************************************************************************
// MAIN MENU



void *(ptr_void) ;

#define MAX_DIM_ROW_MAIN_MENU 10
#define MAX_DIM_COL_MAIN_MENU MAX_LANGUAGES

//    ITALIANO            INGLESE          TEDESCO            FRANCESE            SPAGNOLO
char MainMenuDef[MAX_DIM_ROW_MAIN_MENU][MAX_LANGUAGES][MAX_DISP_CHAR] = {
    {"parametri " ,"parameters" ,"parameter" ,"parametres" ,"parametros"},
    {"stazione 1" ,"Station 1 " ,"Station 1" ,"Station 1 " ,"Station 1 "},
    {"stazione 2" ,"Station 2 " ,"Station 2" ,"Station 2 " ,"Station 2 "},
    {"stazione 3" ,"Station 3 " ,"Station 3" ,"Station 3 " ,"Station 3 "},
    {"stazione 4" ,"Station 4 " ,"Station 4" ,"Station 4 " ,"Station 4 "},
    {"stazione 5" ,"Station 5 " ,"Station 5" ,"Station 5 " ,"Station 5 "},
    {"stazione 6" ,"Station 6 " ,"Station 6" ,"Station 6 " ,"Station 6 "},
    {""           , ""          ,""          ,""           ,""          }
};

char main_menu_display[MAX_ITEM_MENU][MAX_DISP_CHAR];

char (*ptr_main_menu)[MAX_DIM_ROW_MAIN_MENU][MAX_LANGUAGES][MAX_DISP_CHAR]  = &MainMenuDef;



// **********************************************************************************************************








// **********************************************************************************************************
// MENU NAVIGATION STATUS

typedef struct MenuStatus
{
  uint8_t current_pos_prompt_row;
  uint8_t next_item_display;
  uint8_t max_dim_menu;
  uint8_t pos_column_prompt;
  uint8_t main_index;
  uint8_t sub_menu_index;
  uint8_t index_element;
  uint8_t max_row_display;
  uint8_t pos_col_prompt;
  uint8_t level;
  uint8_t mode;                                 // Edit mode. 0 = arrows button use to navigate menu item, 1 = arrows button change data value.
  uint8_t index_field;                          // Numero del campo selezionato nella pagina visualizzata.
  char *prompt;
  char *clear_prompt;

}ts_menu_status;


// **********************************************************************************************************






#define MAX_FIELDS            5                     // Max number of fields in the diplay area

typedef struct
{
    uint8_t edit_day;
    uint8_t min_day;
    uint8_t max_day;

    uint8_t edit_month;
    uint8_t min_month;
    uint8_t max_month;

     uint16_t edit_year;
     uint16_t min_year;
     uint16_t max_year;

}ParamCalendar;                                                          // Calendar management

typedef struct
 {
     uint8_t edit_hours;
     uint8_t min_hours;
     uint8_t max_hours;


     uint8_t edit_minutes;
     uint8_t min_minutes;
     uint8_t max_minutes;


     uint8_t edit_seconds;
     uint8_t min_seconds;
     uint8_t max_seconds;



 }ParamClock;                                                            // Clock management



typedef struct RT_CLOCK
{
  ParamCalendar   rt_calendar;
  ParamClock      rt_clock;
}rt_clock;                                                          // Clock-Calendar management



typedef struct
{
  uint8_t   row;
  uint8_t   column;
}field_pos_def;


typedef struct
{
   uint8_t seconds;
   uint8_t minutes;
   uint8_t hours;
}ClockData;


typedef struct
{
   uint8_t day_of_month;
   uint8_t month;
   uint16_t year;                                     /* (int16_t) value from 2000 to 2099  */
}CalendarData;



typedef struct VarDef
{
  enum {INT_TYPE, FLOAT_TYPE, CALENDAR_TYPE, TIME_TYPE, STRING_TYPE} type_var;      // Type var managed
  enum {READ_ONLY, READ_AND_WRITE} write_var;                                       // Allows to edit data variables.

  union Var_Union {
      int16_t    *s_int16_value;
      uint16_t   *uint16_value;
      float *float_value;
      char  *string_value[16];
  }var_data_union;                                                    // Exclusive data type managed.

  union MIN_Union {
      int   int_value;
      float float_value;
  }var_min_union;                                                     // Lower limit data.


  union MAX_Union {
       int   int_value;
       float float_value;

   }var_max_union;                                                    // Higer limit data.

  ParamCalendar   par_calendar;                                         // Calendar data
  ParamClock      par_clock;                                            // Clock data

  ClockData       *clock_data;
  CalendarData    *calendar_data;


  uint8_t         nr_fields;                                                // Numero di campi che compone la variabile.
  field_pos_def   fields_position[MAX_FIELDS];                              // Posizione dei campi nelle coordinate del display (riga, colonna)
  char            *print_format;                                        // Print format string. Es.: "%02d:%02d"

  uint8_t         var_type;                                                 // Tipo di variablile utilizzata. 0 = int, 1 = float, 2 = boolean , 3 = Dynamic text?

  char            *unit_mis[4];
  uint8_t         nr_dec;                                                   // Number of decimal displayed


  //char *gen_purpos[8];                                                // General purpos array char


}var_def;

// -------------- Data structure definition -----------------------------------------------------------



// **********************************************************************************************************
// FIRST SUB MENU

// Text structure definition
#define MAX_DIM_ROW_SUB_MENU_1 10


//    ITALIANO            INGLESE          TEDESCO            FRANCESE            SPAGNOLO
char Parameters_Def[MAX_DIM_ROW_SUB_MENU_1][MAX_LANGUAGES][MAX_DISP_CHAR] = {
    {"data         ", "date         " ,"jetzt        " ,"date           " ,"fecha          "},
    {"ora          ", "hour         " ,"datum        " ,"heures         " ,"horas          "},
    {"ind. display ", "addr. display" ,"addr.anzeige " ,"adress.afficher" ,"direct. pantal."},
    {"release      ", "release      " ,"release      " ,"release        " ,"release        "},
    {"nr. serie    ", "nr. series   " ,"seriennummer " ,"nr. de serie   " ,"nr. de serie   "},
    {""             , ""              ,""              ,""                ,""               }
};

char main_parameters_display[MAX_ITEM_MENU][MAX_DISP_CHAR];

char (*ptr_param_menu)[MAX_DIM_ROW_SUB_MENU_1][MAX_LANGUAGES][MAX_DISP_CHAR]  = &Parameters_Def;



// **********************************************************************************************************
                                                                  // Series number of product
char      Realease[MAX_COL_DISPLAY] = {"01.00.00"};
uint16_t  nr_serie;                                                                 // Display I2C addres

struct VarDef parameters_data[MAX_DIM_ROW_SUB_MENU_1] =
{

    // Calendar data
    [0] =  {.write_var = READ_AND_WRITE ,.type_var = CALENDAR_TYPE ,
            .par_calendar.edit_day = 1,
            .par_calendar.min_day = 1,
            .par_calendar.max_day = 31,
            .par_calendar.edit_month = 1,
            .par_calendar.min_month = 1,
            .par_calendar.max_month = 12,
            .par_calendar.edit_year = 2000,
            .par_calendar.min_year = 2000,
            .par_calendar.max_year = 2050,
            .nr_fields = 3,
            .fields_position[0].row = 0, .fields_position[0].column = 1,
            .fields_position[1].row = 0, .fields_position[1].column = 4,
            .fields_position[2].row = 0, .fields_position[2].column = 7,
            .print_format = "%02d/%02d/%04d"

           },

    // Clock data
    [1] =  {.write_var = READ_AND_WRITE ,.type_var = TIME_TYPE ,
            .par_clock.edit_hours = 0,
            .par_clock.min_hours = 0,
            .par_clock.max_hours = 23,

            .par_clock.edit_minutes = 0,
            .par_clock.min_minutes = 0,
            .par_clock.max_minutes = 59,

            .par_clock.edit_seconds = 0,
            .par_clock.min_seconds = 0,
            .par_clock.max_seconds = 59,

             .nr_fields = 3,
            .fields_position[0].row = 0, .fields_position[0].column = 1,
            .fields_position[1].row = 0, .fields_position[1].column = 4,
            .fields_position[2].row = 0, .fields_position[2].column = 7,
            .print_format = "%02d:%02d:%02d"

           },

    // Adress display
    [2] =  {.write_var = READ_ONLY , .type_var = INT_TYPE ,
            .var_data_union = {.uint16_value = (uint16_t*) &ind_display}  ,
            .nr_fields = 0,
            .fields_position[0].row = 0, .fields_position[0].column = 1,
            .print_format = "%02d"
           },


    // Release firmware
    [3] =  {.write_var = READ_ONLY ,.type_var = STRING_TYPE ,

            .var_data_union = {.string_value[MAX_COL_DISPLAY-1] = Realease},
            .print_format = ""
            },

    // serial number
    [4] =  {.write_var = READ_ONLY ,.type_var = FLOAT_TYPE ,

            .var_data_union = {.uint16_value = &nr_serie},
            .var_min_union  = {.int_value = 0},
            .var_max_union  = {.int_value = 0 },
            .print_format   = ""


            },

};

// **********************************************************************************************************



// **********************************************************************************************************
// SECOND SUB MENU
#define MAX_DIM_ROW_SUB_MENU_2 10


//    ITALIANO            INGLESE          TEDESCO            FRANCESE            SPAGNOLO
char ParStaz1_Def[MAX_DIM_ROW_SUB_MENU_2][MAX_LANGUAGES][MAX_DISP_CHAR] = {
    {"temperatura    " ,"temperature  " ,"temperature  " ,"temperature  " ,"temperature  "},
    {"pezzi prodotti " ,"nr piece work" ,"nr piece work" ,"nr piece work" ,"nr piece work"},
    {"preriscaldo    " ,"pre heating  " ,"pre heating  " ,"pre heating  " ,"pre heating  "},
    {"T. sosta avanti" ,"T. fwd wait  " ,"T. fwd wait  " ,"T. fwd wait  " ,"T. fwd wait  "},
    {"stato sensori  " ,"sensors state" ,"sensors state" ,"sensors state" ,"sensors state"},
    {"allarmi        " , "alarm       " ,"alarm        " ,"alarm        " ,"alarm        "},
    {""               , ""             ,""              ,""              ,""             }
};

char st1_parameters_display[MAX_ITEM_MENU][MAX_DISP_CHAR];

// **********************************************************************************************************

float staz1_temperature;

struct VarDef staz1_data[MAX_DIM_ROW_SUB_MENU_1] =
{

    // temperatura
    [0] =  {.write_var = READ_AND_WRITE ,.type_var = FLOAT_TYPE,

             .var_data_union =  {.float_value = (float*) &staz1_temperature},
             .nr_fields = 3,
             .nr_dec = 2,
             .unit_mis = {"°"},

            .fields_position[0].row = 0, .fields_position[0].column = 1

           },

    // Pezzi prodotti
    [1] =  {.write_var = READ_AND_WRITE ,.type_var = TIME_TYPE ,

             .nr_fields = 5,
            .fields_position[0].row = 0, .fields_position[0].column = 1

           },

    // Temperatura di preriscaldo
    [2] =  {.write_var = READ_ONLY , .type_var = INT_TYPE ,
            .var_data_union = {.s_int16_value = (int16_t*) &ind_display}  ,
            .nr_fields = 0,
            .fields_position[0].row = 0, .fields_position[0].column = 1,
            .print_format = "%02d"
           },


    // Tempo di sosta avanti
    [3] =  {.write_var = READ_ONLY ,.type_var = STRING_TYPE ,

            .var_data_union = {.string_value[MAX_COL_DISPLAY-1] = Realease},
            .print_format = ""
            },

    // Stato sensori
    [4] =  {.write_var = READ_ONLY ,.type_var = FLOAT_TYPE ,

            .var_data_union = {.uint16_value = (uint16_t*) &nr_serie},
            .var_min_union  = {.int_value = 0},
            .var_max_union  = {.int_value = 0 },
            .print_format   = ""


            },

    // Allarmi
    [5] =  {.write_var = READ_ONLY ,.type_var = FLOAT_TYPE ,

           .var_data_union = {.uint16_value = (uint16_t*) &nr_serie},
           .var_min_union  = {.int_value = 0},
           .var_max_union  = {.int_value = 0 },
           .print_format   = ""


           },


};

// **********************************************************************************************************










// **********************************************************************************************************
// COSTRUZIONE STRUTTURA MENU




char (*ptr_build_menu[MAX_ITEM_MENU][MAX_DEEP_SUB_MENU])[MAX_ITEM_MENU][MAX_DISP_CHAR]  =

      {{&main_menu_display , &main_parameters_display, 0x00 , 0x00},
       {0x00               , &main_menu_display      , 0x00 , 0x00}

      };



typedef struct BuildSubMenu
{
   char (*item_display)[MAX_ITEM_MENU][MAX_DISP_CHAR];
   var_def (*parameters_data1) [MAX_DIM_ROW_SUB_MENU_1];

}build_sub_menu;


typedef struct BuildMenu
{

   char (*main_menu_display)[MAX_ITEM_MENU][MAX_DISP_CHAR];
   build_sub_menu sub_menu[5];

}build_menu;


//(char*) &st1_parameters_display
char a;

build_menu new_menu = {
                        &main_menu_display,
                                          {[0] = { &st1_parameters_display, &parameters_data}}



                     };





// **********************************************************************************************************








// ************************************
// test
void call_submenu(void);


void call_sub_menu(void);

uint8_t prompt_up_1(ts_menu_status *menu_status, char (*ptr_main_menu)[MAX_DIM_ROW_MAIN_MENU][MAX_LANGUAGES][16 -1] , uint8_t nr_element);

//+++++++++++++++++++++++++++++++++++++


//void print_prompt(char *prompt, uint8_t posiz_prompt_row);


extern void init_main_menu(void);

extern void button_navigation_handler(void);

void init_var_menu(void);
void pos_init_prompt(ts_menu_status *menu_status);

uint8_t main_page_init_menu(ts_menu_status *menu_status, uint8_t nr_element);

uint8_t sub_menu_init_page(ts_menu_status *menu_status,char sub_menu[][MAX_LANGUAGES][16 -1], uint8_t nr_element);

void handle_menu(uint8_t key);

extern void HD44780_SetCursor(uint8_t, uint8_t);



uint8_t prompt_down(ts_menu_status *menu_status, char menu[][MAX_LANGUAGES][16 -1], uint8_t nr_element);
uint8_t scroll_up_menu(ts_menu_status *menu_status, char menu[][MAX_LANGUAGES][16 -1], uint8_t nr_element);

uint8_t prompt_up(ts_menu_status *menu_status, char menu[][MAX_LANGUAGES][16 -1], uint8_t nr_element);

void display_data (ts_menu_status *menu_status, var_def *par_var_disp, char *name_par );

void change_value(ts_menu_status *menu_status, var_def *var_display, uint8_t key);

void change_calendar(ts_menu_status *menu_status, var_def *var_display, uint8_t key);
void change_clock(ts_menu_status *menu_status, var_def *var_display, uint8_t key);

void select_field(ts_menu_status *menu_status, var_def *var_display);

#endif /* INC_MENU_H_ */

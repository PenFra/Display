/*
 * Init.h
 *
 *  Created on: 5 feb 2024
 *      Author: penfra
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_


//void MX_I2C1_Init(void);
void Init_micro(void);
void Init_sys(void);

void SystemClock_Config(void);


extern void MX_GPIO_Init(void);
extern void HD44780_Init(uint8_t rows);
extern  void MX_DMA_Init(void);
extern  void MX_ADC1_Init(void);
//extern  void MX_I2C1_Init(void);
extern  void MX_RTC_Init(void);
extern  void MX_TIM1_Init(void);

extern void MX_USART1_UART_Init(void);

//void MX_GPIO_Init(void);
//void SystemClock_Config(void);

#endif /* INC_INIT_H_ */

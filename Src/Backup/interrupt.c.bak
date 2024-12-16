/*
 * interrupt.c
 *
 *  Created on: May 10, 2024
 *      Author: penfra
 */

#include "stm32l4xx_hal.h"
#include "usart.h"

#include "Global.h"

#include "stm32l4xx_it.h"




/* UART1 RX Callback */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_IT(&huart1, rx_buff_uart1, sizeof(rx_buff_uart1)-1); //You need to toggle a breakpoint on this line!
  //HAL_UART_Receive_DMA(&huart1, rx_buff_uart1, 6);

  attiva_risposta = 1;

}




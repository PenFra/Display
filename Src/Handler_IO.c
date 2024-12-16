



#include "Include.h"

#include "Global.h"
#include "Handler_IO.h"

void FncGlbl_InitGPIO(void)
{
	InitGPIO();
}


void FncGlbl_Cycle(void)
{

	InOutPin();
}


void InOutPin(void)
{

	Antirip1 = 0;



	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0 && Antirip == false)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		Antirip = true;
		Counter++;
		printf("Accensione numero: %d \n", Counter);
		printf("LED VERDE ON \n");
	}

	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1 && Antirip == true)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		Antirip = false;
		printf("LED VERDE OFF\n");

	}

}




void InitGPIO(void)
{

	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA5 */
	  GPIO_InitStruct.Pin = GPIO_PIN_5;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  __HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIO pin : PC13 */
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;


	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);




}


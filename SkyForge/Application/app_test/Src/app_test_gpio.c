#include "bsp_gpio.h"
#include "main.h"

void APP_Test_GPIO(void)
{
  /*  BSP_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    HAL_Delay(500);
    */
	 if (BSP_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
	    {
	        BSP_GPIO_WritePin(LD2_GPIO_Port,
	                          LD2_Pin,
	                          GPIO_PIN_SET);
	    }
	    else
	    {
	        BSP_GPIO_WritePin(LD2_GPIO_Port,
	                          LD2_Pin,
	                          GPIO_PIN_RESET);
	    }
}


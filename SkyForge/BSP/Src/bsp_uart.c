#include "bsp_uart.h"
#include <string.h>

HAL_StatusTypeDef BSP_UART_Transmit(UART_HandleTypeDef *huart,
                                    const uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout)
{
    return HAL_UART_Transmit(huart,
                             (uint8_t *)pData,
                             Size,
                             Timeout);
}

HAL_StatusTypeDef BSP_UART_Receive(UART_HandleTypeDef *huart,
                                   uint8_t *pData,
                                   uint16_t Size,
                                   uint32_t Timeout)
{
    return HAL_UART_Receive(huart,
                            pData,
                            Size,
                            Timeout);
}

HAL_StatusTypeDef BSP_UART_TransmitBinary(UART_HandleTypeDef *huart,
                                          uint8_t value)
{
    char binary[10];

    for (uint8_t i = 0; i < 8; i++)
    {
        if (value & (1U << (7 - i)))
        {
            binary[i] = '1';
        }
        else
        {
            binary[i] = '0';
        }
    }

    binary[8] = '\r';
    binary[9] = '\n';

    return HAL_UART_Transmit(huart,
                             (uint8_t *)binary,
                             sizeof(binary),
                             HAL_MAX_DELAY);
}

HAL_StatusTypeDef BSP_UART_TransmitString(UART_HandleTypeDef *huart,
                                          const char *pString)
{
    return HAL_UART_Transmit(huart,
                             (uint8_t *)pString,
                             strlen(pString),
                             HAL_MAX_DELAY);
}

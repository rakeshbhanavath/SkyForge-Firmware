#ifndef BSP_UART_H
#define BSP_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/*==============================================================================
 * Public Function Prototypes
 *============================================================================*/

HAL_StatusTypeDef BSP_UART_Transmit(UART_HandleTypeDef *huart,
                                    const uint8_t *pData,
                                    uint16_t Size,
                                    uint32_t Timeout);

HAL_StatusTypeDef BSP_UART_Receive(UART_HandleTypeDef *huart,
                                   uint8_t *pData,
                                   uint16_t Size,
                                   uint32_t Timeout);

HAL_StatusTypeDef BSP_UART_TransmitString(UART_HandleTypeDef *huart,
                                          const char *pString);

HAL_StatusTypeDef BSP_UART_TransmitBinary(UART_HandleTypeDef *huart,
                                          uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* BSP_UART_H */

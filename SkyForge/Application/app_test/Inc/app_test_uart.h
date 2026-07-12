/******************************************************************************
 * @file    app_test_uart.h
 * @brief   UART BSP Test Application
 ******************************************************************************/

#ifndef APP_TEST_UART_H
#define APP_TEST_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * Includes
 *============================================================================*/

#include "main.h"

/*==============================================================================
 * Public Function Prototypes
 *============================================================================*/

/**
 * @brief Execute the UART BSP test.
 *
 * This function validates UART transmission using the BSP UART APIs.
 */
void APP_Test_UART(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_TEST_UART_H */

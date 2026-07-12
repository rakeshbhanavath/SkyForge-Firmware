/******************************************************************************
 * @file    app_test_gpio.h
 * @brief   GPIO application test interface.
 *
 * This module contains functions used to test GPIO functionality
 * on the target hardware.
 *
 * Author : SkyForge
 ******************************************************************************/

#ifndef APP_TEST_GPIO_H
#define APP_TEST_GPIO_H

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
 * @brief Execute the GPIO test application.
 *
 * This function is intended to be called periodically from the
 * main application loop.
 */
void APP_Test_GPIO(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_TEST_GPIO_H */

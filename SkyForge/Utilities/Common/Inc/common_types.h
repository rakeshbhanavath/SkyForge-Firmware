/******************************************************************************
 * @file    common_types.h
 * @brief   Common data types used across the SkyForge framework.
 *
 * @details
 * This file contains generic data types that are shared between BSP,
 * Drivers, Services and Application layers.
 *
 * Future additions:
 * - Callback function types
 * - Generic handle types
 * - Shared enumerations
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

/* Exported Types -----------------------------------------------------------*/

/**
 * @brief SkyForge common status codes.
 *
 * These status values are returned by SkyForge modules instead of exposing
 * vendor-specific status types (e.g. STM32 HAL_StatusTypeDef).
 */
typedef enum
{
    SF_OK = 0,              /**< Operation completed successfully. */
    SF_ERROR,               /**< General error. */
    SF_BUSY,                /**< Resource is busy. */
    SF_TIMEOUT,             /**< Operation timed out. */
    SF_INVALID_PARAMETER,   /**< Invalid function parameter. */
    SF_NOT_SUPPORTED,       /**< Feature is not supported. */
    SF_NOT_INITIALIZED      /**< Module has not been initialized. */

} SF_Status_t;

#ifdef __cplusplus
}
#endif

#endif /* COMMON_TYPES_H */

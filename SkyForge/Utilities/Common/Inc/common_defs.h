/******************************************************************************
 * @file    common_defs.h
 * @brief   Common macro definitions used across the SkyForge framework.
 *
 * @details
 * This file contains generic macros shared by all software layers.
 * Only project-wide reusable macros should be defined here.
 *
 * Future additions:
 * - Bit manipulation macros
 * - Alignment macros
 * - Compiler attribute macros
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported Macros ----------------------------------------------------------*/

/**
 * @brief Returns the number of elements in an array.
 *
 * @note
 * This macro must only be used with actual arrays.
 * It must NOT be used with pointers.
 */
#define ARRAY_SIZE(array)    (sizeof(array) / sizeof((array)[0]))

/**
 * @brief Marks an unused variable.
 *
 * @note
 * Used to suppress compiler warnings for intentionally unused variables.
 */
#define UNUSED(x)            ((void)(x))

#ifdef __cplusplus
}
#endif

#endif /* COMMON_DEFS_H */

/**
 * @file error.h
 * @brief Standard error codes and error code helpers.
 * 
 * @details
 * This module provides error codes that libraries can return that are
 * always defined by this library. The exact value can differ depending
 * on the implementation used and therefor, the LIBOS_ERR_* values should
 * be used for checking.
 * The module also provides a few helper macros like returning the error
 * value if the expression doesn't evaluate to LIBOS_ERR_OK, or standard
 * checking for NULL arguments and returning LIBOS_ERR_INVALID_ARG if the
 * argument is NULL.
 * 
 * 
 * IMPLEMENTORS:
 * For the implementors it is required to provide a header file with the 
 * path 'libos/platform/error.h'. This header has to provide the
 * 'libos_err_t' typedef. And the following macro definitions that
 * must result in a expression with the type libos_err_t:
 * 
 * * LIBOS_ERR_OK
 * * LIBOS_ERR_FAIL
 * * LIBOS_ERR_NO_MEM
 * * LIBOS_ERR_INVALID_ARG
 * * LIBOS_ERR_NOTSUP
 * * LIBOS_ERR_BUSY
 * * LIBOS_ERR_TIMEOUT
 * * LIBOS_ERR_INVALID_STATE 
 * 
 * Any additional helper macros can be defined but ideally should be
 * up-streamed to the general API if they are OS & platform independent.
 * If they are not OS & platform independent, but widely used, still
 * consider up-streaming.
 * 
 * Additional error codes can be defined, but application are not allowed
 * to rely on them being present. Same as with new helper macros, if
 * general or wide usage, then upstream.
 * 
 * If the platform provides library functions they should be enclosed in 
 * a extern "C" block like: 
 * 
 * @code 
 * #ifdef __cplusplus
 * extern "C" {
 * #endif // __cplusplus
 * 
 * // Functions
 * 
 * #ifdef __cplusplus
 * }
 * #endif // __cplusplus
 * 
 * @endcode
 * 
 * Or, if it does not have a block, each function should be marked as 
 * @code
 * extern "C"
 * @endcode
 * . The general API header for the error will also place the functions
 * in a extern "C" code block when it becomes applicable.
 */

#pragma once
#ifndef LIBOS_ERROR_H
#define LIBOS_ERROR_H

#include <stddef.h>

#include "libos/platform/error.h"

// Error handling

#ifndef LIBOS_ERR_RET_ARG_IN_RANGE

/**
 * @brief Checks if the argument is within the given range and function returns LIBOS_ERR_INVALID_ARG if it isn't
 * 
 * @param value The value to do the range check on (WARNING: multiple evaluation of this are happening within the macro).
 * @param range_min The minimum number @ref value has to be (inclusive).
 * @param range_max The maximum number @ref value can be (inclusive).
 */
#define LIBOS_ERR_RET_ARG_IN_RANGE(value, range_min, range_max) LIBOS_ERR_RET_ON_TRUE(((value) < (range_min) || (value) > (range_max)), LIBOS_ERR_INVALID_ARG)
#endif // LIBOS_ERR_RET_ARG_IN_RANGE

#ifndef LIBOS_ERR_RET_ARG_NOT_NUL

/**
 * @brief Checks if the argument is not null, and if it is, return LIBOS_ERR_INVALID_ARG.
 * 
 * @details
 * This function should be specifically used for arguments that are already given. If you 
 * want to check a memory allocation from something like malloc(), use
 * @ref LIBOS_ERR_RET_MEMORY_NOT_NULL.
 * 
 * @param arg The expression to evaluate and check if it is NULL or not.
 */
#define LIBOS_ERR_RET_ARG_NOT_NUL(arg) LIBOS_ERR_RET_ON_TRUE((arg) == NULL, LIBOS_ERR_INVALID_ARG)
#endif // LIBOS_ERR_RET_ARG_NOT_NUL

#ifndef LIBOS_ERR_RET_MEMORY_NOT_NUL

/**
 * @brief Checks if the pointer is NULL or not; if it is, return LIBOS_ERR_NO_MEM.
 * 
 * @details
 * This check should be used when the given argument is a pointer just returned from a function like malloc().
 * 
 * @param ptr The value to check for NULL
 */
#define LIBOS_ERR_RET_MEMORY_NOT_NUL(ptr) LIBOS_ERR_RET_ON_TRUE(((ptr) == NULL), LIBOS_ERR_NO_MEM)
#endif // LIBOS_ERR_RET_MEMORY_NOT_NUL

#ifndef LIBOS_ERR_RET_ON_TRUE

/**
 * @brief Returns the given @ref ret value if the @ref condition evaluates to true.
 * 
 * @param condition The expression to evaluate.
 * @param ret The expression to return if the @ref condition is @code true.
 */
#define LIBOS_ERR_RET_ON_TRUE(condition, ret) do { if ((condition)) { return (ret); }} while(0)
#endif // LIBOS_ERR_RET_ON_TRUE

#endif // LIBOS_ERROR_H

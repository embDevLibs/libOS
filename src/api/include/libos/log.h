/**
 * @file log.h
 * @brief General purpose logging module.
 * 
 * @details
 * This module is provides a general API that can be used for logging
 * information from modules. The exact output system is different on
 * each system but in general will contain the time, module name,
 * log level and the log message itself.
 * 
 * With module registration, the name should be a valid C identifier.
 * Only one module per file is supported (even if the backend could
 * support more).
 * 
 * IMPORTANT: When starting the system, the logging subsystem has to
 * be initialized before it is used by calling LIBOS_INIT().
 * 
 * NOTE: All members are defined as macro's since it is possible that
 * the host platform supports defining minimum log levels at
 * compile-time which would support minimizing binary size and such.
 * 
 * TIP: A application can define the LIBOS_LOG_LEVEL_MIN to a certain
 * LIBOS_LOG_LEVEL_* value to set a minimum on the severity of the
 * log statements that are included in the application. This has to
 * be defined as a command line symbol because it can't be guaranteed
 * that if the symbol is defined later that the logging module is
 * fully aware of the value of it. If a different value is defined for
 * each translation unit, the behaviour is undefined.
 * 
 * IMPLEMENTORS:
 * A implementation should provide the following macros:
 * 
 * Log levels (any type):
 * * LIBOS_LOG_LEVEL_ERR
 * * LIBOS_LOG_LEVEL_WRN
 * * LIBOS_LOG_LEVEL_INF
 * * LIBOS_LOG_LEVEL_DBG
 * 
 * Log operations (function macros):
 * * LIBOS_LOG_PRINT(level, ...)
 * * LIBOS_LOG_MODULE_MIN_LEVEL(log_name, log_level)
 * * LIBOS_LOG_INIT()
 * 
 * The log levels priority is ERR-WRN-INFO-DBG. The module definition 
 * should only apply to the local file. However, using the same name
 * for multiple files is not supported.
 * The logging backend doesn't natively support minimum level support
 * a construction must be to made to store it in a extra static
 * variable or something similar.
 * If feasible the implementation should make a reasonable attempt to
 * make sure that the statements that are redundant are not compiled
 * into the binary but this might not be feasible. Keeping in mind the
 * cost of having such a filter on complexity, maintainability, run-time
 * overhead etc. The option of compile time minimum is partially handled
 * by the general header (based on LIBOS_LOG_LEVEL_MIN), but this doesn't
 * take the module level in account.
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
 */

#pragma once
#ifndef LIBOS_LOG_H
#define LIBOS_LOG_H

#include "libos/platform/log.h"

#ifndef LIBOS_LOG_LEVEL_MIN
#define LIBOS_LOG_LEVEL_MIN LIBOS_LOG_LEVEL_INF
#endif // LIBOS_LOG_LEVEL_MIN

#if LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_ERR
/**
 * @brief Logs a error message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_ERR(...) LIBOS_LOG_PRINT(LIBOS_LOG_LEVEL_ERR, __VA_ARGS__)
#else
/**
 * @brief Logs a error message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_ERR(...)
#endif // LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_ERR

#if LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_WRN
/**
 * @brief Logs a warning message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_WRN(...) LIBOS_LOG_PRINT(LIBOS_LOG_LEVEL_WRN, __VA_ARGS__)
#else
/**
 * @brief Logs a warning message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_WRN(...)
#endif // LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_WRN

#if LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_INF
/**
 * @brief Logs a info message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_INF(...) LIBOS_LOG_PRINT(LIBOS_LOG_LEVEL_INF, __VA_ARGS__)
#else
/**
 * @brief Logs a info message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_INF(...)
#endif // LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_INF

#if LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_DBG
/**
 * @brief Logs a debug message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_DBG(...) LIBOS_LOG_PRINT(LIBOS_LOG_LEVEL_DBG, __VA_ARGS__)
#else
/**
 * @brief Logs a debug message, printf style, if the log level minimum allows.
 * 
 */
#define LIBOS_LOG_DBG(...)
#endif // LIBOS_LOG_LEVEL_MIN > LIBOS_LOG_LEVEL_DBG

/**
 * @brief Register a log module with the logging level set to the application wide default.
 * 
 */
#define LIBOS_LOG_MODULE(log_name) LIBOS_LOG_MODULE_MIN_LEVEL(log_name, LIBOS_LOG_LEVEL_MIN)

#endif // LIBOS_LOG_H

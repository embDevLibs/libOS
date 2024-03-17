#pragma once
#ifndef LIBOS_PLATFORM_LOG_H
#define LIBOS_PLATFORM_LOG_H

/**
 * @brief The log level for a error message.
 * 
 */
#define LIBOS_LOG_LEVEL_ERR 0

/**
 * @brief The log level for a warning message.
 * 
 */
#define LIBOS_LOG_LEVEL_WRN 1

/**
 * @brief The log level for a info message.
 * 
 */
#define LIBOS_LOG_LEVEL_INF 2

/**
 * @brief The log level for a debug message.
 * 
 */
#define LIBOS_LOG_LEVEL_DBG 3

/**
 * @brief Defines a new log module for this file
 * 
 */
#define LIBOS_LOG_MODULE_MIN_LEVEL(log_name, log_level) static log_module_t __TAG = { .level = log_level, .name = (#log_name) };  

/**
 * @brief Initialize the logging system
 * 
 */
#define LIBOS_LOG_INIT() // Nothing to init for this. Just API compliance.

/**
 * @brief Print a given message on the given log level.
 * 
 */
#define LIBOS_LOG_PRINT(level, ...) libos_log_print(level, __TAG, __VA_ARGS__);

/**
 * @brief Info container for a log module with a specific name.
 * 
 */
typedef struct log_module
{
    int level;          ///< The minimum log level of the log entries.
    const char* name;   ///< The component name of the current file that is included with every log entry.
} log_module_t;

/**
 * @brief Internal API for logging log entries.
 * 
 * @param level The log entry log level.
 * @param module The module for which this log entry is.
 * @param format The printf format of the log entry
 * @param ... The variable arguments for the printf log entry.
 */
void libos_log_print(int level, const log_module_t *module, const char* format, ...);

#endif // LIBOS_PLATFORM_LOG_H

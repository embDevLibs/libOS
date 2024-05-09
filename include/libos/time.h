/**
 * @file time.h
 * @brief Abstract API for time reference keeping.
 * 
 * @details
 * This time module is meant to keep track of 'relative' time.
 * It is not meant for keeping track of the time like a wall
 * clock. The epoch that it chooses is implementation specific
 * and can be everything from a specific date on the calendar,
 * to the time since boot. The application using this module 
 * should not make any assumptions about this.
 * 
 * While specific types like libos_time_milliseconds_t are
 * provided, it is generally recommended to use the libos_time_t
 * to represent time. This will allow libos_time_* to be able
 * to directly operate on it, make consumption by other
 * components easier and provide a more unified experience.
 * 
 * IMPLEMENTORS:
 * For the implementor it is required to provide a
 * libos/platform/time.h header. This header has to provide the
 * following types:
 * 
 *  * libos_time_t
 *  * libos_time_seconds_t
 *  * libos_time_milliseconds_t
 *  * libos_time_microseconds_t
 *  * libos_time_nanoseconds_t
 * 
 * libos_time_t is implementation specific and is allowed to be 
 * anything from a int to struct with complex members. The types
 * for seconds, milliseconds, microseconds, and nanoseconds however
 * have to be signed arithmetic types (aka int, int32_t, etc.).
 * This is required because the difference calculation can be
 * negative.
 * 
 * If the platform provides library functions they should be enclosed
 * in a extern "C" block like: 
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
 * . The general API header for the time places all the functions in
 * a extern "C" code block.
 */

#pragma once
#ifndef LIBOS_TIME_H
#define LIBOS_TIME_H

#include <stdint.h>
#include <stdbool.h>

// Platform specific additions & provisions like the libos_time_*_t types.
#include "libos/platform/time.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Retrieves the current time in libos_time_t format.
 * 
 * @return libos_time_t The representation of the current time.
 */
libos_time_t libos_time_get_now(void);

/**
 * @brief Returns the difference between the two times in nanoseconds.
 * 
 * @param a The time to use as a baseline.
 * @param b The time to get the difference to.
 * 
 * @return libos_time_microseconds_t Returns the time difference in nanoseconds in the platform specific value type.
 */
libos_time_nanoseconds_t libos_time_difference_ms(libos_time_t a, libos_time_t b);

/**
 * @brief Returns the difference between the two times in microseconds.
 * 
 * @param a The time to use as a baseline.
 * @param b The time to get the difference to.
 * 
 * @return libos_time_microseconds_t Returns the time difference in microseconds in the platform specific value type.
 */
libos_time_microseconds_t libos_time_difference_us(libos_time_t a, libos_time_t b);

/**
 * @brief Returns the difference between the two times in milliseconds.
 * 
 * @param a The time to use as a baseline.
 * @param b The time to get the difference to.
 * 
 * @return libos_time_milliseconds_t Returns the time difference in milliseconds in the platform specific value type.
 */
libos_time_milliseconds_t libos_time_difference_ms(libos_time_t a, libos_time_t b);

/**
 * @brief Returns the difference between the two times in seconds.
 * 
 * @param a The time to use as a baseline.
 * @param b The time to get the difference to.
 * 
 * @return libos_time_seconds_t Returns the time difference in seconds in the platform specific value type.
 */
libos_time_seconds_t libos_time_difference_s(libos_time_t a, libos_time_t b);

/**
 * @brief Creates a libos_time_t structure from just the number of nanoseconds since the epoch.
 * 
 * @param ns The nanoseconds component.
 * 
 * @return libos_time_t The resulting time structure.
 */
libos_time_t libos_time_from_ns(libos_time_nanoseconds_t ns);

/**
 * @brief Creates a libos_time_t structure from just the number of microseconds since the epoch.
 * 
 * @param us The microseconds component.
 * 
 * @return libos_time_t The resulting time structure.
 */
libos_time_t libos_time_from_us(libos_time_microseconds_t us);

/**
 * @brief Creates a libos_time_t structure from just the number of milliseconds since the epoch.
 * 
 * @param ms The milliseconds component.
 * 
 * @return libos_time_t The resulting time structure.
 */
libos_time_t libos_time_from_ms(libos_time_milliseconds_t ms);

/**
 * @brief Creates a libos_time_t structure from just the number of seconds since the epoch.
 * 
 * @param s The seconds component.
 * 
 * @return libos_time_t The resulting time structure.
 */
libos_time_t libos_time_from_s(libos_time_seconds_t s);

/**
 * @brief Converts the timestamp to the number of nanoseconds since it's epoch.
 * 
 * @param time The time to convert.
 * 
 * @return libos_time_nanoseconds_t The number of nanoseconds since the epoch.
 */
libos_time_nanoseconds_t libos_time_to_ns(libos_time_t time);

/**
 * @brief Converts the timestamp to the number of microsecond since it's epoch.
 * 
 * @param time The time to convert.
 * 
 * @return libos_time_microseconds_t The number of microseconds since the epoch.
 */
libos_time_microseconds_t libos_time_to_us(libos_time_t time);

/**
 * @brief Converts the timestamp to the number of millisecond since it's epoch
 * 
 * @param time The time to convert.
 * 
 * @return libos_time_milliseconds_t The number of milliseconds since the epoch.
 */
libos_time_milliseconds_t libos_time_to_ms(libos_time_t time);

/**
 * @brief Convert the timestamp to the number of seconds since it's epoch.
 * 
 * @param time The time to convert.
 * 
 * @return libos_time_seconds_t The number of seconds since the epoch.
 */
libos_time_seconds_t libos_time_to_s(libos_time_t time);

/**
 * @brief Subtracts @ref b from the @ref a timestamp.
 * 
 * @param a The base time to subtract from.
 * @param b The time to subtract.
 * 
 * @return libos_time_t The result of the subtraction.
 */
libos_time_t libos_time_subtract(libos_time_t a, libos_time_t b);

/**
 * @brief Adds the two timestamps together.
 * 
 * @param a The base timestamp to add to.
 * @param b The time to add.
 * 
 * @return libos_time_t The result of the addition.
 */
libos_time_t libos_time_add(libos_time_t a, libos_time_t b);

/**
 * @brief Checks if the @ref a timestamp is later than the @ref b timestamp.
 * 
 * @param a Baseline timestamp.
 * @param b The timestamp to compare with.
 * 
 * @retval true If @ref b is later than @ref a.
 * @retval false If @ref b is earlier then @ref a.
 */
bool libos_time_is_later(libos_time_t a, libos_time_t b);

/**
 * @brief Checks if the @ref a timestamp is earlier than the @ref b timestamp.
 * 
 * @param a Baseline timestamp.
 * @param b The timestamp to compare with.
 * 
 * @retval true If @ref b is earlier than @ref a.
 * @retval false If @ref b is later than @ref a.
 */
bool libos_time_is_earlier(libos_time_t a, libos_time_t b);

/**
 * @brief Checks if the @ref a timestamp refers to the same time as @ref b.
 * 
 * @param a Baseline timestamp.
 * @param b The timestamp to compare with.
 * 
 * @retval true If @ref a is the same as @ref b.
 * @retval false If @ref a is NOT the same as @ref b.
 */
bool libos_time_is_same(libos_time_t a, libos_time_t b);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIBOS_TIME_H

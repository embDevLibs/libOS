/**
 * @file mutex.h
 * @brief Abstract API for a Mutex object.
 * 
 * @details
 * This header provides the API to a system native Mutex synchronisation
 * primitive. It provides the general purpose lock and unlock methods,
 * but also a lock with timeout. If the platform supports it, static and
 * dynamic allocations are supported. If only dynamic allocations are supported
 * the system is allowed to wrap static allocations to dynamic allocations.
 * This is with the requirement that libos_mutex_t typedef is still defined.
 * And the expectation that this is clearly documented in the platform
 * implementation documentation.
 * If the platform supports recursive mutexes the prototype for the recursive
 * constructor is enabled. If the platform only supports recursive mutexes, a
 * regular mutex is allowed to show the same behavior (but the recursive
 * prototype also needs to be defined to the actual recursive mutex type). It
 * is the user of the mutex to ensure no recursive lock are done mutexes that
 * may or may not be recursive.
 * 
 * 
 * IMPLEMENTORS:
 * For the implementor it is required to provide a
 * libos/platform/mutex.h header. This header has to provide the
 * following types:
 * * libos_mutex_handle_t
 * * libos_mutex_t (optional)
 * 
 * The libos_mutex_handle_t is a type that refers to a mutex in the system.
 * This is often a pointer but is not required to be one. The libos_mutex_t
 * type is only required if the platform supports static allocations of
 * mutexes. If it only supports dynamic allocations, it MAY wrap static
 * allocations in a dynamic allocation.
 * The recursive mutex must have the same handle type as the regular mutex.
 * To a consumer of the mutex this difference is not visible. If the
 * implementation needs to differentiate between them, this needs be handled
 * internally.
 * 
 * The header provides the LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION and
 * LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION macros. If their value is defined to
 * 1 then the allocation method is supported. If defined to anything else it
 * means not supported. In case the header fails to define them, they will
 * default to 0. A implementation must at least provide 1 initialization
 * method. Providing neither will result in a compile time error.
 * The header also provides LIBOS_MUTEX_ENABLE_RECURSIVE macro. If the value is
 * defined as 1, the platform supports recursive mutexes, any other value, or
 * not defined will indicate no support.
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
#ifndef LIBOS_CONCURRENCY_MUTEX_H
#define LIBOS_CONCURRENCY_MUTEX_H

#include "libos/error.h"
#include "libos/time.h"

#include "libos/platform/concurrent/mutex.h"

#ifndef LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION
#define LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION 0
#endif // LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION

#ifndef LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION
#define LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION 0
#endif // LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION

#ifndef LIBOS_MUTEX_ENABLE_RECURSIVE
#define LIBOS_MUTEX_ENABLE_RECURSIVE 0
#endif // LIBOS_MUTEX_ENABLE_RECURSIVE

#if LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION!=1 && LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION!=1
#error "The platform doesn't provide either a static or dynamic initialization method for mutexes. How are you suppose to initialize mutexes?"
#endif // LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION!=1 && LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION!=1

/**
 * @brief Attempts to lock the mutex within the given time.
 * 
 * @param[in] handle The mutex to lock
 * @param[in] timeout The time (in platform ticks) to allow to take the mutex.
 * 
 * @retval LIBOS_ERR_OK The mutex is successfully locked.
 * @retval LIBOS_ERR_INVALID_ARG @ref handle is NULL.
 * @retval LIBOS_ERR_TIMEOUT Failed to lock the mutex before the end of the timeout.
 * @retval LIBOS_ERR_FAIL In case of platform specific faults.
 * 
 * @return libos_err_t The libos standard success code for locking mutex.
 */
libos_err_t libos_mutex_lock(libos_mutex_handle_t handle, libos_time_t timeout);

/**
 * @brief Unlocks the mutex.
 * 
 * @param[in] handle The mutex to unlock.
 * 
 * @retval LIBOS_ERR_OK The mutex is successfully unlocked.
 * @retval LIBOS_ERR_INVALID_ARG @ref handle is NULL.
 * @retval LIBOS_ERR_INVALID_STATE Failed to unlock the mutex. Usually means the mutex wasn't acquired before.
 * @retval LIBOS_ERR_FAIL In case of platform specific faults.
 * 
 * @return libos_err_t The libos standard success code for unlocking mutex.
 */
libos_err_t libos_mutex_unlock(libos_mutex_handle_t handle);

#if LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION==1

/**
 * @brief Allocate memory for a new mutex and initialize the mutex.
 * 
 * @param[out] handle The handle to the new mutex.
 * 
 * @retval LIBOS_ERR_OK The mutex is successfully created.
 * @retval LIBOS_ERR_INVALID_ARG @ref handle is NULL.
 * @retval LIBOS_ERR_NO_MEM Failed to allocate memory for the mutex.
 * @retval LIBOS_ERR_FAIL In case of platform specific faults.
 * 
 * @return libos_err_t The libos standard success code for allocating and initialing the mutex.
 */
libos_err_t libos_mutex_create_dynamic(libos_mutex_handle_t *handle);

#if LIBOS_MUTEX_ENABLE_RECURSIVE==1

/**
 * @brief Allocate memory for a new mutex and initialize a recursive mutex.
 * 
 * @param[out] handle The handle to the new recursive mutex.
 * 
 * @retval LIBOS_ERR_OK The mutex is successfully created.
 * @retval LIBOS_ERR_INVALID_ARG @ref handle is NULL.
 * @retval LIBOS_ERR_NO_MEM Failed to allocate memory for the mutex.
 * @retval LIBOS_ERR_FAIL In case of platform specific faults.
 * 
 * @return libos_err_t The libos standard success code for allocating and initialing the recursive mutex.
 */
libos_err_t libos_mutex_create_recursive_dynamic(libos_mutex_handle_t *handle);

#endif // LIBOS_MUTEX_ENABLE_RECURSIVE==1

#endif // LIBOS_MUTEX_ENABLE_DYNAMIC_ALLOCATION==1

#if LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION==1

/**
 * @brief Initializes the given mutex.
 * 
 * @param[out] handle The handle to the mutex to initialize.
 * 
 * @retval LIBOS_ERR_OK The mutex is successfully created.
 * @retval LIBOS_ERR_INVALID_ARG @ref handle is NULL.
 * @retval LIBOS_ERR_FAIL In case of platform specific faults.
 * 
 * @return libos_err_t The libos standard success code for initialing the mutex.
 */
libos_err_t libos_mutex_create_static(libos_mutex_handle_t handle);

#if LIBOS_MUTEX_ENABLE_RECURSIVE==1
/**
 * @brief Initializes the given mutex as a recursive mutex.
 * 
 * @param[out] handle The handle to the mutex to initialize.
 * 
 * @retval LIBOS_ERR_OK The mutex is successfully created.
 * @retval LIBOS_ERR_INVALID_ARG @ref handle is NULL.
 * @retval LIBOS_ERR_FAIL In case of platform specific faults.
 * 
 * @return libos_err_t The libos standard success code for initialing the recursive mutex.
 */
libos_err_t libos_mutex_create_recursive_static(libos_mutex_handle_t handle);

#endif // LIBOS_MUTEX_ENABLE_RECURSIVE==1

#endif // LIBOS_MUTEX_ENABLE_STATIC_ALLOCATION==1

/**
 * @brief Deletes the previously initialized mutex (and deallocates if dynamic).
 * 
 * @param handle The mutex to delete.
 */
void libos_mutex_delete(libos_mutex_handle_t handle);

#endif // LIBOS_CONCURRENCY_MUTEX_H

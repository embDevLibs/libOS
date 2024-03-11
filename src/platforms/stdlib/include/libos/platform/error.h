#pragma once
#ifndef LIBOS_PLATFORM_ERROR_H
#define LIBOS_PLATFORM_ERROR_H

#include <errno.h>

// Error type

typedef int libos_err_t;

// Error codes

#define LIBOS_ERR_OK ((libos_err_t)0)
#define LIBOS_ERR_FAIL ((libos_err_t)-1)
#define LIBOS_ERR_NO_MEM ((libos_err_t)ENOMEM)
#define LIBOS_ERR_INVALID_ARG ((libos_err_t)EINVAL)
#define LIBOS_ERR_NOTSUP ((libos_err_t)ENOTSUP)
#define LIBOS_ERR_BUSY ((libos_err_t)EBUSY)
#define LIBOS_ERR_TIMEOUT ((libos_err_t)ETIMEDOUT)

#endif // LIBOS_PLATFORM_ERROR_H

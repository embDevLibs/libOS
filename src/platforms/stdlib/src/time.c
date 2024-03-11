#include <time.h>
#include <sys/time.h>

#include "libos/time.h"

libos_time_t libos_time_get_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // Can't really deal with a 'broken' time result so just ignore the error and hope for the best ¯\_(ツ)_/¯/. Besides, why wouldn't this work.
    return (libos_time_t)( ((libos_time_t)tv.tv_sec * 1000000) + tv.tv_usec);
}

libos_time_microseconds_t libos_time_difference_us(libos_time_t a, libos_time_t b)
{
    return a - b;
}

libos_time_milliseconds_t libos_time_difference_ms(libos_time_t a, libos_time_t b)
{
    return (a - b) / 1000;
}

libos_time_seconds_t libos_time_difference_s(libos_time_t a, libos_time_t b)
{
    return (a - b) / 1000 / 1000;
}

libos_time_t libos_time_from_us(libos_time_microseconds_t us)
{
    return (libos_time_t)us;
}

libos_time_t libos_time_from_ms(libos_time_milliseconds_t ms)
{
    return (libos_time_t)ms * 1000;
}

libos_time_t libos_time_from_s(libos_time_seconds_t s)
{
    return (libos_time_t)s * 1000 * 1000;
}

libos_time_seconds_t libos_time_to_s(libos_time_t time)
{
    return (time / 1000 / 1000);
}

libos_time_milliseconds_t libos_time_to_ms(libos_time_t time)
{
    return (time / 1000);
}

libos_time_microseconds_t libos_time_to_us(libos_time_t time)
{
    return time;
}

libos_time_t libos_time_subtract(libos_time_t a, libos_time_t b)
{
    return (a - b);
}

libos_time_t libos_time_add(libos_time_t a, libos_time_t b)
{
    return (a + b);
}

bool libos_time_is_later(libos_time_t a, libos_time_t b)
{
    return a > b;
}

bool libos_time_is_earlier(libos_time_t a, libos_time_t b)
{
    return a < b;
}

bool libos_time_is_same(libos_time_t a, libos_time_t b)
{
    return a == b;
}

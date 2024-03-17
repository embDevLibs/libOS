#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>

#include "libos/time.h"
#include "libos/log.h"

static const char *err_name = "ERR";
static const char *wrn_name = "WRN";
static const char *inf_name = "INF";
static const char *dbg_name = "DBG";
static const char *unkown_name = "UNK";

static const char *err_to_name(int level)
{
    if (level == LIBOS_LOG_LEVEL_ERR)
    {
        return err_name;
    }

    else if (level == LIBOS_LOG_LEVEL_WRN)
    {
        return wrn_name;
    }
    else if (level == LIBOS_LOG_LEVEL_INF)
    {
        return inf_name;
    }
    else if (level == LIBOS_LOG_LEVEL_DBG)
    {
        return dbg_name;
    }
    else
    {
        return unkown_name;
    }
}

void libos_log_print(int level, const log_module_t *module, const char *format, ...)
{
    if (module == NULL)
    {
        return;
    }

    if (level > module->level)
    {
        va_list list;
        va_start(list, format);
        int64_t now = libos_time_to_ms(libos_time_get_now());
        const char *name = err_to_name(level);
        printf("%8" PRId64 " [%s] %s: ", now, module->name, name); // 3 -> milliseconds -> 5 digits means max is 9 9999 which is about 27 hours, should be fine. Next step would be less than 3 hours.
        vprintf(format, list);
        printf("\n"); // Add that final newline
    }
}

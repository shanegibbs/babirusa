#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "log.h"

gchar* log_timestamp()
{
    time_t t = time(NULL);

    struct tm *tmp;
    tmp = localtime(&t);
    if (tmp == NULL)
    {
        fprintf(stderr, "localtime FAILED");
        exit(1);
    }

    int buflen = 25;
    gchar *timebuf = g_malloc(sizeof(gchar) * buflen);
    int used = strftime(timebuf, buflen, "%F %T", tmp);
    g_assert(used > 0);

    return timebuf;
}

void log_set_level(const gchar *level)
{
    if (g_strcmp0(level, "debug") == 0)
    {
        g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, log_handler, NULL);
    }
    else
    {
        g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MESSAGE, log_handler, NULL);
    }

}

void log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
    static gint i = 1;
    gchar *timebuf = log_timestamp();

    const gchar *level = "";
    switch (log_level)
    {
    case G_LOG_LEVEL_ERROR:
        level = "ERROR";
        break;
    case G_LOG_LEVEL_CRITICAL:
        level = "CRIT";
        break;
    case G_LOG_LEVEL_WARNING:
        level = "WARN";
        break;
    case G_LOG_LEVEL_MESSAGE:
        level = "MSG";
        break;
    case G_LOG_LEVEL_INFO:
        level = "INFO";
        break;
    case G_LOG_LEVEL_DEBUG:
        level = "DEBUG";
        break;
    default:
        level = "UNKNOWN";
        break;
    }

    printf("%-3d %s [%d] %-5s - %s\n", i++, timebuf, getpid(), level, message);
    g_free(timebuf);
}

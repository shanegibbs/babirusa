#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <execinfo.h>

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

void backtrace_printer(int sig)
{
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "\nPrinting stack trace. signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void log_install_backtrace_printer()
{
    signal(SIGSEGV, backtrace_printer);
    signal(SIGABRT, backtrace_printer);
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

    // g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, log_handler, NULL);
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

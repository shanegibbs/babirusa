#include <glib/gstdio.h>
#include <stdio.h>
#include <stdlib.h>

#include "options.h"

void scan_dir(const gchar *p)
{
    g_assert(p != NULL);

    GError *err = NULL;

    GDir *dir = g_dir_open(p, 0, &err);
    if (err != NULL) {
        g_assert(dir == NULL);
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        return;
    }
    g_assert(dir != NULL);

    const gchar *d;
    gchar *full = malloc(1024);
    while ((d = g_dir_read_name(dir)) != NULL) {
        sprintf(full, "%s/%s", p, d);
        g_debug("--> %s", full);

        GStatBuf s;
        if (g_stat(full, &s) == -1) {
            printf("FAILED\n");
            return;
        }

        if ((s.st_mode & S_IFMT) == S_IFDIR) {
            scan_dir(full);
        }

        //scan_dir(d);
    }
    g_dir_close(dir);
}

static void _dummy(const gchar *log_domain,
                   GLogLevelFlags log_level,
                   const gchar *message,
                   gpointer user_data )

{

    GDate *date = g_date_new();
    g_date_set_time_t(date, time (NULL));

    int buflen = 1024;
    gchar *buf = malloc(sizeof(gchar) * buflen);
    // gsize size =
    g_date_strftime(buf, buflen, "%F %T", date);

    printf("%s - %s %s\n", buf, log_domain, message);
    return;
}

int main(int argc, char** argv)
{
    g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, _dummy, NULL);
    // g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,  g_log_default_handler, NULL);

    // g_log_set_handler ("Babirusa", G_LOG_LEVEL_MASK | G_LOG_FLAG_FATAL
    //                   | G_LOG_FLAG_RECURSION, g_log_default_handler, NULL);

    g_message("Starting");

    GError *error = NULL;
    Options *opts = NULL;

    if (!parse_args(argc, argv, &opts, &error)) {
        g_assert(opts == NULL);
        g_assert(error != NULL);
        printf("%s\n", error->message);
        return 1;
    }
    g_assert(opts != NULL);
    g_assert(error == NULL);

    g_message("Path: '%s'", opts->path);
    scan_dir(opts->path);

    g_message("Ended successfully");
    return 0;
}


#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "options.h"
#include "backup.h"

int main(int argc, char** argv)
{
    g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, log_handler, NULL);
    // g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG,  log_handler, NULL);

    g_message("Starting");

    GError *error = NULL;
    Options *opts = NULL;

    if (!parse_args(argc, argv, &opts, &error))
    {
        g_assert(opts == NULL);
        g_assert(error != NULL);
        printf("%s\n", error->message);
        return 1;
    }
    g_assert(opts != NULL);
    g_assert(error == NULL);

    g_message("Path: '%s'", opts->path);
    backup_to_path(opts->path, "target/data");

    g_free(opts);

    g_message("Ended successfully");
    return 0;
}


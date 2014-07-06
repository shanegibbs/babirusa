#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "options.h"
#include "backup.h"
#include "berkeley_registry.h"

int main(int argc, char** argv)
{
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

    log_set_level(opts->level);

    RegistryInterface *reg = Berkeley->new();

    g_message("Path: '%s'", opts->path);
    backup_to_path(opts->path, "target/data", reg);

    reg->free(reg);
    g_free(reg);

    options_free(opts);

    g_message("done");
    return 0;
}

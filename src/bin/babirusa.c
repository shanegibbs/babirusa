#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "options.h"
#include "backup.h"
#include "berkeley_registry.h"

int main(int argc, char** argv)
{
    log_install_backtrace_printer();

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

    Registry *reg = NULL;
    if ((reg = BerkeleyRegistry()->new(&error)) == NULL)
    {
        g_assert(reg == NULL && error != NULL);
    }

    g_assert(reg != NULL && error == NULL);

    g_message("Path: '%s'", opts->path);

    BackupEngine *e = DefaultBackupEngine()->new(NULL);
    g_assert(e != NULL);
    e->set_registry(e, reg);
    e->backup_to_path(e, opts->path, "target/data");

    e->free(e);

    reg->free(reg);
    g_free(reg);

    options_free(opts);

    g_message("done");
    return 0;
}

#include <stdlib.h>
#include <stdio.h>

#include "options.h"

int parse_args(int argc, char** argv, Options **opts)
{

    GError *error = NULL;
    GOptionContext *context;

    Options *o = malloc(sizeof(Options));

    GOptionEntry entries[] = {
        { "path", 'p', 0, G_OPTION_ARG_FILENAME, &o->path, "Path to backup", "PATH" },
        { NULL }
    };

    context = g_option_context_new("- some stuff here");
    g_option_context_add_main_entries(context, entries, NULL);
    if (!g_option_context_parse(context, &argc, &argv, &error)) {
        printf("Error: %s\n", error->message);
        return 1;
    }
    g_option_context_free(context);

    *opts = o;
    return 0;
}

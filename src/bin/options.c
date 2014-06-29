#include <stdlib.h>
#include <stdio.h>

#include "options.h"

GQuark bab_options_error_quark()
{
    return g_quark_from_static_string ("bab-options-error-quark");
}

gboolean parse_args(int argc, char** argv, Options **opts, GError **error)
{
    g_assert(opts != NULL);

    GOptionContext *context;

    Options *o = malloc(sizeof(Options));
    o->path = NULL;

    GOptionEntry entries[] =
    {
        { "path", 'p', 0, G_OPTION_ARG_FILENAME, &o->path, "Path to backup", "PATH" },
        { NULL }
    };

    context = g_option_context_new("- some stuff here");
    g_option_context_add_main_entries(context, entries, NULL);

    GError *err = NULL;
    if (!g_option_context_parse(context, &argc, &argv, &err))
    {
        g_propagate_error(error, err);
        return FALSE;
    }
    g_option_context_free(context);

    if (o->path == NULL)
    {
        g_set_error(error, BAB_OPTIONS_ERROR, BAB_OPTIONS_ERROR_PATH, "No path specified");
        return FALSE;
    }
    *opts = o;
    return TRUE;
}

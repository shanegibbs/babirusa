#include <stdio.h>
#include <glib.h>

#include "options.h"

GQuark bab_options_error_quark()
{
    return g_quark_from_static_string ("bab-options-error-quark");
}

gboolean parse_args(int argc, char** argv, Options **opts, GError **error)
{
    g_assert(opts != NULL);

    GOptionContext *context;

    Options *o = g_malloc(sizeof(Options));
    o->path = NULL;
    o->level = NULL;

    GOptionEntry entries[] =
    {
        { "path", 'p', 0, G_OPTION_ARG_FILENAME, &o->path, "Path to backup", "PATH" },
        { "level", 'l', 0, G_OPTION_ARG_STRING, &o->level, "Log level", "LEVEL" },
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

    if (o->level == NULL)
    {
        o->level = g_strdup("info");
    }

    g_assert(o->path != NULL);
    g_assert(o->level != NULL);

    *opts = o;
    return TRUE;
}

void options_free(Options *opts)
{
    g_free((gpointer)opts->path);
    g_free((gpointer)opts->level);
    g_free(opts);
}

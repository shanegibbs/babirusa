#include <glib.h>

#define BAB_OPTIONS_ERROR bab_options_error_quark()

enum BabOptionsError
{
    BAB_OPTIONS_ERROR_PATH
};

typedef struct
{
    const gchar* path;
    const gchar* level;
} Options;

gboolean parse_args(int argc, char** argv, Options **opts, GError **error);
void options_free(Options *opts);

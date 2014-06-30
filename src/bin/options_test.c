#include <glib.h>
#include <stdio.h>

#include "options.h"

void optionsPathTest(void)
{
    GError *error = NULL;
    char* argv[] =
    {
        "test", "-p", "my-path"
    };
    int argc = 3;
    Options *opts = NULL;

    gboolean result = parse_args(argc, argv, &opts, &error);
    if (error != NULL)
    {
        printf("ERROR: %s\n", error->message);
    }
    g_assert_true(result == TRUE);
    g_assert_null(error);
    g_assert_nonnull(opts);

    g_assert_cmpstr("my-path", == , opts->path);
}

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/options/path", optionsPathTest);
    return g_test_run();
}

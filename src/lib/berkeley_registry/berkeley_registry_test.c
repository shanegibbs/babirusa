#include <glib.h>
#include <stdio.h>

#include "berkeley_registry.h"

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    // g_test_add_func("/options/path", optionsPathTest);
    return g_test_run();
}

#include <glib.h>

typedef struct {
  gchar* path;
} Options;

int parse_args(int argc, char** argv, Options **opts);

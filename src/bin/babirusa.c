#include <glib/gstdio.h>
#include <stdio.h>
#include <stdlib.h>

#include "options.h"

void scan_dir(const gchar *p) {
  g_assert(p != NULL);

  GError *err = NULL;

  GDir *dir = g_dir_open(p, 0, &err);
  if (err != NULL) {
    g_assert(dir == NULL);
    fprintf(stderr, "%s\n", err->message);
    g_error_free(err);
    return;
  }
  g_assert(dir != NULL);

  const gchar *d;
  gchar *full = malloc(1024);
  while ((d = g_dir_read_name(dir)) != NULL) {
    sprintf(full, "%s/%s", p, d);
    printf("--> %s\n", full);

    GStatBuf s;
    if (g_stat(full, &s) == -1) {
      printf("FAILED\n");
      return;
    }

    if ((s.st_mode & S_IFMT) == S_IFDIR) {
      scan_dir(full);
    }

    //scan_dir(d);
  }
  g_dir_close(dir);
}

int main(int argc, char** argv) {

  Options *opts = NULL;

  if (parse_args(argc, argv, &opts)) {
    return 1;
  }

  printf("Path: '%s'\n", opts->path);
  scan_dir(opts->path);

  return 0;
}

